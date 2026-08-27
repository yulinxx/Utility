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
        // ==================== 具名容差常量 ====================
        //
        // 背景：项目里原先有 5 套各自实现的浮点相等判断（FLOAT_EQUAL 宏、
        // GeomMath::almostEqual、EntityFill::isEqual、ScanlineFill/BowFill 各自的
        // 匿名 isEqual、Geo3DPrimitives::almostEqual），而且默认容差差了三个数量级
        // （EPSILON = 1e-6，DOUBLE_EPSILON = 1e-9）。实现已收敛到本结构体，
        // 但**各调用点的容差数值一律显式传入、保持原值**，不做统一——几何算法的
        // 容差是算法语义的一部分，擅自统一会静默改变结果。
        //
        // 新代码请优先用下面的具名常量表达意图，而不是写裸数值。

        /// 除零保护（float）：分母绝对值小于此值就不做除法
        /// float 只有 ~1e-7 的相对精度，比这更小的阈值（如 1e-12f）等价于"只挡精确的 0"
        static constexpr float kEpsDivisorF = 1e-6f;

        /// 除零保护（double）
        static constexpr double kEpsDivisor = 1e-12;

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

        /**
         * @brief float 版接近零判断
         *
         * 独立命名而非重载，避免 isZero(0) 之类的整型实参产生歧义。
         */
        static inline bool isZeroF(float v, float tol = FLOAT_EPSILON)
        {
            return std::abs(v) <= tol;
        }

        /** float 版近似相等判断 */
        static inline bool almostEqualF(float a, float b, float tol = FLOAT_EPSILON)
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
            {
                dR += 2.0 * M_PI;
            }
            return dR;
        }

        /** 将角度归一化到 [-π, π) */
        static inline double normalizeAnglePiToPi(double a)
        {
            double dR = std::fmod(a + M_PI, 2.0 * M_PI);
            if (dR < 0.0)
            {
                dR += 2.0 * M_PI;
            }
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
            if (v > tol)
            {
                return 1;
            }
            if (v < -tol)
            {
                return -1;
            }
            return 0;
        }
    };
}  // namespace Ut