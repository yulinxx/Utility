#include <gtest/gtest.h>
#include "Vec/Vec.hpp"

#include <cmath>
#include <stdexcept>
#include <vector>

using namespace Ut;

// ==================== Vec2d 构造函数测试 ====================

TEST(Vec2dTest, DefaultConstructor)
{
    Vec2d v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
}

TEST(Vec2dTest, ValueConstructor)
{
    Vec2d v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 3.0);
    EXPECT_DOUBLE_EQ(v.y(), 4.0);
}

TEST(Vec2dTest, SingleValueConstructor)
{
    Vec2d v(5.0);
    EXPECT_DOUBLE_EQ(v.x(), 5.0);
    EXPECT_DOUBLE_EQ(v.y(), 5.0);
}

TEST(Vec2dTest, CopyConstructor)
{
    Vec2d v1(1.0, 2.0);
    Vec2d v2(v1);
    EXPECT_DOUBLE_EQ(v2.x(), 1.0);
    EXPECT_DOUBLE_EQ(v2.y(), 2.0);
}

// ==================== Vec2d 访问器测试 ====================

TEST(Vec2dTest, IndexAccess)
{
    Vec2d v(1.0, 2.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    
    v[0] = 10.0;
    v[1] = 20.0;
    EXPECT_DOUBLE_EQ(v.x(), 10.0);
    EXPECT_DOUBLE_EQ(v.y(), 20.0);
}

TEST(Vec2dTest, IndexOutOfRange)
{
    Vec2d v(1.0, 2.0);
    EXPECT_THROW(v[2], std::out_of_range);
}

TEST(Vec2dTest, Dimension)
{
    EXPECT_EQ(Vec2d::dimension(), 2);
    EXPECT_EQ(Vec3d::dimension(), 3);
}

// ==================== Vec2d 算术运算测试 ====================

TEST(Vec2dTest, Addition)
{
    Vec2d v1(1.0, 2.0);
    Vec2d v2(3.0, 4.0);
    Vec2d result = v1 + v2;
    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 6.0);
}

TEST(Vec2dTest, Subtraction)
{
    Vec2d v1(5.0, 7.0);
    Vec2d v2(3.0, 4.0);
    Vec2d result = v1 - v2;
    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), 3.0);
}

TEST(Vec2dTest, ScalarMultiplication)
{
    Vec2d v(2.0, 3.0);
    Vec2d result = v * 2.0;
    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 6.0);
}

TEST(Vec2dTest, ScalarMultiplicationLeft)
{
    Vec2d v(2.0, 3.0);
    Vec2d result = 2.0 * v;
    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 6.0);
}

TEST(Vec2dTest, ScalarDivision)
{
    Vec2d v(4.0, 6.0);
    Vec2d result = v / 2.0;
    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), 3.0);
}

TEST(Vec2dTest, DivisionByZero)
{
    Vec2d v(1.0, 2.0);
    EXPECT_THROW(v / 0.0, std::runtime_error);
}

TEST(Vec2dTest, Negation)
{
    Vec2d v(3.0, -4.0);
    Vec2d result = -v;
    EXPECT_DOUBLE_EQ(result.x(), -3.0);
    EXPECT_DOUBLE_EQ(result.y(), 4.0);
}

// ==================== Vec2d 复合赋值测试 ====================

TEST(Vec2dTest, AdditionAssignment)
{
    Vec2d v(1.0, 2.0);
    v += Vec2d(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 4.0);
    EXPECT_DOUBLE_EQ(v.y(), 6.0);
}

TEST(Vec2dTest, SubtractionAssignment)
{
    Vec2d v(5.0, 7.0);
    v -= Vec2d(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 2.0);
    EXPECT_DOUBLE_EQ(v.y(), 3.0);
}

TEST(Vec2dTest, MultiplicationAssignment)
{
    Vec2d v(2.0, 3.0);
    v *= 2.0;
    EXPECT_DOUBLE_EQ(v.x(), 4.0);
    EXPECT_DOUBLE_EQ(v.y(), 6.0);
}

TEST(Vec2dTest, DivisionAssignment)
{
    Vec2d v(4.0, 6.0);
    v /= 2.0;
    EXPECT_DOUBLE_EQ(v.x(), 2.0);
    EXPECT_DOUBLE_EQ(v.y(), 3.0);
}

TEST(Vec2dTest, DivisionAssignmentByZero)
{
    Vec2d v(1.0, 2.0);
    EXPECT_THROW(v /= 0.0, std::runtime_error);
}

// ==================== Vec2d 比较测试 ====================

TEST(Vec2dTest, Equality)
{
    Vec2d v1(1.0, 2.0);
    Vec2d v2(1.0, 2.0);
    Vec2d v3(1.0, 3.0);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vec2dTest, Inequality)
{
    Vec2d v1(1.0, 2.0);
    Vec2d v2(1.0, 2.0);
    Vec2d v3(1.0, 3.0);
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

// ==================== Vec2d 点积测试 ====================

TEST(Vec2dTest, DotProduct)
{
    Vec2d v1(3.0, 4.0);
    Vec2d v2(4.0, 5.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(Vec2dTest, DotPerpendicularVectors)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.0, 1.0);
    EXPECT_DOUBLE_EQ(v1.dot(v2), 0.0);
}

// ==================== Vec2d 叉积测试 ====================

TEST(Vec2dTest, Cross2D)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.0, 1.0);
    double result = v1.cross2D(v2);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(Vec2dTest, Cross2DParallel)
{
    Vec2d v1(2.0, 3.0);
    Vec2d v2(4.0, 6.0);
    EXPECT_DOUBLE_EQ(v1.cross2D(v2), 0.0);
}

// ==================== Vec2d 长度测试 ====================

TEST(Vec2dTest, LengthSquared)
{
    Vec2d v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.lengthSquared(), 25.0);
}

TEST(Vec2dTest, Length)
{
    Vec2d v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vec2dTest, ZeroVectorLength)
{
    Vec2d v(0.0, 0.0);
    EXPECT_DOUBLE_EQ(v.length(), 0.0);
}

// ==================== Vec2d 距离测试 ====================

TEST(Vec2dTest, Distance)
{
    Vec2d v1(0.0, 0.0);
    Vec2d v2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v1.distance(v2), 5.0);
}

TEST(Vec2dTest, DistanceSquared)
{
    Vec2d v1(0.0, 0.0);
    Vec2d v2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v1.distanceSquared(v2), 25.0);
}

// ==================== Vec2d 归一化测试 ====================

TEST(Vec2dTest, Normalized)
{
    Vec2d v(3.0, 4.0);
    Vec2d result = v.normalized();
    EXPECT_TRUE(result.isUnit());
    EXPECT_DOUBLE_EQ(result.x(), 0.6);
    EXPECT_DOUBLE_EQ(result.y(), 0.8);
}

TEST(Vec2dTest, NormalizeInPlace)
{
    Vec2d v(3.0, 4.0);
    v.normalize();
    EXPECT_TRUE(v.isUnit());
    EXPECT_DOUBLE_EQ(v.x(), 0.6);
    EXPECT_DOUBLE_EQ(v.y(), 0.8);
}

TEST(Vec2dTest, NormalizeZeroVector)
{
    Vec2d v(0.0, 0.0);
    EXPECT_THROW(v.normalize(), std::runtime_error);
    EXPECT_THROW(v.normalized(), std::runtime_error);
}

// ==================== Vec2d 特殊向量测试 ====================

TEST(Vec2dTest, IsZero)
{
    Vec2d v1(0.0, 0.0);
    Vec2d v2(1e-7, 0.0);
    Vec2d v3(1e-5, 0.0);
    EXPECT_TRUE(v1.isZero());
    EXPECT_TRUE(v2.isZero(1e-6));
    EXPECT_FALSE(v3.isZero(1e-6));
}

TEST(Vec2dTest, IsUnit)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.6, 0.8);
    Vec2d v3(1.0, 1.0);
    EXPECT_TRUE(v1.isUnit());
    EXPECT_TRUE(v2.isUnit());
    EXPECT_FALSE(v3.isUnit());
}

// ==================== Vec2d 角度测试 ====================

TEST(Vec2dTest, Angle)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.0, 1.0);
    double angle = v1.angle(v2);
    EXPECT_NEAR(angle, 3.14159265358979323846 / 2.0, 1e-10);
}

TEST(Vec2dTest, AngleDegrees)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.0, 1.0);
    double angle = v1.angleDegrees(v2);
    EXPECT_NEAR(angle, 90.0, 1e-10);
}

TEST(Vec2dTest, AngleWithZeroVector)
{
    Vec2d v1(1.0, 0.0);
    Vec2d v2(0.0, 0.0);
    EXPECT_THROW(v1.angle(v2), std::runtime_error);
}

// ==================== Vec2d 投影测试 ====================

TEST(Vec2dTest, Project)
{
    Vec2d v(3.0, 4.0);
    Vec2d onto(1.0, 0.0);
    Vec2d result = v.project(onto);
    EXPECT_DOUBLE_EQ(result.x(), 3.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
}

TEST(Vec2dTest, ProjectOntoZeroVector)
{
    Vec2d v(1.0, 2.0);
    Vec2d onto(0.0, 0.0);
    EXPECT_THROW(v.project(onto), std::runtime_error);
}

// ==================== Vec2d 反射测试 ====================

TEST(Vec2dTest, Reflect)
{
    Vec2d v(1.0, -1.0);
    Vec2d normal(0.0, 1.0);
    Vec2d result = v.reflect(normal);
    EXPECT_DOUBLE_EQ(result.x(), 1.0);
    EXPECT_DOUBLE_EQ(result.y(), 1.0);
}

// ==================== Vec2d 插值测试 ====================

TEST(Vec2dTest, Lerp)
{
    Vec2d v1(0.0, 0.0);
    Vec2d v2(10.0, 20.0);
    Vec2d result = v1.lerp(v2, 0.5);
    EXPECT_DOUBLE_EQ(result.x(), 5.0);
    EXPECT_DOUBLE_EQ(result.y(), 10.0);
}

TEST(Vec2dTest, LerpEndpoints)
{
    Vec2d v1(0.0, 0.0);
    Vec2d v2(10.0, 20.0);
    Vec2d start = v1.lerp(v2, 0.0);
    Vec2d end = v1.lerp(v2, 1.0);
    EXPECT_EQ(start, v1);
    EXPECT_EQ(end, v2);
}

// ==================== Vec2d 分量操作测试 ====================

TEST(Vec2dTest, MinMax)
{
    Vec2d v1(1.0, 5.0);
    Vec2d v2(3.0, 2.0);
    Vec2d minVec = Vec2d::min(v1, v2);
    Vec2d maxVec = Vec2d::max(v1, v2);
    EXPECT_DOUBLE_EQ(minVec.x(), 1.0);
    EXPECT_DOUBLE_EQ(minVec.y(), 2.0);
    EXPECT_DOUBLE_EQ(maxVec.x(), 3.0);
    EXPECT_DOUBLE_EQ(maxVec.y(), 5.0);
}

TEST(Vec2dTest, Clamp)
{
    Vec2d v(5.0, -5.0);
    Vec2d minVec(0.0, 0.0);
    Vec2d maxVec(10.0, 10.0);
    Vec2d result = v.clamp(minVec, maxVec);
    EXPECT_DOUBLE_EQ(result.x(), 5.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
}

// ==================== Vec3d 测试 ====================

TEST(Vec3dTest, Constructor)
{
    Vec3d v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST(Vec3dTest, CrossProduct)
{
    Vec3d v1(1.0, 0.0, 0.0);
    Vec3d v2(0.0, 1.0, 0.0);
    Vec3d result = v1.cross(v2);
    EXPECT_DOUBLE_EQ(result.x(), 0.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
    EXPECT_DOUBLE_EQ(result.z(), 1.0);
}

TEST(Vec3dTest, CrossProductParallel)
{
    Vec3d v1(2.0, 3.0, 4.0);
    Vec3d v2(4.0, 6.0, 8.0);
    Vec3d result = v1.cross(v2);
    EXPECT_TRUE(result.isZero());
}

TEST(Vec3dTest, DotProduct)
{
    Vec3d v1(1.0, 2.0, 3.0);
    Vec3d v2(4.0, 5.0, 6.0);
    double result = v1.dot(v2);
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(Vec3dTest, Length)
{
    Vec3d v(1.0, 2.0, 2.0);
    EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

// ==================== Vec2i 测试 ====================

TEST(Vec2iTest, IntegerVector)
{
    Vec2i v(3, 4);
    EXPECT_EQ(v.x(), 3);
    EXPECT_EQ(v.y(), 4);
    EXPECT_EQ(v.lengthSquared(), 25);
}

TEST(Vec2iTest, IntegerAddition)
{
    Vec2i v1(10, 20);
    Vec2i v2(5, 15);
    Vec2i result = v1 + v2;
    EXPECT_EQ(result.x(), 15);
    EXPECT_EQ(result.y(), 35);
}

// ==================== Vec2f 测试 ====================

TEST(Vec2fTest, FloatVector)
{
    Vec2f v(1.5f, 2.5f);
    EXPECT_FLOAT_EQ(v.x(), 1.5f);
    EXPECT_FLOAT_EQ(v.y(), 2.5f);
}

// ==================== 赋值运算符测试 ====================

TEST(Vec2dTest, Assignment)
{
    Vec2d v1(1.0, 2.0);
    Vec2d v2;
    v2 = v1;
    EXPECT_EQ(v1, v2);
}

TEST(Vec2dTest, SelfAssignment)
{
    Vec2d v(1.0, 2.0);
    v = v;
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
}

// ==================== 边界情况测试 ====================

TEST(Vec2dTest, LargeValues)
{
    double large = 1e100;
    Vec2d v(large, large);
    EXPECT_DOUBLE_EQ(v.x(), large);
    EXPECT_DOUBLE_EQ(v.y(), large);
}

TEST(Vec2dTest, NegativeValues)
{
    Vec2d v(-1.0, -2.0);
    EXPECT_DOUBLE_EQ(v.x(), -1.0);
    EXPECT_DOUBLE_EQ(v.y(), -2.0);
    EXPECT_DOUBLE_EQ(v.length(), std::sqrt(5.0));
}
