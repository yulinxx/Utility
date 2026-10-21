/**
 * @file ColorTests.cpp
 * @brief Ut::Color 单元测试 —— 重点覆盖 fromHex 的非法输入路径
 *
 * 历史缺陷：fromHex 用 stringstream 解析，"gggggg" 之类非法字符使
 * 流失败位竖起、rgbValue 保持未初始化，随后的位移读是 UB。
 * 修复后：先全量验字符再 stoul，非法字符与长度不符一样抛
 * std::invalid_argument。
 */
#include <gtest/gtest.h>

#include "Color/Color.hpp"

#include <stdexcept>

// ==================== fromHex 合法输入 ====================

TEST(ColorFromHexTest, SixDigitsProducesOpaqueColor)
{
    const Ut::Color c = Ut::Color::fromHex("#FF8000");
    EXPECT_FLOAT_EQ(c.r(), 1.0f);
    EXPECT_FLOAT_EQ(c.g(), 128.0f / 255.0f);
    EXPECT_FLOAT_EQ(c.b(), 0.0f);
    EXPECT_FLOAT_EQ(c.a(), 1.0f);
}

TEST(ColorFromHexTest, EightDigitsCarriesAlpha)
{
    const Ut::Color c = Ut::Color::fromHex("#11223344");
    EXPECT_FLOAT_EQ(c.a(), 68.0f / 255.0f);
}

TEST(ColorFromHexTest, MissingHashPrefixIsAccepted)
{
    EXPECT_NO_THROW(Ut::Color::fromHex("AABBCC"));
}

// ==================== fromHex 非法输入：必须抛，不得 UB ====================

TEST(ColorFromHexTest, NonHexCharactersThrowInvalidArgument)
{
    // 旧实现：解析失败 → rgbValue 未初始化 → UB。现在必须确定性抛出。
    EXPECT_THROW(Ut::Color::fromHex("gggggg"), std::invalid_argument);
    EXPECT_THROW(Ut::Color::fromHex("#GGGGGG"), std::invalid_argument);
    // 空格也不合法（旧 stream 会静默截断在空格处）
    EXPECT_THROW(Ut::Color::fromHex("12 456"), std::invalid_argument);
    EXPECT_THROW(Ut::Color::fromHex("#123 56"), std::invalid_argument);
}

TEST(ColorFromHexTest, WrongLengthThrowsInvalidArgument)
{
    EXPECT_THROW(Ut::Color::fromHex("#12345"), std::invalid_argument);    // 5 位
    EXPECT_THROW(Ut::Color::fromHex("#1234567"), std::invalid_argument);  // 7 位
    EXPECT_THROW(Ut::Color::fromHex(""), std::invalid_argument);
    EXPECT_THROW(Ut::Color::fromHex("#"), std::invalid_argument);
}