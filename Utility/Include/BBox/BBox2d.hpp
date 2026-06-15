#pragma once

#include "UtilityAPI.h"
#include "Vec/Vec.hpp"

#include <algorithm>
#include <limits>

#ifndef UT_EXTERN_TEMPLATE
#ifdef UTILITY_EXTERN_TEMPLATES
#define UT_EXTERN_TEMPLATE extern
#else
#define UT_EXTERN_TEMPLATE
#endif
#endif

namespace Ut
{
    /**
     * @brief 2D 轴对齐包围盒 (Axis-Aligned Bounding Box)
     * @tparam T 数据类型 (float, double等)
     */
    template <typename T>
    class BBox2
    {
    public:
        Vec<T, 2> minPt;  // 最小点 (左下角)
        Vec<T, 2> maxPt;  // 最大点 (右上角)

        // ==================== 构造函数 ====================

        /// 默认构造函数，创建一个无效的包围盒
        BBox2()
        {
            reset();
        }

        /// 从两个点构造包围盒
        BBox2(const Vec<T, 2>& p1, const Vec<T, 2>& p2)
        {
            minPt = Vec<T, 2>::min(p1, p2);
            maxPt = Vec<T, 2>::max(p1, p2);
        }

        /// 从四个坐标值构造包围盒
        BBox2(T minX, T minY, T maxX, T maxY)
            : minPt(std::min(minX, maxX), std::min(minY, maxY))
            , maxPt(std::max(minX, maxX), std::max(minY, maxY))
        {
        }

        /// 拷贝构造函数
        BBox2(const BBox2& other) = default;

        /// 移动构造函数
        BBox2(BBox2&& other) noexcept = default;

        // ==================== 赋值运算符 ====================
        /// 拷贝赋值运算符
        BBox2& operator=(const BBox2& other)
        {
            if (this != &other)  // 防止自赋值
            {
                minPt = other.minPt;
                maxPt = other.maxPt;
            }
            return *this;
        }

        /// 移动赋值运算符 (C++11)
        BBox2& operator=(BBox2&& other) noexcept
        {
            if (this != &other)  // 防止自赋值
            {
                minPt = std::move(other.minPt);
                maxPt = std::move(other.maxPt);
            }
            return *this;
        }

        // ==================== 基本操作 ====================

        /// 重置为无效包围盒
        void reset()
        {
            constexpr T maxVal = std::numeric_limits<T>::max();
            constexpr T minVal = std::numeric_limits<T>::lowest();
            minPt = Vec<T, 2>(maxVal, maxVal);
            maxPt = Vec<T, 2>(minVal, minVal);
        }

        /// 检查包围盒是否有效
        bool isValid() const
        {
            return minPt.x() <= maxPt.x() && minPt.y() <= maxPt.y();
        }

        /// 扩展包围盒以包含指定点
        void expand(const Vec<T, 2>& point)
        {
            minPt = Vec<T, 2>::min(minPt, point);
            maxPt = Vec<T, 2>::max(maxPt, point);
        }

        /// 扩展包围盒以包含另一个包围盒
        void expand(const BBox2& other)
        {
            if (other.isValid())
            {
                minPt = Vec<T, 2>::min(minPt, other.minPt);
                maxPt = Vec<T, 2>::max(maxPt, other.maxPt);
            }
        }

        // ==================== 查询操作 ====================

        /// 获取宽度
        T width() const
        {
            return maxPt.x() - minPt.x();
        }

        /// 获取高度
        T height() const
        {
            return maxPt.y() - minPt.y();
        }

        /// 获取中心点
        Vec<T, 2> center() const
        {
            return (minPt + maxPt) * T(0.5);
        }

        /// 获取对角线长度
        T diagonal() const
        {
            return (maxPt - minPt).length();
        }

        /// 获取面积
        T area() const
        {
            return width() * height();
        }

        /// 检查点是否在包围盒内
        bool contains(const Vec<T, 2>& point) const
        {
            return point.x() >= minPt.x() && point.x() <= maxPt.x() &&
                point.y() >= minPt.y() && point.y() <= maxPt.y();
        }

        /// 检查另一个包围盒是否完全在此包围盒内
        bool contains(const BBox2& other) const
        {
            return other.minPt.x() >= minPt.x() && other.maxPt.x() <= maxPt.x() &&
                other.minPt.y() >= minPt.y() && other.maxPt.y() <= maxPt.y();
        }

        /// 检查是否与另一个包围盒相交
        bool intersects(const BBox2& other) const
        {
            return minPt.x() <= other.maxPt.x() && maxPt.x() >= other.minPt.x() &&
                minPt.y() <= other.maxPt.y() && maxPt.y() >= other.minPt.y();
        }

        /// 获取与另一个包围盒的交集
        BBox2 intersection(const BBox2& other) const
        {
            if (!intersects(other))
            {
                return BBox2(); // 返回无效包围盒
            }
            return BBox2(
                std::max(minPt.x(), other.minPt.x()),
                std::max(minPt.y(), other.minPt.y()),
                std::min(maxPt.x(), other.maxPt.x()),
                std::min(maxPt.y(), other.maxPt.y())
            );
        }

        /// 获取包含两个包围盒的最小包围盒 (并集)
        BBox2 united(const BBox2& other) const
        {
            BBox2 result = *this;
            result.expand(other);
            return result;
        }

        // ==================== 变换操作 ====================

        /// 按指定量扩展包围盒（各边向外扩展）
        BBox2 inflated(T amount) const
        {
            return BBox2(
                minPt.x() - amount, minPt.y() - amount,
                maxPt.x() + amount, maxPt.y() + amount
            );
        }

        /// 按指定量收缩包围盒（各边向内收缩）
        BBox2 deflated(T amount) const
        {
            return inflated(-amount);
        }

        // ==================== 比较运算符 ====================

        bool operator==(const BBox2& other) const
        {
            return minPt == other.minPt && maxPt == other.maxPt;
        }

        bool operator!=(const BBox2& other) const
        {
            return !(*this == other);
        }
    };

    // ==================== 常用类型别名 ====================
    using BBox2f = BBox2<float>;
    using BBox2d = BBox2<double>;

    using Box = BBox2<double>;
    using Rect = BBox2<double>;
    using Range = BBox2<double>;
} // namespace Ut

// 显式实例化声明
UT_EXTERN_TEMPLATE template class Ut::BBox2<float>;
UT_EXTERN_TEMPLATE template class Ut::BBox2<double>;