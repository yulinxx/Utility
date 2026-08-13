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
     * @brief 4x4 矩阵模板类，用于3D变换、投影等
     * @tparam T 数据类型 (float, double)
     *
     * 矩阵存储方式：列主序 (Column-Major), 兼容 OpenGL
     * 布局:
     *   | m[0]  m[4]  m[8]   m[12] |   | m00  m01  m02  m03 |
     *   | m[1]  m[5]  m[9]   m[13] | = | m10  m11  m12  m13 |
     *   | m[2]  m[6]  m[10]  m[14] |   | m20  m21  m22  m23 |
     *   | m[3]  m[7]  m[11]  m[15] |   | m30  m31  m32  m33 |
     */
    template<typename T>
    class Matrix4
    {
    public:
        T data[16];

        // ==================== 构造函数 ====================

        Matrix4()
        {
            for (int i = 0; i < 16; ++i)
            {
                data[i] = T(0);
            }
            data[0] = data[5] = data[10] = data[15] = T(1);
        }

        explicit Matrix4(T diagonal)
        {
            for (int i = 0; i < 16; ++i)
            {
                data[i] = T(0);
            }
            data[0] = data[5] = data[10] = data[15] = diagonal;
        }

        Matrix4(
            T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
        {
            data[0] = m00;
            data[4] = m01;
            data[8] = m02;
            data[12] = m03;
            data[1] = m10;
            data[5] = m11;
            data[9] = m12;
            data[13] = m13;
            data[2] = m20;
            data[6] = m21;
            data[10] = m22;
            data[14] = m23;
            data[3] = m30;
            data[7] = m31;
            data[11] = m32;
            data[15] = m33;
        }

        explicit Matrix4(const T* arr)
        {
            for (int i = 0; i < 16; ++i)
            {
                data[i] = arr[i];
            }
        }

        // ==================== 访问器 ====================

        T& at(int row, int col)
        {
            return data[col * 4 + row];
        }

        const T& at(int row, int col) const
        {
            return data[col * 4 + row];
        }

        T& operator()(int row, int col)
        {
            return at(row, col);
        }

        const T& operator()(int row, int col) const
        {
            return at(row, col);
        }

        T& operator[](int index)
        {
            return data[index];
        }

        const T& operator[](int index) const
        {
            return data[index];
        }

        Vec<T, 4> column(int col) const
        {
            return Vec<T, 4>(data[col * 4], data[col * 4 + 1], data[col * 4 + 2], data[col * 4 + 3]);
        }

        void setColumn(int col, const Vec<T, 4>& v)
        {
            data[col * 4] = v[0];
            data[col * 4 + 1] = v[1];
            data[col * 4 + 2] = v[2];
            data[col * 4 + 3] = v[3];
        }

        T* ptr()
        {
            return data;
        }

        const T* ptr() const
        {
            return data;
        }

        // ==================== 静态 ====================

        static Matrix4 identity()
        {
            return Matrix4(T(1));
        }

        static Matrix4 zero()
        {
            return Matrix4(T(0));
        }

        // ==================== 算术运算 ====================

        Matrix4 operator*(const Matrix4& other) const
        {
            Matrix4 result(T(0));
            for (int col = 0; col < 4; ++col)
            {
                for (int row = 0; row < 4; ++row)
                {
                    for (int k = 0; k < 4; ++k)
                    {
                        result.at(row, col) += at(row, k) * other.at(k, col);
                    }
                }
            }
            return result;
        }

        Vec<T, 4> operator*(const Vec<T, 4>& v) const
        {
            Vec<T, 4> result;
            for (int row = 0; row < 4; ++row)
            {
                result[row] = at(row, 0) * v[0] + at(row, 1) * v[1] + at(row, 2) * v[2] + at(row, 3) * v[3];
            }
            return result;
        }

        /// 变换3D点 (w=1, 考虑平移)
        Vec<T, 3> transformPoint(const Vec<T, 3>& p) const
        {
            Vec<T, 4> v(p[0], p[1], p[2], T(1));
            Vec<T, 4> r = *this * v;
            return Vec<T, 3>(r[0] / r[3], r[1] / r[3], r[2] / r[3]);
        }

        /// 变换3D方向 (w=0, 忽略平移)
        Vec<T, 3> transformDirection(const Vec<T, 3>& d) const
        {
            Vec<T, 4> v(d[0], d[1], d[2], T(0));
            Vec<T, 4> r = *this * v;
            return Vec<T, 3>(r[0], r[1], r[2]);
        }

        Matrix4 operator*(T scalar) const
        {
            Matrix4 result;
            for (int i = 0; i < 16; ++i)
            {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }

        Matrix4& operator*=(const Matrix4& other)
        {
            *this = *this * other;
            return *this;
        }

        // ==================== 矩阵运算 ====================

        Matrix4 transposed() const
        {
            Matrix4 result;
            for (int row = 0; row < 4; ++row)
            {
                for (int col = 0; col < 4; ++col)
                {
                    result.at(row, col) = at(col, row);
                }
            }
            return result;
        }

        T determinant() const
        {
            // 使用余子式展开
            T m[4][4];
            for (int i = 0; i < 16; ++i)
            {
                m[i % 4][i / 4] = data[i];
            }

            T det = T(0);
            for (int i = 0; i < 4; ++i)
            {
                T sub[3][3];
                for (int r = 1; r < 4; ++r)
                {
                    int sc = 0;
                    for (int c = 0; c < 4; ++c)
                    {
                        if (c == i)
                        {
                            continue;
                        }
                        sub[r - 1][sc++] = m[r][c];
                    }
                }
                T subDet = sub[0][0] * (sub[1][1] * sub[2][2] - sub[1][2] * sub[2][1]) -
                    sub[0][1] * (sub[1][0] * sub[2][2] - sub[1][2] * sub[2][0]) +
                    sub[0][2] * (sub[1][0] * sub[2][1] - sub[1][1] * sub[2][0]);
                det += (i % 2 == 0 ? T(1) : T(-1)) * m[0][i] * subDet;
            }
            return det;
        }

        Matrix4 inverse() const
        {
            // Gauss-Jordan elimination
            Matrix4 inv;
            T a[4][8];
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    a[i][j] = at(i, j);
                    a[i][j + 4] = (i == j) ? T(1) : T(0);
                }
            }

            for (int i = 0; i < 4; ++i)
            {
                if (std::abs(a[i][i]) < T(1e-10))
                {
                    int pivot = i + 1;
                    while (pivot < 4 && std::abs(a[pivot][i]) < T(1e-10))
                    {
                        ++pivot;
                    }
                    if (pivot == 4)
                    {
                        throw std::runtime_error("Matrix is singular");
                    }
                    for (int j = 0; j < 8; ++j)
                    {
                        std::swap(a[i][j], a[pivot][j]);
                    }
                }
                T pivot = a[i][i];
                for (int j = 0; j < 8; ++j)
                {
                    a[i][j] /= pivot;
                }
                for (int k = 0; k < 4; ++k)
                {
                    if (k == i)
                    {
                        continue;
                    }
                    T factor = a[k][i];
                    for (int j = 0; j < 8; ++j)
                    {
                        a[k][j] -= factor * a[i][j];
                    }
                }
            }

            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    inv.at(i, j) = a[i][j + 4];
                }
            }
            return inv;
        }

        // ==================== 3D 变换矩阵生成 ====================

        /// 3D平移矩阵
        static Matrix4 translate(T tx, T ty, T tz)
        {
            Matrix4 m;
            m.at(0, 3) = tx;
            m.at(1, 3) = ty;
            m.at(2, 3) = tz;
            return m;
        }

        static Matrix4 translate(const Vec<T, 3>& t)
        {
            return translate(t[0], t[1], t[2]);
        }

        /// 3D缩放矩阵
        static Matrix4 scale(T sx, T sy, T sz)
        {
            Matrix4 m;
            m.at(0, 0) = sx;
            m.at(1, 1) = sy;
            m.at(2, 2) = sz;
            return m;
        }

        static Matrix4 scale(T s)
        {
            return scale(s, s, s);
        }

        static Matrix4 scale(const Vec<T, 3>& s)
        {
            return scale(s[0], s[1], s[2]);
        }

        /// 绕X轴旋转 (弧度)
        static Matrix4 rotateX(T radians)
        {
            T c = std::cos(radians);
            T s = std::sin(radians);
            Matrix4 m;
            m.at(1, 1) = c;
            m.at(1, 2) = -s;
            m.at(2, 1) = s;
            m.at(2, 2) = c;
            return m;
        }

        /// 绕Y轴旋转 (弧度)
        static Matrix4 rotateY(T radians)
        {
            T c = std::cos(radians);
            T s = std::sin(radians);
            Matrix4 m;
            m.at(0, 0) = c;
            m.at(0, 2) = s;
            m.at(2, 0) = -s;
            m.at(2, 2) = c;
            return m;
        }

        /// 绕Z轴旋转 (弧度)
        static Matrix4 rotateZ(T radians)
        {
            T c = std::cos(radians);
            T s = std::sin(radians);
            Matrix4 m;
            m.at(0, 0) = c;
            m.at(0, 1) = -s;
            m.at(1, 0) = s;
            m.at(1, 1) = c;
            return m;
        }

        /// 绕任意轴旋转 (弧度, 轴需归一化)
        static Matrix4 rotate(T radians, const Vec<T, 3>& axis)
        {
            T c = std::cos(radians);
            T s = std::sin(radians);
            T t = T(1) - c;
            T x = axis[0], y = axis[1], z = axis[2];

            Matrix4 m;
            m.at(0, 0) = t * x * x + c;
            m.at(0, 1) = t * x * y - s * z;
            m.at(0, 2) = t * x * z + s * y;
            m.at(1, 0) = t * x * y + s * z;
            m.at(1, 1) = t * y * y + c;
            m.at(1, 2) = t * y * z - s * x;
            m.at(2, 0) = t * x * z - s * y;
            m.at(2, 1) = t * y * z + s * x;
            m.at(2, 2) = t * z * z + c;
            return m;
        }

        /// LookAt 视图矩阵
        static Matrix4 lookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
        {
            Vec<T, 3> f = (center - eye).normalized();
            Vec<T, 3> s = f.cross(up.normalized()).normalized();
            Vec<T, 3> u = s.cross(f);

            Matrix4 m;
            m.at(0, 0) = s[0];
            m.at(0, 1) = s[1];
            m.at(0, 2) = s[2];
            m.at(0, 3) = -s.dot(eye);
            m.at(1, 0) = u[0];
            m.at(1, 1) = u[1];
            m.at(1, 2) = u[2];
            m.at(1, 3) = -u.dot(eye);
            m.at(2, 0) = -f[0];
            m.at(2, 1) = -f[1];
            m.at(2, 2) = -f[2];
            m.at(2, 3) = f.dot(eye);
            m.at(3, 0) = T(0);
            m.at(3, 1) = T(0);
            m.at(3, 2) = T(0);
            m.at(3, 3) = T(1);
            return m;
        }

        /// 透视投影矩阵
        static Matrix4 perspective(T fovY, T aspect, T near, T far)
        {
            T tanHalfFov = std::tan(fovY * T(0.5));
            Matrix4 m(T(0));
            m.at(0, 0) = T(1) / (aspect * tanHalfFov);
            m.at(1, 1) = T(1) / tanHalfFov;
            m.at(2, 2) = -(far + near) / (far - near);
            m.at(2, 3) = -(T(2) * far * near) / (far - near);
            m.at(3, 2) = T(-1);
            return m;
        }

        /// 正交投影矩阵
        static Matrix4 ortho(T left, T right, T bottom, T top, T near, T far)
        {
            Matrix4 m;
            m.at(0, 0) = T(2) / (right - left);
            m.at(1, 1) = T(2) / (top - bottom);
            m.at(2, 2) = T(-2) / (far - near);
            m.at(0, 3) = -(right + left) / (right - left);
            m.at(1, 3) = -(top + bottom) / (top - bottom);
            m.at(2, 3) = -(far + near) / (far - near);
            return m;
        }
    };

    // ==================== 类型别名 ====================

    using Mat4f = Matrix4<float>;
    using Mat4d = Matrix4<double>;
    using Mat4 = Matrix4<float>;
}  // namespace Ut