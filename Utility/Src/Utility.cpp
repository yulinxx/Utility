#include "UtilityAPI.h"
#include "Vec/Vec.hpp"
#include "Mat/Mat.hpp"
#include "BBox/BBox2d.hpp"

// 用于测试验证链接/加载
extern "C" UTILITY_API int SanYiUtilityVersion()
{
    return 1;
}

// =====================================================
// 显式实例化模板类
// =====================================================

// Vec 模板类显式实例化
// 二维向量
template class Ut::Vec<int, 2>;
template class Ut::Vec<float, 2>;
template class Ut::Vec<double, 2>;

// 三维向量
template class Ut::Vec<int, 3>;
template class Ut::Vec<float, 3>;
template class Ut::Vec<double, 3>;

// Matrix 模板类显式实例化
template class Ut::Matrix<int>;
template class Ut::Matrix<float>;
template class Ut::Matrix<double>;

// BBox2 模板类显式实例化
template class Ut::BBox2<float>;
template class Ut::BBox2<double>;