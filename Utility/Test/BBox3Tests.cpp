/**
 * @file BBox3Tests.cpp
 * @brief Ut::BBox3 单元测试 — 3D 算法层的基础数据结构
 *
 * 3D 几何算法（Geo3DAnalysis / BVH3D / SpatialIndex3D）全部依赖 BBox3 做粗筛，
 * 空盒语义、相交判定边界（贴面必须算相交）、expand 的对称性一旦出错，
 * 上层查询会静默漏判。此处锁定这些契约。
 */
#include <gtest/gtest.h>

#include "Ut/BBox3.h"
#include "Ut/Vec.h"

#include <cmath>
#include <limits>

namespace
{
    using BBox3f = Ut::BBox3f;

    BBox3f makeUnitBox()
    {
        return BBox3f(Ut::Vec3f(0, 0, 0), Ut::Vec3f(1, 1, 1));
    }
}  // namespace

// ==================== 空盒语义 ====================

TEST(BBox3Test, DefaultConstructedIsInvalid)
{
    const BBox3f box;
    EXPECT_FALSE(box.isValid());
    EXPECT_EQ(box.minPt[0], std::numeric_limits<float>::max());
    EXPECT_EQ(box.maxPt[0], std::numeric_limits<float>::lowest());
}

TEST(BBox3Test, ResetRestoresEmptyState)
{
    BBox3f box = makeUnitBox();
    ASSERT_TRUE(box.isValid());

    box.reset();
    EXPECT_FALSE(box.isValid());
}

TEST(BBox3Test, ExpandSinglePointMakesDegenerateValidBox)
{
    BBox3f box;
    box.expand(Ut::Vec3f(2, 3, 4));

    ASSERT_TRUE(box.isValid());
    EXPECT_EQ(box.minPt, box.maxPt);
    EXPECT_EQ(box.size(), Ut::Vec3f(0, 0, 0));
    EXPECT_TRUE(box.contains(Ut::Vec3f(2, 3, 4)));
}

// ==================== 两点构造 ====================

TEST(BBox3Test, TwoPointConstructorNormalizesOrder)
{
    const BBox3f box(Ut::Vec3f(3, 1, 5), Ut::Vec3f(-1, 4, 2));
    EXPECT_TRUE(box.isValid());
    EXPECT_EQ(box.minPt, Ut::Vec3f(-1, 1, 2));
    EXPECT_EQ(box.maxPt, Ut::Vec3f(3, 4, 5));
}

TEST(BBox3Test, SixScalarConstructorKeepsValues)
{
    const BBox3f box(-1.0f, -2.0f, -3.0f, 1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(box.isValid());
    EXPECT_EQ(box.center(), Ut::Vec3f(0, 0, 0));
    EXPECT_EQ(box.size(), Ut::Vec3f(2, 4, 6));
}

// ==================== expand ====================

TEST(BBox3Test, ExpandGrowsToCoverAllPoints)
{
    BBox3f box;
    box.expand(Ut::Vec3f(1, 2, 3));
    box.expand(Ut::Vec3f(-1, 5, 0));

    EXPECT_EQ(box.minPt, Ut::Vec3f(-1, 2, 0));
    EXPECT_EQ(box.maxPt, Ut::Vec3f(1, 5, 3));
}

TEST(BBox3Test, ExpandWithInvalidBoxIsNoOp)
{
    BBox3f box = makeUnitBox();
    box.expand(BBox3f());

    EXPECT_EQ(box.minPt, Ut::Vec3f(0, 0, 0));
    EXPECT_EQ(box.maxPt, Ut::Vec3f(1, 1, 1));
}

TEST(BBox3Test, ExpandWithValidBoxUnions)
{
    BBox3f box = makeUnitBox();
    box.expand(BBox3f(Ut::Vec3f(2, -3, 0.5f), Ut::Vec3f(4, 0, 0.6f)));

    EXPECT_EQ(box.minPt, Ut::Vec3f(0, -3, 0));
    EXPECT_EQ(box.maxPt, Ut::Vec3f(4, 1, 1));
}

TEST(BBox3Test, ExpandFromEmptyWithInvalidBoxStaysEmpty)
{
    BBox3f box;
    box.expand(BBox3f());
    EXPECT_FALSE(box.isValid());
}

// ==================== 含点 / 含盒 ====================

TEST(BBox3Test, ContainsPointIncludesBoundary)
{
    const BBox3f box = makeUnitBox();
    EXPECT_TRUE(box.contains(Ut::Vec3f(0.5f, 0.5f, 0.5f)));
    EXPECT_TRUE(box.contains(Ut::Vec3f(0, 0, 0)));
    EXPECT_TRUE(box.contains(Ut::Vec3f(1, 1, 1)));
    EXPECT_FALSE(box.contains(Ut::Vec3f(1.0001f, 0.5f, 0.5f)));
    EXPECT_FALSE(box.contains(Ut::Vec3f(-1e-4f, 0.5f, 0.5f)));
}

TEST(BBox3Test, ContainsBoxRequiresFullCoverage)
{
    const BBox3f outer = makeUnitBox();
    const BBox3f inner(Ut::Vec3f(0.2f, 0.2f, 0.2f), Ut::Vec3f(0.8f, 0.8f, 0.8f));
    const BBox3f straddle(Ut::Vec3f(0.5f, 0.5f, 0.5f), Ut::Vec3f(2, 2, 2));

    EXPECT_TRUE(outer.contains(inner));
    EXPECT_FALSE(outer.contains(straddle));
    EXPECT_TRUE(outer.contains(outer));
}

// ==================== 相关几何量 ====================

TEST(BBox3Test, CenterSizeDiagonalAndMaxExtent)
{
    const BBox3f box(Ut::Vec3f(0, 0, 0), Ut::Vec3f(2, 4, 4));
    EXPECT_EQ(box.center(), Ut::Vec3f(1, 2, 2));
    EXPECT_EQ(box.size(), Ut::Vec3f(2, 4, 4));
    EXPECT_NEAR(box.diagonal(), 6.0f, 1e-5f);
    EXPECT_NEAR(box.maxExtent(), 4.0f, 1e-6f);
}

TEST(BBox3Test, EmptyBoxHasMeaninglessCenterButFiniteOffsets)
{
    const BBox3f box;
    // 空盒的几何量无意义，此处只锁定实现不会产生 NaN（下游算法会拿它参与运算）
    const Ut::Vec3f c = box.center();
    EXPECT_FALSE(std::isnan(c[0]));
    EXPECT_FALSE(std::isnan(c[1]));
    EXPECT_FALSE(std::isnan(c[2]));
}

// ==================== 相交 ====================

TEST(BBox3Test, TouchingBoxesIntersect)
{
    const BBox3f a = makeUnitBox();
    const BBox3f b(Ut::Vec3f(1, 0, 0), Ut::Vec3f(2, 1, 1));  // 贴面
    EXPECT_TRUE(a.intersects(b));
    EXPECT_TRUE(b.intersects(a));
}

TEST(BBox3Test, SeparatedOnSingleAxisDoesNotIntersect)
{
    const BBox3f a = makeUnitBox();
    const BBox3f bx(Ut::Vec3f(1.001f, 0, 0), Ut::Vec3f(2, 1, 1));
    const BBox3f by(Ut::Vec3f(0, -2, 0), Ut::Vec3f(1, -1.001f, 1));
    const BBox3f bz(Ut::Vec3f(0, 0, -2), Ut::Vec3f(1, 1, -1.001f));

    EXPECT_FALSE(a.intersects(bx));
    EXPECT_FALSE(a.intersects(by));
    EXPECT_FALSE(a.intersects(bz));
}

TEST(BBox3Test, IntersectsIsSymmetricForContainedBox)
{
    const BBox3f outer = makeUnitBox();
    const BBox3f inner(Ut::Vec3f(0.25f, 0.25f, 0.25f), Ut::Vec3f(0.75f, 0.75f, 0.75f));

    EXPECT_TRUE(outer.intersects(inner));
    EXPECT_TRUE(inner.intersects(outer));
}

TEST(BBox3Test, EmptyBoxNeverIntersects)
{
    const BBox3f empty;
    EXPECT_FALSE(empty.intersects(makeUnitBox()));
    EXPECT_FALSE(makeUnitBox().intersects(empty));
}

// ==================== 相等比较（空间索引按值删除依赖） ====================

TEST(BBox3Test, EqualityComparesBounds)
{
    const BBox3f a = makeUnitBox();
    const BBox3f b(Ut::Vec3f(0, 0, 0), Ut::Vec3f(1, 1, 1));
    const BBox3f c(Ut::Vec3f(0, 0, 0), Ut::Vec3f(1, 1, 2));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(BBox3Test, DoublePrecisionBoxUsesSameContract)
{
    Ut::BBox3d box(Ut::Vec3d(0, 0, 0), Ut::Vec3d(1e-9, 1e-9, 1e-9));
    EXPECT_TRUE(box.isValid());
    EXPECT_TRUE(box.contains(Ut::Vec3d(1e-9, 0.0, 0.0)));
    EXPECT_NEAR(box.diagonal(), 1.7320508075688772e-9, 1e-20);
}
