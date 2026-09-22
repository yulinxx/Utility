#pragma once
/**
 * @file VertexFormat.hpp
 * @brief 统一顶点格式定义（单一数据源）
 *
 * ## 设计目标
 *
 * 此前顶点格式在多处重复定义：
 * - RenderAbstraction::IRenderTypes.h (枚举)
 * - UI/Common/Render/RenderTypes.h (VertexP3C3, VertexP3C4...)
 * - Engine2D/Render/DisplayMesh.h (DisplayVertex)
 * - Utility/Ut/RenderData.h (RenderVertex, MeshVertex)
 *
 * 此文件作为**唯一数据源**，定义所有预定义顶点格式。
 * 各层按需引用，避免同步更新遗漏。
 *
 * ## 使用方式
 *
 * ```cpp
 * #include "Ut/VertexFormat.hpp"
 *
 * // 使用预定义结构
 * std::vector<Ut::VertexP3C3> vertices;
 * vertices.push_back({1.0f, 2.0f, 3.0f, 1.0f, 0.0f, 0.0f});
 *
 * // 使用字节步长（与 RenderAbstraction::vertexStride 保持一致）
 * constexpr size_t stride = sizeof(Ut::VertexP3C3);  // 24 字节
 * ```
 *
 * ## 布局约定
 *
 * - 所有字段均为 float (32-bit)
 * - 字节步长必须与 RenderAbstraction::vertexStride() 返回值一致
 * - static_assert 用于锁定布局，防止意外变更
 */

#include "UtilityAPI.h"
#include <cstdint>
#include <cstddef>

namespace Ut
{
    // ==================== 顶点格式枚举 ====================
    // 与 RenderAbstraction::VertexFormat 保持一致
    // 仅供需要动态格式的场景使用，预定义结构体更推荐

    enum class VertexFormat : uint8_t
    {
        PositionColor,        // 位置float3 + 颜色float3 = 24字节
        PositionColorAlpha,   // 位置float3 + 颜色float4 = 28字节
        PositionNormal,       // 位置float3 + 法线float3 = 24字节
        PositionUVColor,     // 位置float2 + UVfloat2 + 颜色float4 = 32字节
        WorldPosUVColor,      // 位置float3 + UVfloat2 + 颜色float4 = 36字节
        WorldAnchorOffsetColor, // 世界锚点float3 + 像素偏移float2 + 颜色float4 = 36字节
        WorldPosTexColor      // 位置float3 + 纹理坐标float2 + 颜色float4 = 36字节
    };

    /**
     * @brief 顶点格式的字节步长
     *
     * 与 RenderAbstraction::vertexStride() 返回值保持一致。
     * 使用此函数可避免硬编码数值，同时确保与渲染后端兼容。
     */
    inline constexpr uint32_t vertexStride(VertexFormat fmt)
    {
        switch (fmt)
        {
        case VertexFormat::PositionColor:          return 24;  // float3 + float3
        case VertexFormat::PositionColorAlpha:     return 28;  // float3 + float4
        case VertexFormat::PositionNormal:         return 24;  // float3 + float3
        case VertexFormat::PositionUVColor:        return 32;  // float2 + float2 + float4
        case VertexFormat::WorldPosUVColor:        return 36;  // float3 + float2 + float4
        case VertexFormat::WorldAnchorOffsetColor: return 36;  // float3 + float2 + float4
        case VertexFormat::WorldPosTexColor:       return 36;  // float3 + float2 + float4
        }
        return 0;
    }

    // ==================== 预定义顶点结构 ====================
    // 每个结构体对应一种 VertexFormat，字节布局必须与 vertexStride() 一致

    /**
     * @brief 位置 + RGB颜色 (对应 VertexFormat::PositionColor)
     *
     * 布局: px, py, pz, cr, cg, cb
     * 步长: 24 字节
     * 用途: 2D/3D 通用几何，无光照
     */
    struct VertexP3C3
    {
        float px, py, pz;    // 位置
        float cr, cg, cb;    // 颜色 (RGB)
    };

    static_assert(sizeof(VertexP3C3) == 24,
        "VertexP3C3 必须与 vertexStride(PositionColor) 一致");

    /**
     * @brief 位置 + RGBA颜色 (对应 VertexFormat::PositionColorAlpha)
     *
     * 布局: px, py, pz, cr, cg, cb, ca
     * 步长: 28 字节
     * 用途: 覆盖层、透明度图元
     */
    struct VertexP3C4
    {
        float px, py, pz;            // 位置
        float cr, cg, cb, ca;        // 颜色 (RGBA)
    };

    static_assert(sizeof(VertexP3C4) == 28,
        "VertexP3C4 必须与 vertexStride(PositionColorAlpha) 一致");

    /**
     * @brief 位置 + 法线 (对应 VertexFormat::PositionNormal)
     *
     * 布局: px, py, pz, nx, ny, nz
     * 步长: 24 字节
     * 用途: 3D 网格，带光照
     */
    struct VertexP3N3
    {
        float px, py, pz;    // 位置
        float nx, ny, nz;    // 法线
    };

    static_assert(sizeof(VertexP3N3) == 24,
        "VertexP3N3 必须与 vertexStride(PositionNormal) 一致");

    /**
     * @brief 位置 + UV + RGBA颜色 (对应 VertexFormat::PositionUVColor)
     *
     * 布局: px, py, u, v, cr, cg, cb, ca
     * 步长: 32 字节
     * 用途: 屏幕空间贴图
     */
    struct VertexP2T2C4
    {
        float px, py;                // 位置 (屏幕空间)
        float u, v;                  // 纹理坐标
        float cr, cg, cb, ca;        // 颜色 (RGBA)
    };

    static_assert(sizeof(VertexP2T2C4) == 32,
        "VertexP2T2C4 必须与 vertexStride(PositionUVColor) 一致");

    /**
     * @brief 世界位置 + UV + RGBA颜色 (对应 VertexFormat::WorldPosUVColor)
     *
     * 布局: px, py, pz, u, v, cr, cg, cb, ca
     * 步长: 36 字节
     * 用途: 世界空间贴图
     */
    struct VertexP3T2C4
    {
        float px, py, pz;            // 位置 (世界空间)
        float u, v;                  // 纹理坐标
        float cr, cg, cb, ca;        // 颜色 (RGBA)
    };

    static_assert(sizeof(VertexP3T2C4) == 36,
        "VertexP3T2C4 必须与 vertexStride(WorldPosUVColor) 一致");

    /**
     * @brief 世界锚点 + 像素偏移 + RGBA颜色 (对应 VertexFormat::WorldAnchorOffsetColor)
     *
     * 布局: ax, ay, az, ox, oy, cr, cg, cb, ca
     * 步长: 36 字节
     * 用途: 跟随平移但不跟随缩放的标记类图元（点标记、手柄、捕捉圈等）
     *
     * 渲染层会把 anchor 视为世界坐标，offsetPx 相对锚点的像素偏移，
     * 换算在顶点着色器里做，实现恒定物理尺寸。
     */
    struct VertexP3O2C4
    {
        float ax, ay, az;            // 世界锚点
        float ox, oy;                // 像素偏移
        float cr, cg, cb, ca;        // 颜色 (RGBA)
    };

    static_assert(sizeof(VertexP3O2C4) == 36,
        "VertexP3O2C4 必须与 vertexStride(WorldAnchorOffsetColor) 一致");

    /**
     * @brief 世界位置 + 纹理坐标 + 颜色 (对应 VertexFormat::WorldPosTexColor)
     *
     * 布局: px, py, pz, u, v, cr, cg, cb, ca
     * 步长: 36 字节
     * 用途: 世界空间纹理映射
     */
    struct VertexP3T2C4_Textured
    {
        float px, py, pz;            // 位置 (世界空间)
        float u, v;                   // 纹理坐标
        float cr, cg, cb, ca;        // 颜色 (RGBA)
    };

    static_assert(sizeof(VertexP3T2C4_Textured) == 36,
        "VertexP3T2C4_Textured 必须与 vertexStride(WorldPosTexColor) 一致");

}  // namespace Ut
