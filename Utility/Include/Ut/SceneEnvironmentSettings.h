#pragma once

#include "Vec.h"
#include "Color/Color.hpp"
#include <array>

namespace Ut
{
    /**
     * @brief 工作台面设置
     *
     * 数据结构 —— Engine 持有，Render 只读。
     * 颜色默认全部留黑，真实默认值由 Engine::SceneEnvironment 构造时设置，
     * 以避免 "int 被误解为 0~1 float" 之类的颜色构造歧义。
     */
    struct TableSettings
    {
        float width = 1200.0f;  // 台面宽（毫米）
        float height = 800.0f;  // 台面高（毫米）

        Ut::Color outerColor;    // 台面外背景色
        Ut::Color surfaceColor;  // 台面底色
        Ut::Color borderColor;   // 边框颜色
        float borderWidthPx = 1.5f;

        bool visible = true;

        float outerZ = -1.0f;
        float surfaceZ = -0.8f;
        float borderZ = -0.4f;
    };

    /**
     * @brief 网格设置
     */
    struct GridSettings
    {
        bool visible = true;

        Ut::Color majorColor;
        Ut::Color minorColor;
        float majorLineWidth = 1.0f;
        float minorLineWidth = 1.0f;
        float targetMajorPx = 100.0f;

        /// 网格密度因子：1.0 默认，>1 更疏，<1 更密
        float gridDensity = 1.0f;

        float minorZ = -0.6f;
        float majorZ = -0.4f;
    };

    /**
     * @brief 标尺位置
     */
    enum class RulerPosition : unsigned char
    {
        Top = 0,
        Left,
    };

    /**
     * @brief 单个标尺设置（顶部或左侧）
     */
    struct RulerSettings
    {
        bool visible = true;
        int thicknessPx = 36;
        Ut::Color bgColor;
        Ut::Color tickColor;
        Ut::Color textColor;
        Ut::Color borderColor;

        int fontSizePt = 10;
        int majorTickLen = 10;
        int minorTickLen = 6;
        int mediumTickLen = 8;
        float tickLineWidthPx = 1.0f;

        float bgZ = 0.0f;
        float tickZ = 0.2f;
        float borderZ = 0.25f;

        RulerPosition position = RulerPosition::Top;
    };

    /**
     * @brief 整体场景环境配置
     */
    struct SceneEnvironmentSettings
    {
        TableSettings table;
        GridSettings grid;
        RulerSettings topRuler;
        RulerSettings leftRuler;
    };
}  // namespace Ut
