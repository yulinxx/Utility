#pragma once

#include "EngineAPI.h"
#include "Ut/Vec.h"
#include "Ut/Color.h"

#include <string>

namespace Ut
{
    /**
     * @brief UI 文字的坐标/定位模式。
     *
     * UI 文字的大小始终保持为"像素大小"（不随视图缩放），
     * 但定位锚点的参照系可以不同：
     */
    enum class UiTextCoordMode : unsigned char
    {
        /// 像素坐标：锚点 (x, y) 直接解释为屏幕像素坐标 (0~vpW, 0~vpH)，
        /// 原点在左上角，Y 向下。用于屏幕固定的文字（坐标提示、状态信息等）。
        PixelCoords = 0,

        /// 世界坐标定位，像素大小：锚点 (x, y) 是世界坐标值，
        /// 文字会跟随视图平移，但其字号/大小始终固定（像素级别）。
        /// 用于标尺刻度数字、测量标注、物体标签等。
        WorldPos_PixelSize = 1,
    };

    /**
     * @brief UI 文字对齐方式（相对锚点的偏移）
     */
    enum class UiTextHAlign : unsigned char
    {
        Left = 0,
        Center = 1,
        Right = 2,
    };

    enum class UiTextVAlign : unsigned char
    {
        Top = 0,
        Middle = 1,
        Bottom = 2,
    };

    /**
     * @brief 单个 UI 文字项。
     *
     * Render 层在 paintEvent 中使用 QPainter 绘制这些文字，
     * 保证：
     *   1. 文字大小始终是像素尺寸（不随视图缩放变化）
     *   2. 文字位置由 coordMode 决定是屏幕像素锚点还是世界锚点
     */
    struct ENGINE_API UiTextItem
    {
        std::string        text;
        float              x = 0.0f;   ///< 锚点 X（像素或世界坐标，取决于 coordMode）
        float              y = 0.0f;   ///< 锚点 Y（像素或世界坐标，取决于 coordMode）
        UiTextCoordMode    coordMode = UiTextCoordMode::PixelCoords;
        UiTextHAlign       hAlign = UiTextHAlign::Left;
        UiTextVAlign       vAlign = UiTextVAlign::Top;
        int                fontSize = 10;     ///< 字号（像素）
        Ut::Color          color;             ///< 文字颜色
        float              rotationDeg = 0.0f;///< 文字旋转角度（度，逆时针为正，仅用于世界坐标文字）
        float              zOrder = 0.0f;   ///< 绘制顺序（大的在上层）

        /// 可选的背景框
        bool               hasBackground = false;
        Ut::Color          bgColor;
        float              bgPaddingX = 2.0f;   ///< 背景左右内边距（像素）
        float              bgPaddingY = 1.0f;   ///< 背景上下内边距（像素）
        float              bgRadius = 0.0f;   ///< 背景圆角半径（像素），0=直角

        /// 可选的指向线（用于世界坐标文字的指示线，从锚点到文字框边缘）
        bool               hasLeaderLine = false;
        Ut::Color          leaderLineColor;
        float              leaderLineWidth = 1.0f;
    };

    /// UI 文字集合
    using UiTextItemList = std::vector<UiTextItem>;
}
