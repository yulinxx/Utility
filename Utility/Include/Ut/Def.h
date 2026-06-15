#pragma once

namespace Ut
{
    // ==================== 数学常量 ====================

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI2
#define M_PI2 (2.0 * M_PI)  // 2π
#endif

#ifndef M_PI_2
#define M_PI_2 (M_PI / 2.0)  // π/2
#endif

#ifndef M_PI_4
#define M_PI_4 (M_PI / 4.0)  // π/4
#endif

#ifndef M_E
#define M_E 2.71828182845904523536  // 自然对数底数
#endif

// ==================== 角度转换 ====================

#ifndef DEG_TO_RAD
#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG(rad) ((rad) * 180.0 / M_PI)
#endif

// ==================== 数值比较 ====================

#ifndef EPSILON
#define EPSILON 1e-6
#endif

#ifndef FLOAT_EPSILON
#define FLOAT_EPSILON 1e-5f
#endif

#ifndef DOUBLE_EPSILON
#define DOUBLE_EPSILON 1e-9
#endif

// ==================== 常用宏 ====================

// 绝对值
#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

// 浮点数比较
#ifndef FLOAT_EQUAL
#define FLOAT_EQUAL(a, b) (ABS((a) - (b)) < EPSILON)
#endif

#ifndef FLOAT_ZERO
#define FLOAT_ZERO(x) (ABS(x) < EPSILON)
#endif

// ==================== 内存和数组 ====================

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) do { delete (p); (p) = nullptr; } while(0)
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) do { delete[] (p); (p) = nullptr; } while(0)
#endif
}
