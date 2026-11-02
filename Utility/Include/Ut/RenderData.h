#pragma once

#include "Vec.h"
#include "VertexFormat.hpp"
#include "PrimitiveType.hpp"

#include <cstddef>
#include <vector>

/**
 * @brief 渲染数据传输结构 (2D + 3D)
 */

namespace Ut
{
    using RenderPrimitiveType = PrimitiveType;

    struct RenderBatch
    {
        PrimitiveType primitiveType;
        const Ut::Vec2f* vertices;
        size_t vertexCount;
        const Ut::Vec3f* colors;
        size_t colorCount;
        float lineWidth;
        float pointSize;
    };

    struct RenderDataPackage
    {
        const RenderBatch* batches;
        size_t batchCount;
        float viewMatrix[16];
        float projectionMatrix[16];
        int viewport[4];
    };

    struct RenderBatch3D
    {
        PrimitiveType primitiveType;
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

    struct RenderDataPackage3D
    {
        const RenderBatch3D* batches;
        size_t batchCount;
        float viewMatrix[16];
        float projectionMatrix[16];
    };

    using MeshVertex = VertexP3N3;

    struct MeshData
    {
        const MeshVertex* vertices;
        size_t vertexCount;
        const unsigned int* indices;
        size_t indexCount;
    };

    using RenderVertex = VertexP3C3;

    struct RenderCommand
    {
        PrimitiveType primitiveType = PrimitiveType::Lines;
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