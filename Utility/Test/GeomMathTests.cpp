/**
 * @file GeomMathTests.cpp
 * @brief GeomMath 基础数学工具单元测试
 *
 * 测试目标：
 * - 验证容差比较函数
 * - 验证区间工具函数
 * - 验证角度工具函数
 * - 验证符号工具函数
 */

#include <gtest/gtest.h>
#include "Ut/GeomMath.h"

#include <cmath>

using namespace Ut;

// ==================== 容差比较测试 ====================

TEST(GeomMathTest, IsZero_ExactZero)
{
    EXPECT_TRUE(GeomMath::isZero(0.0));
}

TEST(GeomMathTest, IsZero_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::isZero(1e-10, 1e-9));
    EXPECT_TRUE(GeomMath::isZero(-1e-10, 1e-9));
}

TEST(GeomMathTest, IsZero_OutsideTolerance)
{
    EXPECT_FALSE(GeomMath::isZero(1e-8, 1e-9));
    EXPECT_FALSE(GeomMath::isZero(-1e-8, 1e-9));
}

TEST(GeomMathTest, AlmostEqual_ExactEqual)
{
    EXPECT_TRUE(GeomMath::almostEqual(1.0, 1.0));
    EXPECT_TRUE(GeomMath::almostEqual(-1.0, -1.0));
}

TEST(GeomMathTest, AlmostEqual_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::almostEqual(1.0, 1.0 + 1e-10, 1e-9));
    EXPECT_TRUE(GeomMath::almostEqual(1.0, 1.0 - 1e-10, 1e-9));
}

TEST(GeomMathTest, AlmostEqual_OutsideTolerance)
{
    EXPECT_FALSE(GeomMath::almostEqual(1.0, 1.0 + 1e-8, 1e-9));
    EXPECT_FALSE(GeomMath::almostEqual(1.0, 1.0 - 1e-8, 1e-9));
}

TEST(GeomMathTest, LessOrEqual_ExactEqual)
{
    EXPECT_TRUE(GeomMath::lessOrEqual(1.0, 1.0));
}

TEST(GeomMathTest, LessOrEqual_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::lessOrEqual(1.0, 1.0 + 1e-10, 1e-9));
    EXPECT_TRUE(GeomMath::lessOrEqual(1.0 - 1e-10, 1.0, 1e-9));
}

TEST(GeomMathTest, LessOrEqual_OutsideTolerance)
{
    EXPECT_FALSE(GeomMath::lessOrEqual(1.0 + 1e-8, 1.0, 1e-9));
}

TEST(GeomMathTest, GreaterOrEqual_ExactEqual)
{
    EXPECT_TRUE(GeomMath::greaterOrEqual(1.0, 1.0));
}

TEST(GeomMathTest, GreaterOrEqual_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::greaterOrEqual(1.0, 1.0 - 1e-10, 1e-9));
    EXPECT_TRUE(GeomMath::greaterOrEqual(1.0 + 1e-10, 1.0, 1e-9));
}

TEST(GeomMathTest, GreaterOrEqual_OutsideTolerance)
{
    EXPECT_FALSE(GeomMath::greaterOrEqual(1.0 - 1e-8, 1.0, 1e-9));
}

// ==================== 区间工具测试 ====================

TEST(GeomMathTest, Clamp_WithinRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp(5.0, 0.0, 10.0), 5.0);
}

TEST(GeomMathTest, Clamp_BelowRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp(-5.0, 0.0, 10.0), 0.0);
}

TEST(GeomMathTest, Clamp_AboveRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp(15.0, 0.0, 10.0), 10.0);
}

TEST(GeomMathTest, Clamp01_WithinRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp01(0.5), 0.5);
}

TEST(GeomMathTest, Clamp01_BelowRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp01(-0.5), 0.0);
}

TEST(GeomMathTest, Clamp01_AboveRange)
{
    EXPECT_DOUBLE_EQ(GeomMath::clamp01(1.5), 1.0);
}

TEST(GeomMathTest, Lerp_StartPoint)
{
    EXPECT_DOUBLE_EQ(GeomMath::lerp(0.0, 10.0, 0.0), 0.0);
}

TEST(GeomMathTest, Lerp_EndPoint)
{
    EXPECT_DOUBLE_EQ(GeomMath::lerp(0.0, 10.0, 1.0), 10.0);
}

TEST(GeomMathTest, Lerp_MiddlePoint)
{
    EXPECT_DOUBLE_EQ(GeomMath::lerp(0.0, 10.0, 0.5), 5.0);
}

TEST(GeomMathTest, Lerp_QuarterPoint)
{
    EXPECT_DOUBLE_EQ(GeomMath::lerp(0.0, 10.0, 0.25), 2.5);
}

// ==================== 角度工具测试 ====================

TEST(GeomMathTest, RadToDeg_Zero)
{
    EXPECT_DOUBLE_EQ(GeomMath::radToDeg(0.0), 0.0);
}

TEST(GeomMathTest, RadToDeg_Pi)
{
    EXPECT_NEAR(GeomMath::radToDeg(M_PI), 180.0, 1e-10);
}

TEST(GeomMathTest, RadToDeg_PiOver2)
{
    EXPECT_NEAR(GeomMath::radToDeg(M_PI / 2.0), 90.0, 1e-10);
}

TEST(GeomMathTest, DegToRad_Zero)
{
    EXPECT_DOUBLE_EQ(GeomMath::degToRad(0.0), 0.0);
}

TEST(GeomMathTest, DegToRad_180)
{
    EXPECT_NEAR(GeomMath::degToRad(180.0), M_PI, 1e-10);
}

TEST(GeomMathTest, DegToRad_90)
{
    EXPECT_NEAR(GeomMath::degToRad(90.0), M_PI / 2.0, 1e-10);
}

TEST(GeomMathTest, NormalizeAngle0To2Pi_Zero)
{
    EXPECT_DOUBLE_EQ(GeomMath::normalizeAngle0To2Pi(0.0), 0.0);
}

TEST(GeomMathTest, NormalizeAngle0To2Pi_Pi)
{
    EXPECT_NEAR(GeomMath::normalizeAngle0To2Pi(M_PI), M_PI, 1e-10);
}

TEST(GeomMathTest, NormalizeAngle0To2Pi_Negative)
{
    EXPECT_NEAR(GeomMath::normalizeAngle0To2Pi(-M_PI / 2.0), 3.0 * M_PI / 2.0, 1e-10);
}

TEST(GeomMathTest, NormalizeAngle0To2Pi_GreaterThan2Pi)
{
    EXPECT_NEAR(GeomMath::normalizeAngle0To2Pi(3.0 * M_PI), M_PI, 1e-10);
}

TEST(GeomMathTest, NormalizeAnglePiToPi_Zero)
{
    EXPECT_DOUBLE_EQ(GeomMath::normalizeAnglePiToPi(0.0), 0.0);
}

TEST(GeomMathTest, NormalizeAnglePiToPi_Pi)
{
    EXPECT_NEAR(GeomMath::normalizeAnglePiToPi(M_PI), -M_PI, 1e-10);
}

TEST(GeomMathTest, NormalizeAnglePiToPi_NegativePi)
{
    EXPECT_NEAR(GeomMath::normalizeAnglePiToPi(-M_PI), -M_PI, 1e-10);
}

TEST(GeomMathTest, NormalizeAnglePiToPi_GreaterThanPi)
{
    EXPECT_NEAR(GeomMath::normalizeAnglePiToPi(3.0 * M_PI / 2.0), -M_PI / 2.0, 1e-10);
}

TEST(GeomMathTest, AngleDiff_SameAngle)
{
    EXPECT_NEAR(GeomMath::angleDiff(M_PI / 4.0, M_PI / 4.0), 0.0, 1e-10);
}

TEST(GeomMathTest, AngleDiff_OppositeAngles)
{
    EXPECT_NEAR(GeomMath::angleDiff(M_PI, 0.0), M_PI, 1e-10);
    EXPECT_NEAR(GeomMath::angleDiff(0.0, M_PI), -M_PI, 1e-10);
}

TEST(GeomMathTest, AngleDiff_CrossingPi)
{
    EXPECT_NEAR(GeomMath::angleDiff(3.0 * M_PI / 4.0, -3.0 * M_PI / 4.0), -M_PI / 2.0, 1e-10);
}

// ==================== 区间判断测试 ====================

TEST(GeomMathTest, InRange_WithinRange)
{
    EXPECT_TRUE(GeomMath::inRange(5.0, 0.0, 10.0));
}

TEST(GeomMathTest, InRange_AtBoundary)
{
    EXPECT_TRUE(GeomMath::inRange(0.0, 0.0, 10.0));
    EXPECT_TRUE(GeomMath::inRange(10.0, 0.0, 10.0));
}

TEST(GeomMathTest, InRange_OutsideRange)
{
    EXPECT_FALSE(GeomMath::inRange(-1.0, 0.0, 10.0));
    EXPECT_FALSE(GeomMath::inRange(11.0, 0.0, 10.0));
}

TEST(GeomMathTest, InRange_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::inRange(-1e-10, 0.0, 10.0, 1e-9));
    EXPECT_TRUE(GeomMath::inRange(10.0 + 1e-10, 0.0, 10.0, 1e-9));
}

TEST(GeomMathTest, InRange01_WithinRange)
{
    EXPECT_TRUE(GeomMath::inRange01(0.5));
}

TEST(GeomMathTest, InRange01_AtBoundary)
{
    EXPECT_TRUE(GeomMath::inRange01(0.0));
    EXPECT_TRUE(GeomMath::inRange01(1.0));
}

TEST(GeomMathTest, InRange01_OutsideRange)
{
    EXPECT_FALSE(GeomMath::inRange01(-0.1));
    EXPECT_FALSE(GeomMath::inRange01(1.1));
}

TEST(GeomMathTest, InRange01_WithinTolerance)
{
    EXPECT_TRUE(GeomMath::inRange01(-1e-10, 1e-9));
    EXPECT_TRUE(GeomMath::inRange01(1.0 + 1e-10, 1e-9));
}

// ==================== 符号工具测试 ====================

TEST(GeomMathTest, Sign_Positive)
{
    EXPECT_EQ(GeomMath::sign(1.0), 1);
    EXPECT_EQ(GeomMath::sign(100.0), 1);
}

TEST(GeomMathTest, Sign_Negative)
{
    EXPECT_EQ(GeomMath::sign(-1.0), -1);
    EXPECT_EQ(GeomMath::sign(-100.0), -1);
}

TEST(GeomMathTest, Sign_Zero)
{
    EXPECT_EQ(GeomMath::sign(0.0), 0);
}

TEST(GeomMathTest, Sign_WithinTolerance)
{
    EXPECT_EQ(GeomMath::sign(1e-10, 1e-9), 0);
    EXPECT_EQ(GeomMath::sign(-1e-10, 1e-9), 0);
}

TEST(GeomMathTest, Sign_OutsideTolerance)
{
    EXPECT_EQ(GeomMath::sign(1e-8, 1e-9), 1);
    EXPECT_EQ(GeomMath::sign(-1e-8, 1e-9), -1);
}

// ==================== 边界情况测试 ====================

TEST(GeomMathTest, LargeValues)
{
    double large = 1e100;
    EXPECT_TRUE(GeomMath::almostEqual(large, large + 1e90, 1e91));
    EXPECT_FALSE(GeomMath::almostEqual(large, large + 1e92, 1e91));
}

TEST(GeomMathTest, SmallValues)
{
    double small = 1e-100;
    EXPECT_TRUE(GeomMath::isZero(small, 1e-99));
    EXPECT_FALSE(GeomMath::isZero(small, 1e-101));
}

TEST(GeomMathTest, NegativeValues)
{
    EXPECT_TRUE(GeomMath::lessOrEqual(-10.0, -5.0));
    EXPECT_TRUE(GeomMath::greaterOrEqual(-5.0, -10.0));
}

TEST(GeomMathTest, AngleWrapping)
{
    // 测试大角度归一化
    double largeAngle = 100.0 * M_PI;
    double normalized = GeomMath::normalizeAngle0To2Pi(largeAngle);
    EXPECT_GE(normalized, 0.0);
    EXPECT_LT(normalized, 2.0 * M_PI);
}
