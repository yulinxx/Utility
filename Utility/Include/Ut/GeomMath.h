#pragma once

#include "Ut/Def.h"

#include <cmath>
#include <algorithm>

namespace Ut
{
    /**
     * @brief 基础数学工具（纯函数，header-only）
     *
     * 收口所有浮点容差比较、区间工具、角度归一化等基础数值操作。
     * 不依赖任何 Engine 层，仅供 Ut:: 和 Geo2DPrimitives 调用。
     */
    struct GeomMath
    {
        // ==================== 容差比较 ====================

        /** 判断值是否接近零 */
        static inline bool isZero(double v, double tol = DOUBLE_EPSILON)
        {
            return std::abs(v) <= tol;
        }

        /** 判断两浮点数是否近似相等 */
        static inline bool almostEqual(double a, double b, double tol = DOUBLE_EPSILON)
        {
            return std::abs(a - b) <= tol;
        }

        /** 判断 a <= b（带容差） */
        static inline bool lessOrEqual(double a, double b, double tol = DOUBLE_EPSILON)
        {
            return a <= b + tol;
        }

        /** 判断 a >= b（带容差） */
        static inline bool greaterOrEqual(double a, double b, double tol = DOUBLE_EPSILON)
        {
            return a >= b - tol;
        }

        // ==================== 区间工具 ====================

        /** 将值限制在 [lo, hi] 范围内 */
        static inline double clamp(double v, double lo, double hi)
        {
            return std::clamp(v, lo, hi);
        }

        /** 将值限制在 [0, 1] 范围内 */
        static inline double clamp01(double v)
        {
            return std::clamp(v, 0.0, 1.0);
        }

        /** 线性插值 */
        static inline double lerp(double a, double b, double t)
        {
            return a + (b - a) * t;
        }

        // ==================== 角度工具 ====================

        /** 弧度转角度 */
        static inline double radToDeg(double rad)
        {
            return rad * 180.0 / M_PI;
        }

        /** 角度转弧度 */
        static inline double degToRad(double deg)
        {
            return deg * M_PI / 180.0;
        }

        /** 将角度归一化到 [0, 2π) */
        static inline double normalizeAngle0To2Pi(double a)
        {
            double dR = std::fmod(a, 2.0 * M_PI);
            if (dR < 0.0)
                dR += 2.0 * M_PI;
            return dR;
        }

        /** 将角度归一化到 [-π, π) */
        static inline double normalizeAnglePiToPi(double a)
        {
            double dR = std::fmod(a + M_PI, 2.0 * M_PI);
            if (dR < 0.0)
                dR += 2.0 * M_PI;
            return dR - M_PI;
        }

        /** 计算两角度之间的最小差值，结果 ∈ [-π, π] */
        static inline double angleDiff(double a, double b)
        {
            double d = normalizeAnglePiToPi(a - b);
            return d;
        }

        // ==================== 区间判断 ====================

        /** 判断值是否在 [lo, hi] 区间内（带容差） */
        static inline bool inRange(double v, double lo, double hi, double tol = DOUBLE_EPSILON)
        {
            return v >= lo - tol && v <= hi + tol;
        }

        /** 判断值是否在 [0, 1] 区间内（带容差） */
        static inline bool inRange01(double v, double tol = DOUBLE_EPSILON)
        {
            return v >= -tol && v <= 1.0 + tol;
        }

        // ==================== 符号工具 ====================

        /** 返回 -1, 0, 1 */
        static inline int sign(double v, double tol = DOUBLE_EPSILON)
        {
            if (v > tol) return 1;
            if (v < -tol) return -1;
            return 0;
        }
    };
} // namespace Ut