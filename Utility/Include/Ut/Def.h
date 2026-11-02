#pragma once

#ifdef _WIN32
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
#endif

#if defined(_MSC_VER)
    #define SY_SUPPRESS_DEPRECATED_BEGIN __pragma(warning(push)) __pragma(warning(disable : 4996))
    #define SY_SUPPRESS_DEPRECATED_END   __pragma(warning(pop))
#elif defined(__clang__)
    #define SY_SUPPRESS_DEPRECATED_BEGIN \
        _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
    #define SY_SUPPRESS_DEPRECATED_END _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
    #define SY_SUPPRESS_DEPRECATED_BEGIN \
        _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
    #define SY_SUPPRESS_DEPRECATED_END _Pragma("GCC diagnostic pop")
#else
    #define SY_SUPPRESS_DEPRECATED_BEGIN
    #define SY_SUPPRESS_DEPRECATED_END
#endif

namespace Ut
{
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef M_PI2
    #define M_PI2 (2.0 * M_PI)  // 2π
#endif

#ifndef M_PI_2
    #define M_PI_2 (M_PI / 2.0)  // π/2
#endif

#ifndef M_PI_4
    #define M_PI_4 (M_PI / 4.0)  // π/4
#endif

#ifndef M_E
    #define M_E 2.71828182845904523536  // 自然对数底数
#endif

#ifndef DEG_TO_RAD
    #define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0)
#endif

#ifndef RAD_TO_DEG
    #define RAD_TO_DEG(rad) ((rad) * 180.0 / M_PI)
#endif

#ifndef EPSILON
    #define EPSILON 1e-6
#endif

#ifndef FLOAT_EPSILON
    #define FLOAT_EPSILON 1e-5f
#endif

#ifndef DOUBLE_EPSILON
    #define DOUBLE_EPSILON 1e-9
#endif

#ifndef ABS
    #define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

#ifndef FLOAT_EQUAL
    #define FLOAT_EQUAL(a, b) (ABS((a) - (b)) < EPSILON)
#endif

#ifndef FLOAT_ZERO
    #define FLOAT_ZERO(x) (ABS(x) < EPSILON)
#endif

#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef SAFE_DELETE
    #define SAFE_DELETE(p) \
        do                 \
        {                  \
            delete (p);    \
            (p) = nullptr; \
        } while (0)
#endif

#ifndef SAFE_DELETE_ARRAY
    #define SAFE_DELETE_ARRAY(p) \
        do                       \
        {                        \
            delete[] (p);        \
            (p) = nullptr;       \
        } while (0)
#endif

#ifndef ENSURE_NONNULL
    #define ENSURE_NONNULL(ptr, retVal) \
        do                              \
        {                               \
            if (!(ptr))                 \
            {                           \
                return (retVal);        \
            }                           \
        } while (0)
#endif

#ifndef ENSURE_NONNULL_BOOL
    #define ENSURE_NONNULL_BOOL(ptr) ENSURE_NONNULL(ptr, false)
#endif

#ifndef ENSURE_NONNULL_PTR
    #define ENSURE_NONNULL_PTR(ptr) ENSURE_NONNULL(ptr, nullptr)
#endif

#ifndef RETURN_IF_FALSE
    #define RETURN_IF_FALSE(condition, retVal) \
        do                                     \
        {                                      \
            if (!(condition))                  \
            {                                  \
                return (retVal);               \
            }                                  \
        } while (0)
#endif

#ifndef SAFE_CALL
    #define SAFE_CALL(methodCall) \
        do                        \
        {                         \
            if (this)             \
            {                     \
                methodCall;       \
            }                     \
        } while (0)
#endif

#ifndef SAFE_ARRAY_ACCESS
    #define SAFE_ARRAY_ACCESS(arr, index, defaultVal) \
        (((index) >= 0 && (index) < ARRAY_SIZE(arr)) ? (arr)[index] : (defaultVal))
#endif
}  // namespace Ut
