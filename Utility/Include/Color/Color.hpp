#pragma once

#include "UtilityAPI.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <array>
#include <string>
#include <cstdint>

namespace Ut
{
    /**
     * @brief 颜色类，支持RGBA格式，多种输入范围
     * @details OpenGL使用的范围为0-1
     */
    class UTILITY_API Color
    {
    public:
        /// 默认构造函数，创建黑色不透明颜色
        Color();

        /// 从0-1范围的浮点数创建颜色
        Color(float red, float green, float blue, float alpha = 1.0f);

        // ==================== 运算符重载 ====================
        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const;
        Color operator+(const Color& other) const;
        Color operator-(const Color& other) const;
        Color operator*(float scalar) const;
        Color operator/(float scalar) const;

    public:
        // ==================== 颜色创建 ====================
        /// 从0-255范围的整数创建颜色 (带边界检查)
        static Color fromRGB255(int red, int green, int blue, int alpha = 255);

        /// 从十六进制字符串创建颜色 (支持 #RRGGBB 和 #RRGGBBAA 格式)
        static Color fromHex(const std::string& hex);

        /// 从HSV颜色空间创建颜色
        static Color fromHSV(float hue, float saturation, float value, float alpha = 1.0f);

        /// 从HSL颜色空间创建颜色
        static Color fromHSL(float hue, float saturation, float lightness, float alpha = 1.0f);

        // ==================== 获取颜色分量 ====================

        /// 获取0-1范围的红、绿、蓝、透明度分量
        float red() const;
        float green() const;
        float blue() const;
        float alpha() const;

        /// 对上面函数名称的(简写)
        float r() const;
        float g() const;
        float b() const;
        float a() const;

        /// 获取0-255范围的红色、绿色、蓝色、透明度分量
        int red255() const;
        int green255() const;
        int blue255() const;
        int alpha255() const;

        /// 获取HSV颜色空间的色相、饱和度、明度
        void getHSV(float& hue, float& saturation, float& value) const;
        /// 获取HSL颜色空间的色相、饱和度、亮度
        void getHSL(float& hue, float& saturation, float& lightness) const;

        /// 获取HSV颜色空间的色相 (0-360度)
        float hue() const;
        /// 获取HSV颜色空间的饱和度 (0-1)
        float saturation() const;
        /// 获取HSV颜色空间的明度 (0-1)
        float value() const;

        /// 获取HSL颜色空间的色相 (0-360度)
        float hueHSL() const;
        /// 获取HSL颜色空间的饱和度 (0-1)
        float saturationHSL() const;
        /// 获取HSL颜色空间的亮度 (0-1)
        float lightness() const;

        // ==================== 设置颜色分量 ====================

        /// 设置0-1范围的红、绿、蓝、透明度分量
        void setRGBA(float r, float g, float b, float a = 1.0);
        void setRed(float red);
        void setGreen(float green);
        void setBlue(float blue);
        void setAlpha(float alpha);

        /// 设置0-255范围的红、绿、蓝、透明度分量
        void setRGBA255(int r, int g, int b, int a = 255);
        void setRed255(int red);
        void setGreen255(int green);
        void setBlue255(int blue);
        void setAlpha255(int alpha);

        /// 设置HSV颜色空间的色相、饱和度、明度
        void setHSV(float hue, float saturation, float value);
        /// 设置HSL颜色空间的色相、饱和度、亮度
        void setHSL(float hue, float saturation, float lightness);

        // ==================== 颜色操作 ====================

        /// 颜色混合 (线性插值)
        Color blend(const Color& other, float factor) const;

        /// 颜色变亮、变暗
        Color lighten(float factor) const;
        Color darken(float factor) const;

        /// 调整饱和度
        Color saturate(float factor) const;
        /// 调整透明度
        Color fade(float factor) const;

        /// 计算亮度 (0-1)
        float luminance() const;

        /// 计算与另一个颜色的对比度
        float contrast(const Color& other) const;

        // ==================== 颜色索引功能 ====================

        /// 将RGBA值转换为唯一的整数索引 (0-4294967295范围)
        uint32_t toIndex() const;

        /// 通过索引值创建颜色 (0-4294967295范围)
        static Color fromIndex(uint32_t index);

        /// 将RGBA值转换为哈希值
        size_t hash() const;

        /// 获取颜色在0-255范围内的简化索引 (用于调色板)
        uint8_t toPaletteIndex() const;

        // ==================== 预定义颜色 ====================
        static Color Black();
        static Color White();
        static Color Red();
        static Color Green();
        static Color Blue();
        static Color Yellow();
        static Color Magenta();
        static Color Cyan();
        static Color Gray();
        static Color Transparent();

        // ==================== 转换方法 ====================
        /// 转换为十六进制字符串 (#RRGGBB格式)
        std::string toHexRGB() const;
        /// 转换为十六进制字符串 (#RRGGBBAA格式)
        std::string toHexRGBA() const;

        /// 转换为CSS rgba格式字符串
        std::string toCSS() const;

        // ==================== OpenGL相关方法 ====================
        const float* data() const;
        float* data();

        /// 获取OpenGL可用的4元素数组
        std::array<float, 4> toArray() const;

        /// 转换为OpenGL可用的向量格式
        void toGLFloatArray(float* array) const;

    private:
        // HSV/HSL转换函数
        static void RGBtoHSV(float r, float g, float b, float& h, float& s, float& v);
        static void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b);
        static void RGBtoHSL(float r, float g, float b, float& h, float& s, float& l);
        static void HSLtoRGB(float h, float s, float l, float& r, float& g, float& b);

    private:
        float m_data[4];  // RGBA分量数组，[r, g, b, a]
    };
}  // namespace Ut