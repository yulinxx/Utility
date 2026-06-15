#pragma once

#include "UtilityAPI.h"
#include "Vec/Vec.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

namespace Ut
{
    /**
     * @brief 3x3 矩阵模板类，用于2D变换、正交投影等
     * @tparam T 数据类型 (int, float, double等)
     *
     * 矩阵存储方式：列主序（Column-Major）
     * 矩阵布局:
     *   | m[0]  m[3]  m[6] |   | m00  m01  m02 |
     *   | m[1]  m[4]  m[7] | = | m10  m11  m12 |
     *   | m[2]  m[5]  m[8] |   | m20  m21  m22 |
     */
    template <typename T>
    class Matrix
    {
    public:
        // 数据存储（列主序）
        T data[9];

        // ==================== 构造函数 ====================

        /// 默认构造函数，初始化为单位矩阵
        Matrix() : Matrix(T(1))
        {
        }

        /// 对角线构造，指定对角线元素值
        explicit Matrix(T diagonal)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] = T(0);
            }
            data[0] = diagonal; // m00
            data[4] = diagonal; // m11
            data[8] = diagonal; // m22
        }

        /// 从9个元素构造（行主序输入，内部转为列主序存储）
        Matrix(T m00, T m01, T m02,
            T m10, T m11, T m12,
            T m20, T m21, T m22)
        {
            // 列主序存储
            data[0] = m00; data[3] = m01; data[6] = m02;
            data[1] = m10; data[4] = m11; data[7] = m12;
            data[2] = m20; data[5] = m21; data[8] = m22;
        }

        /// 从数组构造（列主序）
        explicit Matrix(const T* arr)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] = arr[i];
            }
        }

        /// 拷贝构造函数
        Matrix(const Matrix& other)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] = other.data[i];
            }
        }

        // ==================== 静态工厂方法 ====================

        /// 创建单位矩阵
        static Matrix identity()
        {
            return Matrix(T(1));
        }

        /// 创建零矩阵
        static Matrix zero()
        {
            return Matrix(T(0));
        }

        // ==================== 访问器 ====================

        /// 获取指定位置元素（行row, 列col）
        T& at(size_t row, size_t col)
        {
            if (row >= 3 || col >= 3)
            {
                throw std::out_of_range("Matrix index out of range");
            }
            return data[col * 3 + row];
        }

        const T& at(size_t row, size_t col) const
        {
            if (row >= 3 || col >= 3)
            {
                throw std::out_of_range("Matrix index out of range");
            }
            return data[col * 3 + row];
        }

        /// 括号访问运算符 mat(row, col)
        T& operator()(size_t row, size_t col)
        {
            return at(row, col);
        }

        const T& operator()(size_t row, size_t col) const
        {
            return at(row, col);
        }

        /// 下标访问运算符（直接访问列主序数据）
        T& operator[](size_t index)
        {
            if (index >= 9)
            {
                throw std::out_of_range("Matrix index out of range");
            }
            return data[index];
        }

        const T& operator[](size_t index) const
        {
            if (index >= 9)
            {
                throw std::out_of_range("Matrix index out of range");
            }
            return data[index];
        }

        /// 获取列向量
        Vec<T, 3> column(size_t col) const
        {
            if (col >= 3)
            {
                throw std::out_of_range("Column index out of range");
            }
            return Vec<T, 3>(data[col * 3], data[col * 3 + 1], data[col * 3 + 2]);
        }

        /// 获取行向量
        Vec<T, 3> row(size_t r) const
        {
            if (r >= 3)
            {
                throw std::out_of_range("Row index out of range");
            }
            return Vec<T, 3>(data[r], data[3 + r], data[6 + r]);
        }

        /// 设置列向量
        void setColumn(size_t col, const Vec<T, 3>& v)
        {
            if (col >= 3)
            {
                throw std::out_of_range("Column index out of range");
            }
            data[col * 3] = v.data[0];
            data[col * 3 + 1] = v.data[1];
            data[col * 3 + 2] = v.data[2];
        }

        /// 设置行向量
        void setRow(size_t r, const Vec<T, 3>& v)
        {
            if (r >= 3)
            {
                throw std::out_of_range("Row index out of range");
            }
            data[r] = v.data[0];
            data[3 + r] = v.data[1];
            data[6 + r] = v.data[2];
        }

        /// 获取原始数据指针（用于图形渲染）
        T* ptr()
        {
            return data;
        }
        const T* ptr() const
        {
            return data;
        }

        // ==================== 赋值运算符 ====================

        Matrix& operator=(const Matrix& other)
        {
            if (this != &other)
            {
                for (size_t i = 0; i < 9; ++i)
                {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        // ==================== 算术运算符 ====================

        /// 矩阵加法
        Matrix operator+(const Matrix& other) const
        {
            Matrix result;
            for (size_t i = 0; i < 9; ++i)
            {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        /// 矩阵减法
        Matrix operator-(const Matrix& other) const
        {
            Matrix result;
            for (size_t i = 0; i < 9; ++i)
            {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

        /// 矩阵乘法
        Matrix operator*(const Matrix& other) const
        {
            Matrix result;
            for (size_t col = 0; col < 3; ++col)
            {
                for (size_t row = 0; row < 3; ++row)
                {
                    T sum = T(0);
                    for (size_t k = 0; k < 3; ++k)
                    {
                        sum += at(row, k) * other.at(k, col);
                    }
                    result.at(row, col) = sum;
                }
            }
            return result;
        }

        /// 标量乘法
        Matrix operator*(T scalar) const
        {
            Matrix result;
            for (size_t i = 0; i < 9; ++i)
            {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }

        /// 标量除法
        Matrix operator/(T scalar) const
        {
            if (scalar == T(0))
            {
                throw std::runtime_error("Division by zero");
            }
            Matrix result;
            for (size_t i = 0; i < 9; ++i)
            {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }

        /// 取负
        Matrix operator-() const
        {
            Matrix result;
            for (size_t i = 0; i < 9; ++i)
            {
                result.data[i] = -data[i];
            }
            return result;
        }

        // ==================== 矩阵与向量运算 ====================

        /// 矩阵乘以三维向量 (用于齐次坐标变换)
        Vec<T, 3> operator*(const Vec<T, 3>& v) const
        {
            return Vec<T, 3>(
                at(0, 0) * v.data[0] + at(0, 1) * v.data[1] + at(0, 2) * v.data[2],
                at(1, 0) * v.data[0] + at(1, 1) * v.data[1] + at(1, 2) * v.data[2],
                at(2, 0) * v.data[0] + at(2, 1) * v.data[1] + at(2, 2) * v.data[2]
            );
        }

        /// 变换二维点 (自动添加齐次坐标w=1，返回时除以w)
        Vec<T, 2> transformPoint(const Vec<T, 2>& p) const
        {
            T x = at(0, 0) * p.data[0] + at(0, 1) * p.data[1] + at(0, 2);
            T y = at(1, 0) * p.data[0] + at(1, 1) * p.data[1] + at(1, 2);
            T w = at(2, 0) * p.data[0] + at(2, 1) * p.data[1] + at(2, 2);

            if (std::abs(w) < T(1e-10))
            {
                throw std::runtime_error("Homogeneous coordinate w is zero");
            }
            return Vec<T, 2>(x / w, y / w);
        }

        /// 变换二维向量 (不考虑平移，w=0)
        Vec<T, 2> transformVector(const Vec<T, 2>& v) const
        {
            return Vec<T, 2>(
                at(0, 0) * v.data[0] + at(0, 1) * v.data[1],
                at(1, 0) * v.data[0] + at(1, 1) * v.data[1]
            );
        }

        // ==================== 复合赋值运算符 ====================

        Matrix& operator+=(const Matrix& other)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] += other.data[i];
            }
            return *this;
        }

        Matrix& operator-=(const Matrix& other)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }

        Matrix& operator*=(const Matrix& other)
        {
            *this = *this * other;
            return *this;
        }

        Matrix& operator*=(T scalar)
        {
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] *= scalar;
            }
            return *this;
        }

        Matrix& operator/=(T scalar)
        {
            if (scalar == T(0))
            {
                throw std::runtime_error("Division by zero");
            }
            for (size_t i = 0; i < 9; ++i)
            {
                data[i] /= scalar;
            }
            return *this;
        }

        // ==================== 比较运算符 ====================

        bool operator==(const Matrix& other) const
        {
            for (size_t i = 0; i < 9; ++i)
            {
                if (data[i] != other.data[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        /// 近似相等比较
        bool equals(const Matrix& other, T epsilon = T(1e-6)) const
        {
            for (size_t i = 0; i < 9; ++i)
            {
                if (std::abs(data[i] - other.data[i]) > epsilon)
                {
                    return false;
                }
            }
            return true;
        }

        // ==================== 矩阵运算 ====================

        /// 转置矩阵
        Matrix transposed() const
        {
            Matrix result;
            for (size_t row = 0; row < 3; ++row)
            {
                for (size_t col = 0; col < 3; ++col)
                {
                    result.at(row, col) = at(col, row);
                }
            }
            return result;
        }

        /// 就地转置
        Matrix& transpose()
        {
            std::swap(data[1], data[3]); // m10 <-> m01
            std::swap(data[2], data[6]); // m20 <-> m02
            std::swap(data[5], data[7]); // m21 <-> m12
            return *this;
        }

        /// 计算行列式
        T determinant() const
        {
            // det = m00*(m11*m22 - m12*m21) - m01*(m10*m22 - m12*m20) + m02*(m10*m21 - m11*m20)
            T m00 = at(0, 0), m01 = at(0, 1), m02 = at(0, 2);
            T m10 = at(1, 0), m11 = at(1, 1), m12 = at(1, 2);
            T m20 = at(2, 0), m21 = at(2, 1), m22 = at(2, 2);

            return m00 * (m11 * m22 - m12 * m21)
                - m01 * (m10 * m22 - m12 * m20)
                + m02 * (m10 * m21 - m11 * m20);
        }

        /// 计算逆矩阵
        Matrix inverse() const
        {
            T det = determinant();
            if (std::abs(det) < T(1e-10))
            {
                throw std::runtime_error("Matrix is singular, cannot compute inverse");
            }

            T m00 = at(0, 0), m01 = at(0, 1), m02 = at(0, 2);
            T m10 = at(1, 0), m11 = at(1, 1), m12 = at(1, 2);
            T m20 = at(2, 0), m21 = at(2, 1), m22 = at(2, 2);

            T invDet = T(1) / det;

            // 伴随矩阵的转置除以行列式
            Matrix result;
            result.at(0, 0) = (m11 * m22 - m12 * m21) * invDet;
            result.at(0, 1) = (m02 * m21 - m01 * m22) * invDet;
            result.at(0, 2) = (m01 * m12 - m02 * m11) * invDet;
            result.at(1, 0) = (m12 * m20 - m10 * m22) * invDet;
            result.at(1, 1) = (m00 * m22 - m02 * m20) * invDet;
            result.at(1, 2) = (m02 * m10 - m00 * m12) * invDet;
            result.at(2, 0) = (m10 * m21 - m11 * m20) * invDet;
            result.at(2, 1) = (m01 * m20 - m00 * m21) * invDet;
            result.at(2, 2) = (m00 * m11 - m01 * m10) * invDet;

            return result;
        }

        /// 判断是否为单位矩阵
        bool isIdentity(T epsilon = T(1e-6)) const
        {
            return equals(Matrix::identity(), epsilon);
        }

        /// 判断是否为零矩阵
        bool isZero(T epsilon = T(1e-6)) const
        {
            for (size_t i = 0; i < 9; ++i)
            {
                if (std::abs(data[i]) > epsilon)
                {
                    return false;
                }
            }
            return true;
        }

        /// 判断是否可逆
        bool isInvertible(T epsilon = T(1e-10)) const
        {
            return std::abs(determinant()) > epsilon;
        }

        // ==================== 2D 变换矩阵生成（静态方法）====================

        /// 创建2D平移矩阵
        static Matrix translate(T tx, T ty)
        {
            Matrix result = identity();
            result.at(0, 2) = tx;
            result.at(1, 2) = ty;
            return result;
        }

        static Matrix translate(const Vec<T, 2>& t)
        {
            return translate(t.data[0], t.data[1]);
        }

        /// 创建2D旋转矩阵（弧度）
        static Matrix rotate(T radians)
        {
            T c = std::cos(radians);
            T s = std::sin(radians);
            Matrix result = identity();
            result.at(0, 0) = c;  result.at(0, 1) = -s;
            result.at(1, 0) = s;  result.at(1, 1) = c;
            return result;
        }

        /// 创建2D旋转矩阵（角度）
        static Matrix rotateDegrees(T degrees)
        {
            return rotate(degrees * T(3.14159265358979323846) / T(180));
        }

        /// 创建绕指定点旋转的矩阵
        static Matrix rotateAround(T radians, const Vec<T, 2>& center)
        {
            return translate(center) * rotate(radians) * translate(-center.data[0], -center.data[1]);
        }

        /// 创建2D缩放矩阵
        static Matrix scale(T sx, T sy)
        {
            Matrix result = identity();
            result.at(0, 0) = sx;
            result.at(1, 1) = sy;
            return result;
        }

        static Matrix scale(T s)
        {
            return scale(s, s);
        }

        static Matrix scale(const Vec<T, 2>& s)
        {
            return scale(s.data[0], s.data[1]);
        }

        /// 创建绕指定点缩放的矩阵
        static Matrix scaleAround(T sx, T sy, const Vec<T, 2>& center)
        {
            return translate(center) * scale(sx, sy) * translate(-center.data[0], -center.data[1]);
        }

        /// 创建2D剪切矩阵
        static Matrix shear(T shx, T shy)
        {
            Matrix result = identity();
            result.at(0, 1) = shx;
            result.at(1, 0) = shy;
            return result;
        }

        /// 创建X轴镜像矩阵（关于Y轴对称）
        static Matrix mirrorX()
        {
            return scale(T(-1), T(1));
        }

        /// 创建Y轴镜像矩阵（关于X轴对称）
        static Matrix mirrorY()
        {
            return scale(T(1), T(-1));
        }

        /// 创建关于任意直线的镜像矩阵（过原点，方向由角度指定）
        static Matrix mirror(T radians)
        {
            T c2 = std::cos(T(2) * radians);
            T s2 = std::sin(T(2) * radians);
            Matrix result = identity();
            result.at(0, 0) = c2;   result.at(0, 1) = s2;
            result.at(1, 0) = s2;   result.at(1, 1) = -c2;
            return result;
        }

        /**
         * @brief 创建关于任意两点定义直线的镜像矩阵
         * @param p1 直线上的第一个点
         * @param p2 直线上的第二个点
         * @return 镜像变换矩阵
         *
         * 变换步骤：平移p1到原点 -> 旋转使直线与X轴重合 -> 关于X轴镜像 -> 反向旋转 -> 反向平移
         */
        static Matrix mirrorLine(const Vec<T, 2>& p1, const Vec<T, 2>& p2)
        {
            T dx = p2.data[0] - p1.data[0];
            T dy = p2.data[1] - p1.data[1];
            T len = std::sqrt(dx * dx + dy * dy);

            if (len < T(1e-10))
            {
                throw std::runtime_error("Mirror line points are too close");
            }

            // 归一化方向向量
            T ux = dx / len;
            T uy = dy / len;

            // 直接计算镜像矩阵 (效率更高)
            // 对于过点(x0,y0)、方向(ux,uy)的直线：
            // M = T(p1) * R * mirrorY * R^(-1) * T(-p1)
            // 其中 R 是将直线旋转到X轴的矩阵

            // 简化计算: 关于过(x0,y0)方向(ux,uy)的直线镜像
            T x0 = p1.data[0];
            T y0 = p1.data[1];

            // 2D镜像矩阵元素
            T a = ux * ux - uy * uy;      // cos(2θ)
            T b = T(2) * ux * uy;          // sin(2θ)

            Matrix result;
            result.at(0, 0) = a;
            result.at(0, 1) = b;
            result.at(0, 2) = x0 - a * x0 - b * y0;
            result.at(1, 0) = b;
            result.at(1, 1) = -a;
            result.at(1, 2) = y0 - b * x0 + a * y0;
            result.at(2, 0) = T(0);
            result.at(2, 1) = T(0);
            result.at(2, 2) = T(1);

            return result;
        }

        /// 关于两点定义直线的镜像 (别名)
        static Matrix mirrorAboutLine(const Vec<T, 2>& p1, const Vec<T, 2>& p2)
        {
            return mirrorLine(p1, p2);
        }

        // ==================== OpenGL 投影矩阵 ====================

        /**
         * @brief 创建2D正交投影矩阵
         * @param left   视图左边界
         * @param right  视图右边界
         * @param bottom 视图下边界
         * @param top    视图上边界
         * @return 正交投影矩阵
         *
         * 将[left, right] x [bottom, top]映射到[-1, 1] x [-1, 1]
         */
        static Matrix ortho2D(T left, T right, T bottom, T top)
        {
            if (right == left || top == bottom)
            {
                throw std::runtime_error("Invalid orthographic projection parameters");
            }

            Matrix result = identity();
            result.at(0, 0) = T(2) / (right - left);
            result.at(1, 1) = T(2) / (top - bottom);
            result.at(0, 2) = -(right + left) / (right - left);
            result.at(1, 2) = -(top + bottom) / (top - bottom);
            return result;
        }

        /**
         * @brief 创建视图变换矩阵
         * @param x      视图左下角X坐标
         * @param y      视图左下角Y坐标
         * @param width  视图宽度
         * @param height 视图高度
         * @return 视图变换矩阵
         *
         * 将NDC [-1, 1] x [-1, 1] 映射到屏幕坐标 [x, x+width] x [y, y+height]
         */
        static Matrix viewport(T x, T y, T width, T height)
        {
            Matrix result = identity();
            result.at(0, 0) = width / T(2);
            result.at(1, 1) = height / T(2);
            result.at(0, 2) = x + width / T(2);
            result.at(1, 2) = y + height / T(2);
            return result;
        }

        // ==================== CAD 常用变换 ====================

        /**
         * @brief 创建从世界坐标到屏幕坐标的变换矩阵
         * @param worldCenter 世界坐标中心点
         * @param screenCenter 屏幕坐标中心点
         * @param zoom 缩放因子
         * @return 组合变换矩阵
         */
        static Matrix worldToScreen(const Vec<T, 2>& worldCenter, const Vec<T, 2>& screenCenter, T zoom)
        {
            // 先平移世界中心到原点，再缩放，最后平移到屏幕中心
            // 注意：屏幕坐标Y轴通常向下，需要翻转
            return translate(screenCenter) * scale(zoom, -zoom) * translate(-worldCenter.data[0], -worldCenter.data[1]);
        }

        /**
         * @brief 创建从屏幕坐标到世界坐标的变换矩阵
         * @param worldCenter 世界坐标中心点
         * @param screenCenter 屏幕坐标中心点
         * @param zoom 缩放因子
         * @return 组合变换矩阵
         */
        static Matrix screenToWorld(const Vec<T, 2>& worldCenter, const Vec<T, 2>& screenCenter, T zoom)
        {
            return worldToScreen(worldCenter, screenCenter, zoom).inverse();
        }
    };

    // ==================== 全局运算符 ====================

    /// 标量 * 矩阵
    template <typename T>
    inline Matrix<T> operator*(T scalar, const Matrix<T>& mat)
    {
        return mat * scalar;
    }

    // ==================== 常用类型别名 ====================

    using Mat3i = Matrix<int>;
    using Mat3f = Matrix<float>;
    using Mat = Matrix<double>;
    using Mat3 = Matrix<double>;
    using Mat3d = Matrix<double>;

    // 默认使用 double 精度
    using Matrix3 = Matrix<double>;
} // namespace Ut