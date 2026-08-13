#pragma once

#include "Vec.h"
#include <cstddef>
#include <vector>

/**
 * @brief 渲染数据传输结构 (2D + 3D)
 */

namespace Ut
{
    // ==================== 图元渲染类型 ====================

    enum class RenderPrimitiveType : unsigned char
    {
        Points,
        Lines,
        LineStrip,
        LineLoop,
        Triangles,
        TriangleFan,
    };

    // ==================== 2D 渲染数据结构 (兼容旧代码) ====================

    /**
     * @brief 2D渲染批次
     */
    struct RenderBatch
    {
        RenderPrimitiveType primitiveType;
        const Ut::Vec2f* vertices;
        size_t vertexCount;
        const Ut::Vec3f* colors;
        size_t colorCount;
        float lineWidth;
        float pointSize;
    };

    /**
     * @brief 2D渲染数据包
     */
    struct RenderDataPackage
    {
        const RenderBatch* batches;
        size_t batchCount;
        float viewMatrix[16];
        float projectionMatrix[16];
        int viewport[4];
    };

    // ==================== 3D 渲染数据结构 ====================

    /**
     * @brief 3D渲染批次
     */
    struct RenderBatch3D
    {
        RenderPrimitiveType primitiveType;
        const Vec3f* vertices;
        size_t vertexCount;
        const Vec3f* normals;
        size_t normalCount;
        const Vec3f* colors;
        size_t colorCount;
        const unsigned int* indices;
        size_t indexCount;
        float lineWidth;
    };

    /**
     * @brief 3D渲染数据包
     */
    struct RenderDataPackage3D
    {
        const RenderBatch3D* batches;
        size_t batchCount;
        float viewMatrix[16];
        float projectionMatrix[16];
    };

    /**
     * @brief 网格顶点（带法线）
     */
    struct MeshVertex
    {
        Vec3f position;
        Vec3f normal;
    };

    /**
     * @brief 网格数据
     */
    struct MeshData
    {
        const MeshVertex* vertices;
        size_t vertexCount;
        const unsigned int* indices;
        size_t indexCount;
    };

    // ==================== 通用渲染命令（RenderDataConsumer 使用） ====================

    /**
     * @brief 渲染顶点（含颜色）
     */
    struct RenderVertex
    {
        Vec3f position;
        Vec3f color;
    };

    /**
     * @brief 单条渲染命令
     */
    struct RenderCommand
    {
        RenderPrimitiveType primitiveType = RenderPrimitiveType::Lines;
        std::vector<RenderVertex> vertices;
        bool useVertexColors = false;
        float lineWidth = 1.0f;

        size_t vertexCount() const
        {
            return vertices.size();
        }

        bool isEmpty() const
        {
            return vertices.empty();
        }
    };

    /**
     * @brief 渲染命令列表
     */
    struct RenderCommandList
    {
        std::vector<RenderCommand> commands;

        bool empty() const
        {
            return commands.empty();
        }

        size_t size() const
        {
            return commands.size();
        }
    };
}  // namespace Ut