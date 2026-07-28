# Utility 测试

工具库单元测试。

## 测试文件

| 文件 | 测试内容 |
|------|----------|
| VecTests.cpp | 向量运算（2D/3D 向量、算术、点积、叉积、归一化） |
| BBox2dTests.cpp | 2D 包围盒（构造、扩展、包含、相交、合并） |
| GeomMathTests.cpp | 基础数学工具（容差比较、区间、角度、符号） |

## 运行测试

```bash
# 编译
cmake --build build --target UtilityTests

# 运行
./build/bin_Qt6/Release/UtilityTests
```
