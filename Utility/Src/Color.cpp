#include "Color/Color.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

namespace Ut
{
    static constexpr float EPS = 1.0f / 255.0f;

    Color::Color() : m_data{ 0.0f, 0.0f, 0.0f, 1.0f }
    {
    }

    Color::Color(float red, float green, float blue, float alpha)
        : m_data{
            std::clamp(red, 0.0f, 1.0f),
            std::clamp(green, 0.0f, 1.0f),
            std::clamp(blue, 0.0f, 1.0f),
            std::clamp(alpha, 0.0f, 1.0f)
        }
    {
    }

    bool Color::operator==(const Color& other) const
    {
        return std::fabs(m_data[0] - other.m_data[0]) < EPS &&
            std::fabs(m_data[1] - other.m_data[1]) < EPS &&
            std::fabs(m_data[2] - other.m_data[2]) < EPS &&
            std::fabs(m_data[3] - other.m_data[3]) < EPS;
    }

    bool Color::operator!=(const Color& other) const
    {
        return !(*this == other);
    }

    Color Color::operator+(const Color& other) const
    {
        return Color(
            std::clamp(m_data[0] + other.m_data[0], 0.0f, 1.0f),
            std::clamp(m_data[1] + other.m_data[1], 0.0f, 1.0f),
            std::clamp(m_data[2] + other.m_data[2], 0.0f, 1.0f),
            std::clamp(m_data[3] + other.m_data[3], 0.0f, 1.0f)
        );
    }

    Color Color::operator-(const Color& other) const
    {
        return Color(
            std::clamp(m_data[0] - other.m_data[0], 0.0f, 1.0f),
            std::clamp(m_data[1] - other.m_data[1], 0.0f, 1.0f),
            std::clamp(m_data[2] - other.m_data[2], 0.0f, 1.0f),
            std::clamp(m_data[3] - other.m_data[3], 0.0f, 1.0f)
        );
    }

    Color Color::operator*(float scalar) const
    {
        return Color(
            std::clamp(m_data[0] * scalar, 0.0f, 1.0f),
            std::clamp(m_data[1] * scalar, 0.0f, 1.0f),
            std::clamp(m_data[2] * scalar, 0.0f, 1.0f),
            std::clamp(m_data[3] * scalar, 0.0f, 1.0f)
        );
    }

    Color Color::operator/(float scalar) const
    {
        if (std::fabs(scalar) < 1e-6f)
        {
            throw std::invalid_argument("Division by zero or near-zero value");
        }
        return Color(
            std::clamp(m_data[0] / scalar, 0.0f, 1.0f),
            std::clamp(m_data[1] / scalar, 0.0f, 1.0f),
            std::clamp(m_data[2] / scalar, 0.0f, 1.0f),
            std::clamp(m_data[3] / scalar, 0.0f, 1.0f)
        );
    }

    Color Color::fromRGB255(int red, int green, int blue, int alpha)
    {
        return Color(
            std::clamp(red, 0, 255) / 255.0f,
            std::clamp(green, 0, 255) / 255.0f,
            std::clamp(blue, 0, 255) / 255.0f,
            std::clamp(alpha, 0, 255) / 255.0f
        );
    }

    Color Color::fromHex(const std::string& hex)
    {
        std::string strCleanHex = hex;

        // 移除#前缀
        if (!strCleanHex.empty() && strCleanHex[0] == '#')
        {
            strCleanHex = strCleanHex.substr(1);
        }

        // 验证长度
        if (strCleanHex.length() != 6 && strCleanHex.length() != 8)
        {
            throw std::invalid_argument("Hex string must be 6 or 8 characters long");
        }

        // 解析十六进制值
        unsigned int rgbValue;
        std::stringstream ss;
        ss << std::hex << strCleanHex;
        ss >> rgbValue;

        if (strCleanHex.length() == 6)
        {
            // #RRGGBB格式
            int r = (rgbValue >> 16) & 0xFF;
            int g = (rgbValue >> 8) & 0xFF;
            int b = rgbValue & 0xFF;
            return fromRGB255(r, g, b);
        }
        else
        {
            // #RRGGBBAA格式
            int r = (rgbValue >> 24) & 0xFF;
            int g = (rgbValue >> 16) & 0xFF;
            int b = (rgbValue >> 8) & 0xFF;
            int a = rgbValue & 0xFF;
            return fromRGB255(r, g, b, a);
        }
    }

    Color Color::fromHSV(float hue, float saturation, float value, float alpha)
    {
        float r, g, b;
        HSVtoRGB(hue, saturation, value, r, g, b);
        return Color(r, g, b, alpha);
    }

    Color Color::fromHSL(float hue, float saturation, float lightness, float alpha)
    {
        float r, g, b;
        HSLtoRGB(hue, saturation, lightness, r, g, b);
        return Color(r, g, b, alpha);
    }

    // ==================== 获取颜色分量实现 ====================

    float Color::red() const
    {
        return m_data[0];
    }

    float Color::green() const
    {
        return m_data[1];
    }

    float Color::blue() const
    {
        return m_data[2];
    }

    float Color::alpha() const
    {
        return m_data[3];
    }

    float Color::r() const
    {
        return m_data[0];
    }

    float Color::g() const
    {
        return m_data[1];
    }

    float Color::b() const
    {
        return m_data[2];
    }

    float Color::a() const
    {
        return m_data[3];
    }

    int Color::red255() const
    {
        return static_cast<int>(m_data[0] * 255.0f);
    }

    int Color::green255() const
    {
        return static_cast<int>(m_data[1] * 255.0f);
    }

    int Color::blue255() const
    {
        return static_cast<int>(m_data[2] * 255.0f);
    }

    int Color::alpha255() const
    {
        return static_cast<int>(m_data[3] * 255.0f);
    }

    void Color::getHSV(float& hue, float& saturation, float& value) const
    {
        RGBtoHSV(m_data[0], m_data[1], m_data[2], hue, saturation, value);
    }

    void Color::getHSL(float& hue, float& saturation, float& lightness) const
    {
        RGBtoHSL(m_data[0], m_data[1], m_data[2], hue, saturation, lightness);
    }

    float Color::hue() const
    {
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        return h;
    }

    float Color::saturation() const
    {
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        return s;
    }

    float Color::value() const
    {
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        return v;
    }

    float Color::hueHSL() const
    {
        float h, s, l;
        RGBtoHSL(m_data[0], m_data[1], m_data[2], h, s, l);
        return h;
    }

    float Color::saturationHSL() const
    {
        float h, s, l;
        RGBtoHSL(m_data[0], m_data[1], m_data[2], h, s, l);
        return s;
    }

    float Color::lightness() const
    {
        float h, s, l;
        RGBtoHSL(m_data[0], m_data[1], m_data[2], h, s, l);
        return l;
    }

    // ==================== 设置颜色分量实现 ====================
    void Color::setRGBA(float r, float g, float b, float a /*=1.0*/)
    {
        m_data[0] = std::clamp(r, 0.0f, 1.0f);
        m_data[1] = std::clamp(g, 0.0f, 1.0f);
        m_data[2] = std::clamp(b, 0.0f, 1.0f);
        m_data[3] = std::clamp(a, 0.0f, 1.0f);
    }

    void Color::setRed(float red)
    {
        m_data[0] = std::clamp(red, 0.0f, 1.0f);
    }

    void Color::setGreen(float green)
    {
        m_data[1] = std::clamp(green, 0.0f, 1.0f);
    }

    void Color::setBlue(float blue)
    {
        m_data[2] = std::clamp(blue, 0.0f, 1.0f);
    }

    void Color::setAlpha(float alpha)
    {
        m_data[3] = std::clamp(alpha, 0.0f, 1.0f);
    }

    void Color::setRGBA255(int r, int g, int b, int a /*=255*/)
    {
        m_data[0] = std::clamp(r, 0, 255) / 255.0f;
        m_data[1] = std::clamp(g, 0, 255) / 255.0f;
        m_data[2] = std::clamp(b, 0, 255) / 255.0f;
        m_data[3] = std::clamp(a, 0, 255) / 255.0f;
    }

    void Color::setRed255(int red)
    {
        m_data[0] = std::clamp(red, 0, 255) / 255.0f;
    }

    void Color::setGreen255(int green)
    {
        m_data[1] = std::clamp(green, 0, 255) / 255.0f;
    }

    void Color::setBlue255(int blue)
    {
        m_data[2] = std::clamp(blue, 0, 255) / 255.0f;
    }

    void Color::setAlpha255(int alpha)
    {
        m_data[3] = std::clamp(alpha, 0, 255) / 255.0f;
    }

    void Color::setHSV(float hue, float saturation, float value)
    {
        HSVtoRGB(hue, saturation, value, m_data[0], m_data[1], m_data[2]);
    }

    void Color::setHSL(float hue, float saturation, float lightness)
    {
        HSLtoRGB(hue, saturation, lightness, m_data[0], m_data[1], m_data[2]);
    }

    // ==================== 颜色操作实现 ====================

    Color Color::blend(const Color& other, float factor) const
    {
        factor = std::clamp(factor, 0.0f, 1.0f);
        return Color(
            m_data[0] * (1.0f - factor) + other.m_data[0] * factor,
            m_data[1] * (1.0f - factor) + other.m_data[1] * factor,
            m_data[2] * (1.0f - factor) + other.m_data[2] * factor,
            m_data[3] * (1.0f - factor) + other.m_data[3] * factor
        );
    }

    Color Color::lighten(float factor) const
    {
        factor = std::clamp(factor, 0.0f, 1.0f);
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        v = std::clamp(v + factor, 0.0f, 1.0f);
        return fromHSV(h, s, v, m_data[3]);
    }

    Color Color::darken(float factor) const
    {
        factor = std::clamp(factor, 0.0f, 1.0f);
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        v = std::clamp(v - factor, 0.0f, 1.0f);
        return fromHSV(h, s, v, m_data[3]);
    }

    Color Color::saturate(float factor) const
    {
        factor = std::clamp(factor, 0.0f, 1.0f);
        float h, s, v;
        RGBtoHSV(m_data[0], m_data[1], m_data[2], h, s, v);
        s = std::clamp(s + factor, 0.0f, 1.0f);
        return fromHSV(h, s, v, m_data[3]);
    }

    Color Color::fade(float factor) const
    {
        factor = std::clamp(factor, 0.0f, 1.0f);
        return Color(m_data[0], m_data[1], m_data[2], m_data[3] * factor);
    }

    float Color::luminance() const
    {
        return 0.299f * m_data[0] + 0.587f * m_data[1] + 0.114f * m_data[2];
    }

    float Color::contrast(const Color& other) const
    {
        float l1 = luminance();
        float l2 = other.luminance();

        if (l1 > l2)
        {
            return (l1 + 0.05f) / (l2 + 0.05f);
        }
        else
        {
            return (l2 + 0.05f) / (l1 + 0.05f);
        }
    }

    // ==================== 颜色索引功能实现 ====================

    uint32_t Color::toIndex() const
    {
        uint32_t r = static_cast<uint32_t>(m_data[0] * 255.0f);
        uint32_t g = static_cast<uint32_t>(m_data[1] * 255.0f);
        uint32_t b = static_cast<uint32_t>(m_data[2] * 255.0f);
        uint32_t a = static_cast<uint32_t>(m_data[3] * 255.0f);

        return (r << 24) | (g << 16) | (b << 8) | a;
    }

    Color Color::fromIndex(uint32_t index)
    {
        uint32_t r = (index >> 24) & 0xFF;
        uint32_t g = (index >> 16) & 0xFF;
        uint32_t b = (index >> 8) & 0xFF;
        uint32_t a = index & 0xFF;

        return Color(
            r / 255.0f,
            g / 255.0f,
            b / 255.0f,
            a / 255.0f
        );
    }

    size_t Color::hash() const
    {
        size_t h1 = std::hash<uint32_t>{}(static_cast<uint32_t>(m_data[0] * 255.0f));
        size_t h2 = std::hash<uint32_t>{}(static_cast<uint32_t>(m_data[1] * 255.0f));
        size_t h3 = std::hash<uint32_t>{}(static_cast<uint32_t>(m_data[2] * 255.0f));
        size_t h4 = std::hash<uint32_t>{}(static_cast<uint32_t>(m_data[3] * 255.0f));

        size_t seed = 0;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }

    uint8_t Color::toPaletteIndex() const
    {
        float gray = 0.299f * m_data[0] + 0.587f * m_data[1] + 0.114f * m_data[2];
        return static_cast<uint8_t>(gray * 255.0f);
    }

    // ==================== 预定义颜色实现 ====================

    Color Color::Black()
    {
        return Color(0.0f, 0.0f, 0.0f);
    }

    Color Color::White()
    {
        return Color(1.0f, 1.0f, 1.0f);
    }

    Color Color::Red()
    {
        return Color(1.0f, 0.0f, 0.0f);
    }

    Color Color::Green()
    {
        return Color(0.0f, 1.0f, 0.0f);
    }

    Color Color::Blue()
    {
        return Color(0.0f, 0.0f, 1.0f);
    }

    Color Color::Yellow()
    {
        return Color(1.0f, 1.0f, 0.0f);
    }

    Color Color::Magenta()
    {
        return Color(1.0f, 0.0f, 1.0f);
    }

    Color Color::Cyan()
    {
        return Color(0.0f, 1.0f, 1.0f);
    }

    Color Color::Gray()
    {
        return Color(0.5f, 0.5f, 0.5f);
    }

    Color Color::Transparent()
    {
        return Color(0.0f, 0.0f, 0.0f, 0.0f);
    }

    // ==================== 转换方法实现 ====================

    std::string Color::toHexRGB() const
    {
        std::stringstream ss;
        ss << "#" << std::hex << std::setfill('0') << std::setw(2) << red255()
            << std::setw(2) << green255() << std::setw(2) << blue255();
        return ss.str();
    }

    std::string Color::toHexRGBA() const
    {
        std::stringstream ss;
        ss << "#" << std::hex << std::setfill('0') << std::setw(2) << red255()
            << std::setw(2) << green255() << std::setw(2) << blue255()
            << std::setw(2) << alpha255();
        return ss.str();
    }

    std::string Color::toCSS() const
    {
        std::stringstream ss;
        ss << "rgba(" << red255() << ", " << green255() << ", " << blue255()
            << ", " << a() << ")";
        return ss.str();
    }

    // ==================== OpenGL相关方法实现 ====================

    const float* Color::data() const
    {
        return m_data;
    }

    float* Color::data()
    {
        return m_data;
    }

    std::array<float, 4> Color::toArray() const
    {
        return { m_data[0], m_data[1], m_data[2], m_data[3] };
    }

    void Color::toGLFloatArray(float* array) const
    {
        array[0] = m_data[0];
        array[1] = m_data[1];
        array[2] = m_data[2];
        array[3] = m_data[3];
    }

    // ==================== HSV/HSL转换函数实现 ====================

    void Color::RGBtoHSV(float r, float g, float b, float& h, float& s, float& v)
    {
        float min = std::min(std::min(r, g), b);
        float max = std::max(std::max(r, g), b);
        float delta = max - min;

        v = max;

        if (max == 0.0f)
        {
            s = 0.0f;
            h = 0.0f;
            return;
        }

        s = delta / max;

        if (delta == 0.0f)
        {
            h = 0.0f;
        }
        else if (max == r)
        {
            h = 60.0f * ((g - b) / delta);
        }
        else if (max == g)
        {
            h = 60.0f * ((b - r) / delta + 2.0f);
        }
        else
        {
            h = 60.0f * ((r - g) / delta + 4.0f);
        }

        if (h < 0.0f)
        {
            h += 360.0f;
        }
    }

    void Color::HSVtoRGB(float h, float s, float v, float& r, float& g, float& b)
    {
        h = std::fmod(h, 360.0f);
        if (h < 0.0f) h += 360.0f;
        s = std::clamp(s, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        float c = v * s;
        float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = v - c;

        if (h < 60.0f)
        {
            r = c; g = x; b = 0.0f;
        }
        else if (h < 120.0f)
        {
            r = x; g = c; b = 0.0f;
        }
        else if (h < 180.0f)
        {
            r = 0.0f; g = c; b = x;
        }
        else if (h < 240.0f)
        {
            r = 0.0f; g = x; b = c;
        }
        else if (h < 300.0f)
        {
            r = x; g = 0.0f; b = c;
        }
        else
        {
            r = c; g = 0.0f; b = x;
        }

        r += m;
        g += m;
        b += m;
    }

    void Color::RGBtoHSL(float r, float g, float b, float& h, float& s, float& l)
    {
        float min = std::min(std::min(r, g), b);
        float max = std::max(std::max(r, g), b);
        float delta = max - min;

        l = (max + min) / 2.0f;

        if (delta == 0.0f)
        {
            h = 0.0f;
            s = 0.0f;
            return;
        }

        if (l < 0.5f)
        {
            s = delta / (max + min);
        }
        else
        {
            s = delta / (2.0f - max - min);
        }

        if (max == r)
        {
            h = 60.0f * ((g - b) / delta);
        }
        else if (max == g)
        {
            h = 60.0f * ((b - r) / delta + 2.0f);
        }
        else
        {
            h = 60.0f * ((r - g) / delta + 4.0f);
        }

        if (h < 0.0f)
        {
            h += 360.0f;
        }
    }

    void Color::HSLtoRGB(float h, float s, float l, float& r, float& g, float& b)
    {
        h = std::fmod(h, 360.0f);
        if (h < 0.0f) h += 360.0f;
        s = std::clamp(s, 0.0f, 1.0f);
        l = std::clamp(l, 0.0f, 1.0f);

        float c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
        float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = l - c / 2.0f;

        if (h < 60.0f)
        {
            r = c; g = x; b = 0.0f;
        }
        else if (h < 120.0f)
        {
            r = x; g = c; b = 0.0f;
        }
        else if (h < 180.0f)
        {
            r = 0.0f; g = c; b = x;
        }
        else if (h < 240.0f)
        {
            r = 0.0f; g = x; b = c;
        }
        else if (h < 300.0f)
        {
            r = x; g = 0.0f; b = c;
        }
        else
        {
            r = c; g = 0.0f; b = x;
        }

        r += m;
        g += m;
        b += m;
    }
}