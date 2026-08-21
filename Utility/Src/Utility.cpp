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
// 显式实例化模板类 (visibility 由 CMake -fvisibility=default 控制)
// =====================================================

// Matrix 模板类显式实例化
template class Ut::Matrix<int>;
template class Ut::Matrix<float>;
template class Ut::Matrix<double>;