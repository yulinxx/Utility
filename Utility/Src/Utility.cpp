#include "UtilityAPI.h"
#include "Vec/Vec.hpp"
#include "Mat/Mat.hpp"
#include "BBox/BBox2d.hpp"

// 用于测试验证链接/加载
extern "C" UTILITY_API int SanYiUtilityVersion()
{
    return 1;
}


template class Ut::Matrix<int>;
template class Ut::Matrix<float>;
template class Ut::Matrix<double>;