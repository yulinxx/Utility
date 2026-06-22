#include <gtest/gtest.h>
#include "BBox/BBox2d.hpp"

#include <cmath>
#include <limits>

using namespace Ut;

// ==================== BBox2d 构造函数测�?====================

TEST(BBox2dTest, DefaultConstructor)
{
    BBox2d bbox;
    EXPECT_FALSE(bbox.isValid());
}

TEST(BBox2dTest, TwoPointConstructor)
{
    Vec2d p1(1.0, 2.0);
    Vec2d p2(3.0, 4.0);
    BBox2d bbox(p1, p2);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 4.0);
}

TEST(BBox2dTest, TwoPointConstructorReversed)
{
    Vec2d p1(3.0, 4.0);
    Vec2d p2(1.0, 2.0);
    BBox2d bbox(p1, p2);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 4.0);
}

TEST(BBox2dTest, FourValueConstructor)
{
    BBox2d bbox(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 4.0);
}

TEST(BBox2dTest, FourValueConstructorReversed)
{
    BBox2d bbox(3.0, 4.0, 1.0, 2.0);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 4.0);
}

TEST(BBox2dTest, CopyConstructor)
{
    BBox2d bbox1(1.0, 2.0, 3.0, 4.0);
    BBox2d bbox2(bbox1);
    EXPECT_TRUE(bbox2.isValid());
    EXPECT_EQ(bbox1.minPt, bbox2.minPt);
    EXPECT_EQ(bbox1.maxPt, bbox2.maxPt);
}

// ==================== BBox2d 基本属性测�?====================

TEST(BBox2dTest, Width)
{
    BBox2d bbox(1.0, 2.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(bbox.width(), 4.0);
}

TEST(BBox2dTest, Height)
{
    BBox2d bbox(1.0, 2.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(bbox.height(), 4.0);
}

TEST(BBox2dTest, Center)
{
    BBox2d bbox(0.0, 0.0, 10.0, 20.0);
    Vec2d center = bbox.center();
    EXPECT_DOUBLE_EQ(center.x(), 5.0);
    EXPECT_DOUBLE_EQ(center.y(), 10.0);
}

TEST(BBox2dTest, Area)
{
    BBox2d bbox(0.0, 0.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(bbox.area(), 12.0);
}

TEST(BBox2dTest, Diagonal)
{
    BBox2d bbox(0.0, 0.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(bbox.diagonal(), 5.0);
}

// ==================== BBox2d reset 测试 ====================

TEST(BBox2dTest, Reset)
{
    BBox2d bbox(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(bbox.isValid());
    bbox.reset();
    EXPECT_FALSE(bbox.isValid());
}

// ==================== BBox2d expand 测试 ====================

TEST(BBox2dTest, ExpandByPoint)
{
    BBox2d bbox;
    EXPECT_FALSE(bbox.isValid());
    
    bbox.expand(Vec2d(1.0, 2.0));
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 2.0);
    
    bbox.expand(Vec2d(3.0, 0.0));
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 1.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 2.0);
}

TEST(BBox2dTest, ExpandByBBox)
{
    BBox2d bbox1(0.0, 0.0, 2.0, 2.0);
    BBox2d bbox2(1.0, 1.0, 3.0, 3.0);
    bbox1.expand(bbox2);
    EXPECT_DOUBLE_EQ(bbox1.minPt.x(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.maxPt.x(), 3.0);
    EXPECT_DOUBLE_EQ(bbox1.maxPt.y(), 3.0);
}

TEST(BBox2dTest, ExpandByInvalidBBox)
{
    BBox2d bbox1(0.0, 0.0, 2.0, 2.0);
    BBox2d bbox2;
    bbox1.expand(bbox2);
    EXPECT_DOUBLE_EQ(bbox1.minPt.x(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(bbox1.maxPt.x(), 2.0);
    EXPECT_DOUBLE_EQ(bbox1.maxPt.y(), 2.0);
}

// ==================== BBox2d contains 测试 ====================

TEST(BBox2dTest, ContainsPoint)
{
    BBox2d bbox(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(bbox.contains(Vec2d(5.0, 5.0)));
    EXPECT_TRUE(bbox.contains(Vec2d(0.0, 0.0)));
    EXPECT_TRUE(bbox.contains(Vec2d(10.0, 10.0)));
    EXPECT_FALSE(bbox.contains(Vec2d(-1.0, 5.0)));
    EXPECT_FALSE(bbox.contains(Vec2d(5.0, -1.0)));
    EXPECT_FALSE(bbox.contains(Vec2d(11.0, 5.0)));
    EXPECT_FALSE(bbox.contains(Vec2d(5.0, 11.0)));
}

TEST(BBox2dTest, ContainsBBox)
{
    BBox2d outer(0.0, 0.0, 10.0, 10.0);
    BBox2d inner(2.0, 2.0, 8.0, 8.0);
    BBox2d overlap(5.0, 5.0, 15.0, 15.0);
    
    EXPECT_TRUE(outer.contains(inner));
    EXPECT_FALSE(inner.contains(outer));
    EXPECT_FALSE(outer.contains(overlap));
}

TEST(BBox2dTest, ContainsBBoxExact)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(bbox1.contains(bbox2));
}

// ==================== BBox2d intersects 测试 ====================

TEST(BBox2dTest, Intersects)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(5.0, 5.0, 15.0, 15.0);
    BBox2d bbox3(11.0, 11.0, 20.0, 20.0);
    BBox2d bbox4(-5.0, -5.0, -1.0, -1.0);
    
    EXPECT_TRUE(bbox1.intersects(bbox2));
    EXPECT_TRUE(bbox2.intersects(bbox1));
    EXPECT_FALSE(bbox1.intersects(bbox3));
    EXPECT_FALSE(bbox1.intersects(bbox4));
}

TEST(BBox2dTest, IntersectsEdgeTouching)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(10.0, 0.0, 20.0, 10.0);
    EXPECT_TRUE(bbox1.intersects(bbox2));
}

TEST(BBox2dTest, IntersectsWithInvalid)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2;
    EXPECT_FALSE(bbox1.intersects(bbox2));
}

// ==================== BBox2d intersection 测试 ====================

TEST(BBox2dTest, Intersection)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(5.0, 5.0, 15.0, 15.0);
    BBox2d result = bbox1.intersection(bbox2);
    
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.minPt.x(), 5.0);
    EXPECT_DOUBLE_EQ(result.minPt.y(), 5.0);
    EXPECT_DOUBLE_EQ(result.maxPt.x(), 10.0);
    EXPECT_DOUBLE_EQ(result.maxPt.y(), 10.0);
}

TEST(BBox2dTest, IntersectionNoOverlap)
{
    BBox2d bbox1(0.0, 0.0, 5.0, 5.0);
    BBox2d bbox2(10.0, 10.0, 15.0, 15.0);
    BBox2d result = bbox1.intersection(bbox2);
    EXPECT_FALSE(result.isValid());
}

TEST(BBox2dTest, IntersectionCompleteOverlap)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(2.0, 2.0, 8.0, 8.0);
    BBox2d result = bbox1.intersection(bbox2);
    
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.minPt.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.maxPt.x(), 8.0);
    EXPECT_DOUBLE_EQ(result.maxPt.y(), 8.0);
}

// ==================== BBox2d united 测试 ====================

TEST(BBox2dTest, United)
{
    BBox2d bbox1(0.0, 0.0, 5.0, 5.0);
    BBox2d bbox2(3.0, 3.0, 10.0, 10.0);
    BBox2d result = bbox1.united(bbox2);
    
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.minPt.x(), 0.0);
    EXPECT_DOUBLE_EQ(result.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(result.maxPt.x(), 10.0);
    EXPECT_DOUBLE_EQ(result.maxPt.y(), 10.0);
}

// ==================== BBox2d inflate/deflate 测试 ====================

TEST(BBox2dTest, Inflated)
{
    BBox2d bbox(0.0, 0.0, 10.0, 10.0);
    BBox2d result = bbox.inflated(2.0);
    
    EXPECT_DOUBLE_EQ(result.minPt.x(), -2.0);
    EXPECT_DOUBLE_EQ(result.minPt.y(), -2.0);
    EXPECT_DOUBLE_EQ(result.maxPt.x(), 12.0);
    EXPECT_DOUBLE_EQ(result.maxPt.y(), 12.0);
}

TEST(BBox2dTest, Deflated)
{
    BBox2d bbox(0.0, 0.0, 10.0, 10.0);
    BBox2d result = bbox.deflated(2.0);
    
    EXPECT_DOUBLE_EQ(result.minPt.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.minPt.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.maxPt.x(), 8.0);
    EXPECT_DOUBLE_EQ(result.maxPt.y(), 8.0);
}

TEST(BBox2dTest, DeflatedTooMuch)
{
    BBox2d bbox(0.0, 0.0, 5.0, 5.0);
    BBox2d result = bbox.deflated(10.0);
    EXPECT_FALSE(result.isValid());
}

// ==================== BBox2d 比较运算符测�?====================

TEST(BBox2dTest, Equality)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox3(0.0, 0.0, 11.0, 10.0);
    
    EXPECT_TRUE(bbox1 == bbox2);
    EXPECT_FALSE(bbox1 == bbox3);
}

TEST(BBox2dTest, Inequality)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox3(0.0, 0.0, 11.0, 10.0);
    
    EXPECT_FALSE(bbox1 != bbox2);
    EXPECT_TRUE(bbox1 != bbox3);
}

// ==================== BBox2d 赋值运算符测试 ====================

TEST(BBox2dTest, Assignment)
{
    BBox2d bbox1(0.0, 0.0, 10.0, 10.0);
    BBox2d bbox2;
    bbox2 = bbox1;
    EXPECT_EQ(bbox1, bbox2);
}

TEST(BBox2dTest, SelfAssignment)
{
    BBox2d bbox(0.0, 0.0, 10.0, 10.0);
    bbox = bbox;
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 10.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 10.0);
}

// ==================== BBox2d 边界情况测试 ====================

TEST(BBox2dTest, ZeroSizeBBox)
{
    BBox2d bbox(5.0, 5.0, 5.0, 5.0);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.width(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.height(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.area(), 0.0);
}

TEST(BBox2dTest, NegativeSize)
{
    BBox2d bbox(10.0, 10.0, 0.0, 0.0);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.minPt.x(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.minPt.y(), 0.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.x(), 10.0);
    EXPECT_DOUBLE_EQ(bbox.maxPt.y(), 10.0);
}

TEST(BBox2dTest, LargeValues)
{
    double large = 1e100;
    BBox2d bbox(-large, -large, large, large);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.width(), 2.0 * large);
}

TEST(BBox2dTest, NegativeCoordinates)
{
    BBox2d bbox(-10.0, -5.0, 5.0, 10.0);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_DOUBLE_EQ(bbox.width(), 15.0);
    EXPECT_DOUBLE_EQ(bbox.height(), 15.0);
    EXPECT_DOUBLE_EQ(bbox.center().x(), -2.5);
    EXPECT_DOUBLE_EQ(bbox.center().y(), 2.5);
}

// ==================== BBox2f 测试 ====================

TEST(BBox2fTest, FloatBBox)
{
    BBox2f bbox(0.0f, 0.0f, 10.0f, 10.0f);
    EXPECT_TRUE(bbox.isValid());
    EXPECT_FLOAT_EQ(bbox.width(), 10.0f);
    EXPECT_FLOAT_EQ(bbox.height(), 10.0f);
}
