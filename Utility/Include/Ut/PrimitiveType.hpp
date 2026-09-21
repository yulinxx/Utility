#pragma once
/**
 * @file PrimitiveType.hpp
 * @brief 统一图元类型枚举（单一数据源）
 *
 * ## 设计目标
 *
 * 此前图元类型枚举在多处重复定义：
 * - RenderAbstraction::IRenderTypes.h (PrimitiveType)
 * - UI/Common/Render/RenderTypes.h (Render::PrimitiveType)
 * - Engine2D/Render/DisplayMesh.h (EDisplayPrimitiveType)
 * - Engine2D/Render/Tessellator.h (TessellatedEntity::PrimitiveType)
 * - Utility/Ut/RenderData.h (RenderPrimitiveType)
 *
 * 此文件作为**唯一数据源**，定义所有图元类型。
 * 各层通过 using 或 enum class 转发来引用，避免重复定义。
 *
 * ## 布局约定
 *
 * - 使用 uint8_t 底层类型，确保跨 DLL 兼容
 * - TriangleFan 保留用于 CAD 扇形填充（Metal/Vulkan 不支持，需在应用层展开）
 */

#include "UtilityAPI.h"
#include <cstdint>

namespace Ut
{
    /**
     * @brief 统一图元类型枚举
     *
     * ## 与其他层的关系
     *
     * - RenderAbstraction::PrimitiveType: 转发此枚举
     * - Render::PrimitiveType: 转发此枚举
     * - Tessellator: 使用此枚举，展开 TriangleFan 为 TriangleList
     * - RenderX: 转换为后端原语（Metal/Vulkan 展开 TriangleFan）
     *
     * ## 数值约定
     *
     * 数值与 RenderAbstraction::PrimitiveType 保持一致，
     * 确保直接映射无需转换。
     */
    enum class PrimitiveType : uint8_t
    {
        Points        = 0,
        Lines         = 1,
        LineStrip     = 2,
        LineLoop      = 3,
        Triangles     = 4,
        TriangleStrip = 5,
        TriangleFan   = 6   // CAD 专用，需展开为 TriangleList
    };

    /// 图元类型总数
    constexpr uint32_t PRIMITIVE_TYPE_COUNT = 7;

    /**
     * @brief 检查图元类型是否为需要展开的类型
     *
     * TriangleFan 在某些渲染后端（Metal/Vulkan）不支持，
     * 需要在提交前展开为 TriangleList。
     */
    inline constexpr bool requiresExpansion(PrimitiveType type)
    {
        return type == PrimitiveType::TriangleFan;
    }

    /**
     * @brief 将需要展开的类型转换为可支持的类型
     *
     * TriangleFan -> Triangles
     * 其他类型保持不变
     */
    inline constexpr PrimitiveType expandPrimitiveType(PrimitiveType type)
    {
        return (type == PrimitiveType::TriangleFan) ? PrimitiveType::Triangles : type;
    }

}  // namespace Ut
