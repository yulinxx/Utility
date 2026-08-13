#pragma once

#include "UtilityAPI.h"
#include "Vec/Vec.hpp"
#include <algorithm>
#include <limits>

namespace Ut
{
    /**
     * @brief 3D 轴对齐包围盒 (Axis-Aligned Bounding Box)
     */
    template<typename T>
    class BBox3
    {
    public:
        Vec<T, 3> minPt;
        Vec<T, 3> maxPt;

        BBox3()
        {
            reset();
        }

        BBox3(const Vec<T, 3>& p1, const Vec<T, 3>& p2)
        {
            minPt = Vec<T, 3>::min(p1, p2);
            maxPt = Vec<T, 3>::max(p1, p2);
        }

        BBox3(T minX, T minY, T minZ, T maxX, T maxY, T maxZ)
            : minPt(minX, minY, minZ)
            , maxPt(maxX, maxY, maxZ)
        {
        }

        void reset()
        {
            constexpr T maxVal = std::numeric_limits<T>::max();
            constexpr T minVal = std::numeric_limits<T>::lowest();
            minPt = Vec<T, 3>(maxVal, maxVal, maxVal);
            maxPt = Vec<T, 3>(minVal, minVal, minVal);
        }

        bool isValid() const
        {
            return minPt[0] <= maxPt[0] && minPt[1] <= maxPt[1] && minPt[2] <= maxPt[2];
        }

        void expand(const Vec<T, 3>& pt)
        {
            minPt = Vec<T, 3>::min(minPt, pt);
            maxPt = Vec<T, 3>::max(maxPt, pt);
        }

        void expand(const BBox3& other)
        {
            if (other.isValid())
            {
                expand(other.minPt);
                expand(other.maxPt);
            }
        }

        bool contains(const Vec<T, 3>& pt) const
        {
            return pt[0] >= minPt[0] && pt[0] <= maxPt[0] && pt[1] >= minPt[1] && pt[1] <= maxPt[1] &&
                pt[2] >= minPt[2] && pt[2] <= maxPt[2];
        }

        bool contains(const BBox3& other) const
        {
            return minPt[0] <= other.minPt[0] && maxPt[0] >= other.maxPt[0] && minPt[1] <= other.minPt[1] &&
                maxPt[1] >= other.maxPt[1] && minPt[2] <= other.minPt[2] && maxPt[2] >= other.maxPt[2];
        }

        Vec<T, 3> center() const
        {
            return Vec<T, 3>(
                (minPt[0] + maxPt[0]) * T(0.5), (minPt[1] + maxPt[1]) * T(0.5), (minPt[2] + maxPt[2]) * T(0.5));
        }

        Vec<T, 3> size() const
        {
            return Vec<T, 3>(maxPt[0] - minPt[0], maxPt[1] - minPt[1], maxPt[2] - minPt[2]);
        }

        T diagonal() const
        {
            return (maxPt - minPt).length();
        }

        T maxExtent() const
        {
            Vec<T, 3> s = size();
            return std::max({ s[0], s[1], s[2] });
        }

        bool intersects(const BBox3& other) const
        {
            return minPt[0] <= other.maxPt[0] && maxPt[0] >= other.minPt[0] && minPt[1] <= other.maxPt[1] &&
                maxPt[1] >= other.minPt[1] && minPt[2] <= other.maxPt[2] && maxPt[2] >= other.minPt[2];
        }
    };

    using BBox3f = BBox3<float>;
    using BBox3d = BBox3<double>;
}  // namespace Ut