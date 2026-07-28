# Utility Library (Utility.dll)

> **SanYi CAD 核心工具库** — 提供数学运算（向量、矩阵）、颜色、边界框等基础数据结构和算法。

---

## 目录

- [功能描述](#功能描述)
- [使用方法](#使用方法)
  - [在 CMake 项目中链接此库](#在-cmake-项目中链接此库)
  - [如何 include 头文件](#如何-include-头文件)
- [设计框架](#设计框架)
  - [模块结构](#模块结构)
  - [主要类说明](#主要类说明)
  - [模板显式实例化机制](#模板显式实例化机制)
- [依赖库](#依赖库)
  - [无外部依赖](#无外部依赖)
  - [可选: bshoshany-thread-pool](#可选-bshoshany-thread-pool)
- [构建配置](#构建配置)
  - [CMake 配置说明](#cmake-配置说明)
  - [构建选项](#构建选项)
- [API 概要](#api-概要)
  - [Ut::Vec\<T, N\> — 向量](#utvect-t-n--向量)
  - [Ut::Matrix\<T\> — 3x3 矩阵](#utmatrixt--3x3-矩阵)
  - [Ut::Matrix4\<T\> — 4x4 矩阵](#utmatrix4t--4x4-矩阵)
  - [Ut::Color — 颜色](#utcolor--颜色)
  - [Ut::BBox2\<T\> — 2D 边界框](#utbbox2t--2d-边界框)
  - [Ut::BBox3\<T\> — 3D 边界框](#utbbox3t--3d-边界框)
  - [Ut::GeomMath — 数学工具](#utgeommath--数学工具)
  - [渲染数据结构](#渲染数据结构)
- [版本信息](#版本信息)

---

## 功能描述

Utility 库是 SanYi CAD 项目的核心基础模块，提供了 CAD 系统中最常用的基础数据结构和算法：

- **向量运算**：二维、三维、四维向量的完整算术运算、点积、叉积、归一化、投影、反射、插值等
- **矩阵运算**：3x3 和 4x4 矩阵，支持平移、旋转、缩放、镜像、投影等 2D/3D 变换
- **颜色管理**：RGBA 颜色空间，支持 HSV/HSL 转换、颜色混合、亮度调整、预设颜色等
- **边界框**：2D/3D 轴对齐包围盒，支持扩展、相交、包含判断、膨胀/收缩等操作
- **数学工具**：浮点容差比较、角度归一化、区间判断等基础数值操作
- **渲染数据**：为渲染引擎提供批量渲染数据结构（兼容 OpenGL）

所有类均定义在 `Ut` 命名空间下。

---

## 使用方法

### 在 CMake 项目中链接此库

```cmake
# 方式一：子目录方式（直接将 Utility 作为子项目引入）
add_subdirectory(Utility)

# 方式二：通过 find_package（如果安装为独立包）
find_package(Utility REQUIRED)

# 链接到你的目标
target_link_libraries(YourTarget PRIVATE Utility)
```

### 如何 include 头文件

Utility 库的头文件按功能分目录组织，所有 include 路径已在 CMake 中配置为 PUBLIC，只需包含相应的头文件：

```cpp
// 向量
#include "Vec/Vec.hpp"

// 3x3 矩阵 (2D 变换)
#include "Mat/Mat.hpp"

// 4x4 矩阵 (3D 变换)
#include "Mat/Mat4.hpp"

// 颜色
#include "Color/Color.hpp"

// 2D 边界框
#include "BBox/BBox2d.hpp"

// 3D 边界框
#include "BBox/BBox3.hpp"

// 数学工具（容差比较、角度归一化等）
#include "Ut/GeomMath.h"

// 渲染数据结构
#include "Ut/RenderData.h"

// 场景环境设置
#include "Ut/SceneEnvironmentSettings.h"
```

**命名空间**：所有类型均位于 `Ut` 命名空间下。

**导出宏**：使用 `UTILITY_API` 标记导出的类和函数（定义在 `UtilityAPI.h`）。

---

## 设计框架

### 模块结构

```
Utility/
├── CMakeLists.txt              # 构建配置
├── Include/                    # 头文件
│   ├── UtilityAPI.h            # DLL 导出/导入宏定义
│   ├── Def.h                   # 通用宏定义 (M_PI 等)
│   ├── Vec/
│   │   └── Vec.hpp             # 向量类模板
│   ├── Mat/
│   │   ├── Mat.hpp             # 3x3 矩阵类模板
│   │   └── Mat4.hpp            # 4x4 矩阵类模板
│   ├── Color/
│   │   └── Color.hpp           # 颜色类
│   ├── BBox/
│   │   ├── BBox2d.hpp          # 2D 边界框类模板
│   │   └── BBox3.hpp           # 3D 边界框类模板
│   └── Ut/                     # 实用工具（旧版兼容层）
│       ├── GeomMath.h          # 数学工具（容差、角度等）
│       ├── RenderData.h        # 渲染数据结构
│       ├── SceneEnvironmentSettings.h  # 场景环境设置
│       └── Def.h               # 常量定义
├── Src/                        # 源文件
│   ├── Utility.cpp             # 主入口 + 模板显式实例化
│   ├── Vec.cpp                 # Vec 模板显式实例化
│   ├── Color.cpp               # Color 实现
│   └── BBox2d.cpp              # BBox2 模板显式实例化
└── Test/                       # 单元测试
    ├── CMakeLists.txt
    ├── VecTests.cpp
    ├── GeomMathTests.cpp
    ├── BBox2dTests.cpp
    └── README.md
```

### 主要类说明

| 类名 | 命名空间 | 说明 | 头文件 |
|------|----------|------|--------|
| `Vec<T, N>` | `Ut` | 向量模板类，支持 2D/3D/4D | `Vec/Vec.hpp` |
| `Matrix<T>` | `Ut` | 3x3 矩阵（列主序，2D 变换） | `Mat/Mat.hpp` |
| `Matrix4<T>` | `Ut` | 4x4 矩阵（列主序，OpenGL 兼容） | `Mat/Mat4.hpp` |
| `Color` | `Ut` | RGBA 颜色类（0-1 浮点范围） | `Color/Color.hpp` |
| `BBox2<T>` | `Ut` | 2D 轴对齐包围盒 | `BBox/BBox2d.hpp` |
| `BBox3<T>` | `Ut` | 3D 轴对齐包围盒 | `BBox/BBox3.hpp` |
| `GeomMath` | `Ut` | 数学工具（纯静态方法，header-only） | `Ut/GeomMath.h` |
| `RenderData` 系列 | `Ut` | 渲染数据结构（RenderBatch 等） | `Ut/RenderData.h` |
| `SceneEnvironmentSettings` | `Ut` | 场景环境配置（台面、网格、标尺） | `Ut/SceneEnvironmentSettings.h` |

#### Vec\<T, N\> — 向量

向量模板类支持 `int`、`float`、`double` 类型，支持 2/3/4 个维度：

```cpp
Ut::Vec2d v1(1.0, 2.0);          // 二维 double 向量
Ut::Vec3f v2(1.0f, 2.0f, 3.0f);  // 三维 float 向量
Ut::Vec4d v3(1.0, 2.0, 3.0, 1.0); // 四维齐次坐标向量

// 运算
Ut::Vec3d sum = v2 + Ut::Vec3d(1, 2, 3);
double dot = v1.dot(Ut::Vec2d(3, 4));
Ut::Vec3d cross = v2.cross(Ut::Vec3f(1, 0, 0));
Ut::Vec3d norm = v2.normalized();
```

**预定义类型别名：**
- `Vec2i`, `Vec2f`, `Vec2`/`Vec2d` — 二维向量
- `Vec3i`, `Vec3f`, `Vec3`/`Vec3d` — 三维向量
- `Vec4f`, `Vec4d`, `Vec4` — 四维向量
- `Point2i`, `Point2f`, `Point2`/`Point2d` — 二维点
- `Point3i`, `Point3f`, `Point3`/`Point3d` — 三维点
- `Vec2dVector`, `Vec3dVector` 等 — 向量/点容器别名

#### Matrix\<T\> — 3x3 矩阵

用于 2D 几何变换，采用列主序存储：

```cpp
Ut::Mat3d mat = Ut::Matrix<double>::rotateDegrees(45.0);
Ut::Vec2d transformed = mat.transformPoint(Ut::Vec2d(100, 200));
Ut::Mat3d inv = mat.inverse();
```

**主要功能：**
- 2D 变换：`translate()`, `rotate()`, `scale()`, `shear()`, `mirror()`
- 视图投影：`ortho2D()`, `viewport()`
- CAD 常用：`worldToScreen()`, `screenToWorld()`
- 矩阵运算：转置、行列式、逆矩阵

#### Matrix4\<T\> — 4x4 矩阵

用于 3D 变换，列主序存储，兼容 OpenGL：

```cpp
Ut::Mat4f view = Ut::Matrix4<float>::lookAt(eye, center, up);
Ut::Mat4f proj = Ut::Matrix4<float>::perspective(fov, aspect, near, far);
Ut::Mat4f model = Ut::Matrix4<float>::translate(1, 0, 0) *
                 Ut::Matrix4<float>::rotateZ(1.57f);
```

**主要功能：**
- 3D 变换：`translate()`, `scale()`, `rotateX/Y/Z()`, `rotate(axis)`
- 视图：`lookAt()`
- 投影：`perspective()`, `ortho()`
- 变换方法：`transformPoint()`, `transformDirection()`

#### Color — 颜色

RGBA 颜色类，使用 0-1 浮点范围（OpenGL 兼容）：

```cpp
Ut::Color c1(1.0f, 0.0f, 0.0f, 1.0f);           // 红色
Ut::Color c2 = Ut::Color::fromHex("#FF0000");     // 从十六进制
Ut::Color c3 = Ut::Color::fromRGB255(255, 0, 0);  // 从 0-255
Ut::Color blended = c1.blend(c2, 0.5f);           // 混合
```

**预定义颜色：** `Black()`, `White()`, `Red()`, `Green()`, `Blue()`, `Yellow()`, `Magenta()`, `Cyan()`, `Gray()`, `Transparent()`

**颜色空间转换：** HSV、HSL 双向转换

#### BBox2\<T\> — 2D 边界框

```cpp
Ut::BBox2d box(0, 0, 100, 200);           // 从坐标构造
box.expand(Ut::Vec2d(150, 250));          // 扩展
bool inside = box.contains(Ut::Vec2d(50, 50));
bool hit = box.intersects(otherBox);
Ut::BBox2d inflated = box.inflated(10.0); // 膨胀
```

**预定义别名：** `Box`, `Rect`, `Range` 均为 `BBox2<double>` 的别名

#### BBox3\<T\> — 3D 边界框

与 BBox2 类似，增加了三维空间的操作：

```cpp
Ut::BBox3d bbox(0, 0, 0, 100, 100, 100);
Ut::Vec3d c = bbox.center();
Ut::Vec3d s = bbox.size();
```

### 模板显式实例化机制

为了减小编译体积并加快编译速度，Utility 库采用了 **模板显式实例化（Explicit Template Instantiation）** 机制：

#### 工作原理

1. **在头文件中**，模板类声明使用 `UT_EXTERN_TEMPLATE` 修饰符标记为 `extern`，告诉编译器不要在每个翻译单元中实例化：

```cpp
// Vec/Vec.hpp
UT_EXTERN_TEMPLATE template class Ut::Vec<int, 2>;
UT_EXTERN_TEMPLATE template class Ut::Vec<float, 2>;
UT_EXTERN_TEMPLATE template class Ut::Vec<double, 2>;
// ... 其他特化
```

2. **在源文件中**，使用不带 `extern` 的 `template class` 定义来强制实例化：

```cpp
// Src/Vec.cpp
template class Ut::Vec<int, 2>;
template class Ut::Vec<float, 2>;
template class Ut::Vec<double, 2>;
// ...
```

3. **CMake 配置**：库编译时定义 `UTILITY_EXTERN_TEMPLATES` 宏，将 `UT_EXTERN_TEMPLATE` 展开为 `extern`；消费方（使用此库的项目）通过 `PUBLIC` 编译定义也会获得此宏。

#### 已显式实例化的类型

| 类 | 已实例化的特化 |
|----|----------------|
| `Vec<T, N>` | `<int,2>`, `<float,2>`, `<double,2>`, `<int,3>`, `<float,3>`, `<double,3>`, `<float,4>`, `<double,4>` |
| `Matrix<T>` | `<int>`, `<float>`, `<double>` |
| `BBox2<T>` | `<float>`, `<double>` |
| `BBox3<T>` | 无（header-only） |
| `Matrix4<T>` | 无（header-only） |

#### 添加新类型特化

如需新增某个类型的显式实例化（例如 `Vec<long double, 2>`），需要：

1. 在头文件中添加声明：
```cpp
UT_EXTERN_TEMPLATE template class Ut::Vec<long double, 2>;
```

2. 在源文件中添加定义：
```cpp
template class Ut::Vec<long double, 2>;
```

---

## 依赖库

### 无外部依赖

Utility 库的核心功能**不依赖任何外部库**，仅使用 C++ 标准库（`<cmath>`, `<algorithm>`, `<stdexcept>`, `<type_traits>`, `<limits>`, `<vector>`, `<array>`, `<string>`, `<cstdint>`）。

### 可选: bshoshany-thread-pool

用于并行计算的 header-only 库。如果系统中检测到此库，会自动将其包含到 include 路径中。

#### 安装方法

**通过 vcpkg 安装：**

```bash
vcpkg install bshoshany-thread-pool:x64-windows
vcpkg install bshoshany-thread-pool:x64-linux
vcpkg install bshoshany-thread-pool:arm64-osx
```

**通过 vcpkg manifest 模式集成（推荐）：**

在项目根目录创建 `vcpkg.json`：

```json
{
  "name": "sanyi-cad",
  "version-string": "1.0.0",
  "dependencies": [
    "bshoshany-thread-pool"
  ]
}
```

然后配置 CMake 时指定 vcpkg 工具链：

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake ...
```

**手动安装：**

也可以直接从 GitHub 下载 header 文件：

```bash
git clone https://github.com/bshoshany/thread-pool.git
# 将 BS_thread_pool.hpp 放入项目的第三方头文件目录
```

CMake 会通过 `find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")` 自动检测。

---

## 构建配置

### CMake 配置说明

#### 独立构建

```bash
cd Utility
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

#### 作为子项目构建

```cmake
# 在主项目的 CMakeLists.txt 中
add_subdirectory(Utility)
target_link_libraries(YourTarget PRIVATE Utility)
```

#### CMake 变量说明

| 变量 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `BUILD_UTILITY_TESTS` | `option` | `OFF` | 是否构建单元测试 |
| `SANYI_ROOT` | `PATH` | 自动检测 | SanYi 项目根目录 |

#### 编译特性

- **C++ 标准**：C++17（`cxx_std_17`）
- **字符编码**：UTF-8（MSVC: `/utf-8`）
- **DLL 后缀**：Debug 版本添加 `_d` 后缀
- **导出宏**：`UTILITY_EXPORTS`（库内部使用）、`UTILITY_EXTERN_TEMPLATES`（控制模板实例化）

#### 平台支持

| 平台 | 导出方式 |
|------|----------|
| Windows (MSVC) | `__declspec(dllexport)` / `__declspec(dllimport)` |
| Linux (GCC/Clang) | `__attribute__((visibility("default")))` |
| macOS (Clang) | `__attribute__((visibility("default")))` |

### 构建选项

#### 启用单元测试

```bash
cmake .. -DBUILD_UTILITY_TESTS=ON
cmake --build .
ctest --test-dir .
```

测试框架使用 Google Test (GTest)，需要提前安装。

#### 指定 bshoshany-thread-pool 路径

```bash
cmake .. -DBSHOSHANY_THREAD_POOL_INCLUDE_DIRS="/path/to/thread-pool/header"
```

---

## API 概要

### Ut::Vec\<T, N\> — 向量

| 分类 | 方法/运算符 | 说明 |
|------|------------|------|
| **构造** | `Vec()`, `Vec(value)`, `Vec(x,y)`, `Vec(x,y,z)`, `Vec(x,y,z,w)` | 多维度构造 |
| **访问** | `x()`, `y()`, `z()`, `w()`, `operator[]` | 分量访问（带越界检查） |
| **算术** | `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=` | 向量四则运算 |
| **比较** | `==`, `!=` | 逐分量比较 |
| **向量运算** | `dot()`, `cross()`, `cross2D()` | 点积、叉积 |
| **长度** | `length()`, `lengthSquared()` | 向量长度 |
| **距离** | `distance()`, `distanceSquared()` | 两点距离 |
| **归一化** | `normalized()`, `normalize()` | 归一化（返回新值 / 原地） |
| **判断** | `isZero()`, `isUnit()` | 零向量/单位向量判断 |
| **角度** | `angle()`, `angleDegrees()` | 两向量夹角 |
| **投影/反射** | `project()`, `reflect()` | 投影和反射 |
| **插值** | `lerp()` | 线性插值 |
| **极值** | `min()`, `max()`, `clamp()` | 分量级极值运算 |

### Ut::Matrix\<T\> — 3x3 矩阵

| 分类 | 方法 | 说明 |
|------|------|------|
| **构造** | `Matrix()`, `Matrix(diagonal)`, `Matrix(m00,...,m22)` | 单位矩阵/对角/全元素 |
| **静态工厂** | `identity()`, `zero()` | 单位矩阵、零矩阵 |
| **访问** | `at(row,col)`, `operator()`, `operator[]`, `column()`, `row()` | 元素和行列访问 |
| **算术** | `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=` | 矩阵运算 |
| **矩阵×向量** | `operator*(Vec)`, `transformPoint()`, `transformVector()` | 向量变换 |
| **矩阵运算** | `transposed()`, `transpose()`, `determinant()`, `inverse()` | 转置、行列式、逆 |
| **判断** | `isIdentity()`, `isZero()`, `isInvertible()`, `equals()` | 状态判断 |
| **2D 变换** | `translate()`, `rotate()`, `rotateDegrees()`, `rotateAround()`, `scale()`, `scaleAround()`, `shear()` | 2D 变换生成 |
| **镜像** | `mirrorX()`, `mirrorY()`, `mirror()`, `mirrorLine()` | 镜像变换 |
| **投影** | `ortho2D()`, `viewport()` | 正交投影、视口变换 |
| **CAD** | `worldToScreen()`, `screenToWorld()` | 世界/屏幕坐标互转 |

### Ut::Matrix4\<T\> — 4x4 矩阵

| 分类 | 方法 | 说明 |
|------|------|------|
| **构造** | `Matrix4()`, `Matrix4(diagonal)`, `Matrix4(m00,...,m33)` | 单位/对角/全元素 |
| **静态工厂** | `identity()`, `zero()` | 单位、零矩阵 |
| **访问** | `at()`, `operator()`, `operator[]`, `column()` | 元素访问 |
| **算术** | `*`, `*=`, `operator*(Vec<T,4>)` | 矩阵乘法、矩阵×向量 |
| **变换** | `transformPoint()`, `transformDirection()` | 3D 点/方向变换 |
| **矩阵运算** | `transposed()`, `determinant()`, `inverse()` | 转置、行列式、逆（Gauss-Jordan） |
| **3D 变换** | `translate()`, `scale()`, `rotateX/Y/Z()`, `rotate(axis)` | 3D 变换生成 |
| **视图** | `lookAt()` | LookAt 视图矩阵 |
| **投影** | `perspective()`, `ortho()` | 透视/正交投影 |

### Ut::Color — 颜色

| 分类 | 方法 | 说明 |
|------|------|------|
| **构造** | `Color()`, `Color(r,g,b,a)` | 默认黑色 / RGBA 构造（0-1 范围） |
| **创建** | `fromRGB255()`, `fromHex()`, `fromHSV()`, `fromHSL()` | 多种颜色空间创建 |
| **获取** | `red()/r()`, `green()/g()`, `blue()/b()`, `alpha()/a()` | 0-1 范围分量 |
| **获取 (255)** | `red255()`, `green255()`, `blue255()`, `alpha255()` | 0-255 范围分量 |
| **HSV/HSL** | `getHSV()`, `getHSL()`, `hue()`, `saturation()`, `value()`, `lightness()` | HSV/HSL 分量 |
| **设置** | `setRGBA()`, `setRed()`, `setGreen()`, `setBlue()`, `setAlpha()` | 颜色分量设置 |
| **运算** | `+`, `-`, `*`, `/`, `==`, `!=` | 颜色算术和比较 |
| **操作** | `blend()`, `lighten()`, `darken()`, `saturate()`, `fade()` | 颜色调整 |
| **分析** | `luminance()`, `contrast()` | 亮度和对比度 |
| **索引** | `toIndex()`, `fromIndex()`, `hash()`, `toPaletteIndex()` | 索引和哈希 |
| **转换** | `toHexRGB()`, `toHexRGBA()`, `toCSS()` | 格式转换 |
| **OpenGL** | `data()`, `toArray()`, `toGLFloatArray()` | OpenGL 兼容接口 |
| **预设** | `Black()`, `White()`, `Red()`, `Green()`, `Blue()`, `Yellow()`, `Magenta()`, `Cyan()`, `Gray()`, `Transparent()` | 常用颜色 |

### Ut::BBox2\<T\> — 2D 边界框

| 分类 | 方法 | 说明 |
|------|------|------|
| **构造** | `BBox2()`, `BBox2(p1,p2)`, `BBox2(minX,minY,maxX,maxY)` | 多种构造方式 |
| **基本操作** | `reset()`, `isValid()`, `expand(point)`, `expand(bbox)` | 重置/验证/扩展 |
| **查询** | `width()`, `height()`, `center()`, `diagonal()`, `area()` | 几何属性 |
| **包含** | `contains(point)`, `contains(bbox)` | 包含判断 |
| **相交** | `intersects(bbox)`, `intersection(bbox)`, `united(bbox)` | 相交判断和运算 |
| **变换** | `inflated()`, `deflated()` | 膨胀/收缩 |
| **比较** | `==`, `!=` | 相等比较 |

### Ut::BBox3\<T\> — 3D 边界框

| 分类 | 方法 | 说明 |
|------|------|------|
| **构造** | `BBox3()`, `BBox3(p1,p2)`, `BBox3(minX,minY,minZ,maxX,maxY,maxZ)` | 3D 构造 |
| **基本操作** | `reset()`, `isValid()`, `expand()`, `contains()` | 基础操作 |
| **查询** | `center()`, `size()`, `diagonal()`, `maxExtent()` | 几何属性 |
| **相交** | `intersects()` | 相交判断 |

### Ut::GeomMath — 数学工具

| 分类 | 方法 | 说明 |
|------|------|------|
| **容差比较** | `isZero()`, `almostEqual()`, `lessOrEqual()`, `greaterOrEqual()` | 带容差的浮点比较 |
| **区间工具** | `clamp()`, `clamp01()`, `lerp()` | 限制和插值 |
| **角度工具** | `radToDeg()`, `degToRad()`, `normalizeAngle0To2Pi()`, `normalizeAnglePiToPi()`, `angleDiff()` | 角度转换和归一化 |
| **区间判断** | `inRange()`, `inRange01()` | 区间检查（带容差） |
| **符号工具** | `sign()` | 返回 -1/0/1 |

### 渲染数据结构

定义在 `Ut/RenderData.h` 中：

| 结构体 | 说明 |
|--------|------|
| `RenderPrimitiveType` | 渲染图元类型枚举（Points, Lines, Triangles 等） |
| `RenderBatch` | 2D 渲染批次（顶点 + 颜色 + 线宽） |
| `RenderDataPackage` | 2D 渲染数据包（含矩阵和视口） |
| `RenderBatch3D` | 3D 渲染批次（含法线和索引） |
| `RenderDataPackage3D` | 3D 渲染数据包 |
| `MeshVertex` | 网格顶点（位置 + 法线） |
| `MeshData` | 网格数据（顶点 + 索引） |
| `RenderVertex` | 渲染顶点（位置 + 颜色） |
| `RenderCommand` | 单条渲染命令 |
| `RenderCommandList` | 渲染命令列表 |

### 场景环境设置

定义在 `Ut/SceneEnvironmentSettings.h` 中：

| 结构体 | 说明 |
|--------|------|
| `TableSettings` | 工作台面设置（尺寸、颜色、Z 层级） |
| `GridSettings` | 网格设置（可见性、密度、颜色、线宽） |
| `RulerPosition` | 标尺位置枚举（Top, Left） |
| `RulerSettings` | 标尺设置（刻度、字号、颜色） |
| `SceneEnvironmentSettings` | 整体场景环境配置（聚合以上所有） |

---

## 版本信息

- **当前版本**：`1.0.0`
- **C++ 标准**：C++17
- **构建类型**：Shared Library (DLL)
- **导出宏**：`UTILITY_API`
- **模板实例化宏**：`UT_EXTERN_TEMPLATE`
- **项目**：SanYi CAD — Core Utility Library

---

*© SanYi CAD Project*