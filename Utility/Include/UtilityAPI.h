#pragma once

// Windows
#if defined(_WIN32) || defined(_WIN64)
#ifdef UTILITY_EXPORTS
#define UTILITY_API __declspec(dllexport)
#else
#define UTILITY_API __declspec(dllimport)
#endif
// Linux/Unix
#elif defined(__GNUC__) || defined(__clang__)
#ifdef UTILITY_EXPORTS
#define UTILITY_API __attribute__((visibility("default")))
#else
#define UTILITY_API
#endif
#else
#define UTILITY_API
#endif

#ifndef UT_EXTERN_TEMPLATE
#ifdef UTILITY_EXTERN_TEMPLATES
#define UT_EXTERN_TEMPLATE extern
#else
#define UT_EXTERN_TEMPLATE
#endif
#endif