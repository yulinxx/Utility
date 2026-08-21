#pragma once

#include "UtilityAPI.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <vector>

// [兼容性修复] Windows.h 定义的 min/max 宏与 Vec::min/Vec::max 静态成员函数冲突。
// 此处 undef 以确保成员函数正确编译。
#ifdef min
    #undef min
#endif
#ifdef max
    #undef max
#endif

namespace Ut
{
    /**
     * @brief 向量模板类，支持二维/三维向量和点坐标
     * @tparam T 数据类型 (int, float, double等)
     * @tparam N 维度 (目前只支持二/三维计算)
     */
    template<typename T, size_t N>
    class Vec
    {
    public:
        // 数据存储
        T data[N];

        Vec()
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = T(0);
            }
        }

        /// 单值构造函数，所有分量初始化为相同值
        explicit Vec(T value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = value;
            }
        }

        /// 二维向量构造函数 (N=2)
        template<size_t M = N, typename = std::enable_if_t<M == 2>>
        Vec(T x, T y)
        {
            data[0] = x;
            data[1] = y;
        }

        /// 三维向量构造函数 (N=3)
        template<size_t M = N, typename = std::enable_if_t<M == 3>>
        Vec(T x, T y, T z)
        {
            data[0] = x;
            data[1] = y;
            data[2] = z;
        }

        /// 四维向量构造函数 (N=4)
        template<size_t M = N, typename = std::enable_if_t<M == 4>>
        Vec(T x, T y, T z, T w)
        {
            data[0] = x;
            data[1] = y;
            data[2] = z;
            data[3] = w;
        }

        /// 拷贝构造函数
        Vec(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = other.data[i];
            }
        }

        // ==================== 访问器 ====================

        /// 获取X分量
        T& x()
        {
            return data[0];
        }

        const T& x() const
        {
            return data[0];
        }

        /// 获取Y分量
        template<size_t M = N, typename = std::enable_if_t<(M >= 2)>>
        T& y()
        {
            return data[1];
        }

        template<size_t M = N, typename = std::enable_if_t<(M >= 2)>>
        const T& y() const
        {
            return data[1];
        }

        /// 获取Z分量
        template<size_t M = N, typename = std::enable_if_t<(M >= 3)>>
        T& z()
        {
            return data[2];
        }

        template<size_t M = N, typename = std::enable_if_t<(M >= 3)>>
        const T& z() const
        {
            return data[2];
        }

        /// 获取W分量
        template<size_t M = N, typename = std::enable_if_t<(M == 4)>>
        T& w()
        {
            return data[3];
        }

        template<size_t M = N, typename = std::enable_if_t<(M == 4)>>
        const T& w() const
        {
            return data[3];
        }

        /// 下标访问运算符
        T& operator[](size_t index)
        {
            if (index >= N)
            {
                throw std::out_of_range("Vector index out of range");
            }
            return data[index];
        }

        const T& operator[](size_t index) const
        {
            if (index >= N)
            {
                throw std::out_of_range("Vector index out of range");
            }
            return data[index];
        }

        /// 获取维度
        static constexpr size_t dimension()
        {
            return N;
        }

        // ==================== 赋值运算符 ====================

        Vec& operator=(const Vec& other)
        {
            if (this != &other)
            {
                for (size_t i = 0; i < N; ++i)
                {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        // ==================== 算术运算符 ====================

        /// 向量加法
        Vec operator+(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        /// 向量减法
        Vec operator-(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

        /// 标量乘法
        Vec operator*(T scalar) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }

        /// 标量除法
        Vec operator/(T scalar) const
        {
            if (scalar == T(0))
            {
                throw std::runtime_error("Division by zero");
            }
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }

        /// 取负
        Vec operator-() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = -data[i];
            }
            return result;
        }

        // ==================== 复合赋值运算符 ====================

        Vec& operator+=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] += other.data[i];
            }
            return *this;
        }

        Vec& operator-=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }

        Vec& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] *= scalar;
            }
            return *this;
        }

        Vec& operator/=(T scalar)
        {
            if (scalar == T(0))
            {
                throw std::runtime_error("Division by zero");
            }
            for (size_t i = 0; i < N; ++i)
            {
                data[i] /= scalar;
            }
            return *this;
        }

        // ==================== 比较运算符 ====================

        bool operator==(const Vec& other) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (data[i] != other.data[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Vec& other) const
        {
            return !(*this == other);
        }

        // ==================== 向量运算 ====================

        /// 点积 (内积)
        T dot(const Vec& other) const
        {
            T result = T(0);
            for (size_t i = 0; i < N; ++i)
            {
                result += data[i] * other.data[i];
            }
            return result;
        }

        /// 叉积 (仅适用于三维向量)
        template<size_t M = N, typename = std::enable_if_t<M == 3>>
        Vec cross(const Vec& other) const
        {
            Vec result;
            result.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
            result.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
            result.data[2] = data[0] * other.data[1] - data[1] * other.data[0];
            return result;
        }

        /// 二维叉积 (返回标量，表示z分量)
        template<size_t M = N, typename = std::enable_if_t<M == 2>>
        T cross2D(const Vec& other) const
        {
            return data[0] * other.data[1] - data[1] * other.data[0];
        }

        /// 向量长度的平方
        T lengthSquared() const
        {
            T result = T(0);
            for (size_t i = 0; i < N; ++i)
            {
                result += data[i] * data[i];
            }
            return result;
        }

        /// 向量长度
        T length() const
        {
            return std::sqrt(lengthSquared());
        }

        /// 欧几里得距离到另一个点
        T distance(const Vec& other) const
        {
            return (*this - other).length();
        }

        /// 距离的平方
        T distanceSquared(const Vec& other) const
        {
            return (*this - other).lengthSquared();
        }

        /// 归一化（返回单位向量）
        Vec normalized() const
        {
            // 检查向量分量是否包含NaN或无穷大
            for (size_t i = 0; i < N; ++i)
            {
                if (data[i] != data[i])
                {
                    throw std::runtime_error("Cannot normalize vector containing NaN");
                }
                if (data[i] == std::numeric_limits<T>::infinity() || data[i] == -std::numeric_limits<T>::infinity())
                {
                    throw std::runtime_error("Cannot normalize vector containing infinity");
                }
            }

            T len = length();
            if (len == T(0))
            {
                return Vec();  // 零向量归一化结果仍为零向量（默认构造即全 0）
            }
            return *this / len;
        }

        /// 就地归一化
        Vec& normalize()
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (data[i] != data[i])
                {
                    throw std::runtime_error("Cannot normalize vector containing NaN");
                }
                if (data[i] == std::numeric_limits<T>::infinity() || data[i] == -std::numeric_limits<T>::infinity())
                {
                    throw std::runtime_error("Cannot normalize vector containing infinity");
                }
            }

            T len = length();
            if (len == T(0))
            {
                *this = Vec();  // 零向量归一化结果仍为零向量（默认构造即全 0）
                return *this;
            }
            *this /= len;
            return *this;
        }

        /// 判断是否为零向量
        bool isZero(T epsilon = T(1e-6)) const
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (std::abs(data[i]) > epsilon)
                {
                    return false;
                }
            }
            return true;
        }

        /// 判断是否为单位向量
        bool isUnit(T epsilon = T(1e-6)) const
        {
            return std::abs(length() - T(1)) < epsilon;
        }

        /// 两向量之间的夹角（弧度）
        T angle(const Vec& other) const
        {
            T lenProduct = length() * other.length();
            if (lenProduct == T(0))
            {
                throw std::runtime_error("Cannot compute angle with zero vector");
            }
            T cosAngle = dot(other) / lenProduct;
            cosAngle = std::max(T(-1), std::min(T(1), cosAngle));
            return std::acos(cosAngle);
        }

        /// 两向量之间的夹角（度数）
        T angleDegrees(const Vec& other) const
        {
            return angle(other) * T(180) / T(3.14159265358979323846);
        }

        /// 投影到另一个向量上
        Vec project(const Vec& onto) const
        {
            T lenSquared = onto.lengthSquared();
            if (lenSquared == T(0))
            {
                throw std::runtime_error("Cannot project onto zero vector");
            }
            return onto * (dot(onto) / lenSquared);
        }

        /// 反射向量（根据法向量）
        Vec reflect(const Vec& normal) const
        {
            return *this - normal * (T(2) * dot(normal));
        }

        /// 线性插值
        Vec lerp(const Vec& other, T t) const
        {
            return *this * (T(1) - t) + other * t;
        }

        /// 获取每个分量的最小值
        static Vec min(const Vec& a, const Vec& b)
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = std::min(a.data[i], b.data[i]);
            }
            return result;
        }

        /// 获取每个分量的最大值
        static Vec max(const Vec& a, const Vec& b)
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = std::max(a.data[i], b.data[i]);
            }
            return result;
        }

        /// 限制向量在指定范围内
        Vec clamp(const Vec& minVec, const Vec& maxVec) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i)
            {
                result.data[i] = std::max(minVec.data[i], std::min(data[i], maxVec.data[i]));
            }
            return result;
        }
    };

    // ==================== 全局运算符 ====================

    /// 标量 * 向量
    template<typename T, size_t N>
    inline Vec<T, N> operator*(T scalar, const Vec<T, N>& vec)
    {
        return vec * scalar;
    }

    // ==================== 常用类型别名 ====================

    // 二维向量
    using Vec2i = Vec<int, 2>;
    using Vec2f = Vec<float, 2>;
    using Vec2 = Vec<double, 2>;
    using Vec2d = Vec<double, 2>;

    // 三维向量
    using Vec3i = Vec<int, 3>;
    using Vec3f = Vec<float, 3>;
    using Vec3 = Vec<double, 3>;
    using Vec3d = Vec<double, 3>;

    // 点类型
    using Point2i = Vec<int, 2>;
    using Point2f = Vec<float, 2>;
    using Point2 = Vec<double, 2>;
    using Point2d = Vec<double, 2>;

    using Point3i = Vec<int, 3>;
    using Point3f = Vec<float, 3>;
    using Point3 = Vec<double, 3>;
    using Point3d = Vec<double, 3>;

    // 向量容器别名
    using Vec2dVector = std::vector<Vec2d>;
    using Vec2fVector = std::vector<Vec2f>;
    using Vec2iVector = std::vector<Vec2i>;

    using Vec3dVector = std::vector<Vec3d>;
    using Vec3fVector = std::vector<Vec3f>;
    using Vec3iVector = std::vector<Vec3i>;

    // 点容器别名
    using Point2dVector = std::vector<Point2d>;
    using Point2fVector = std::vector<Point2f>;
    using Point2iVector = std::vector<Point2i>;

    using Point3dVector = std::vector<Point3d>;
    using Point3fVector = std::vector<Point3f>;
    using Point3iVector = std::vector<Point3i>;

    // 四维向量 (齐次坐标)
    using Vec4f = Vec<float, 4>;
    using Vec4d = Vec<double, 4>;
    using Vec4 = Vec<float, 4>;
}  // namespace Ut

// NOTE: extern template 声明已移除，原因:
// Clang 在 -fvisibility=hidden + -fvisibility-inlines-hidden 下会生成
// weak private 符号，导致 dylib 无法导出。改为在 Src/Vec.cpp 中用
// #pragma GCC visibility push(default) 导出显式实例化符号。