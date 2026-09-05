#pragma once

#include "UtilityAPI.h"
#include <string>
#include <filesystem>

namespace Ut
{
    /**
     * @brief 文件路径工具函数
     *
     * 提供跨平台的路径与 UTF-8 字符串转换功能。
     */
    namespace FileUtils
    {
        /**
         * @brief 路径转 UTF-8 字符串
         *
         * 跨平台实现：
         * - Windows: 使用 WideCharToMultiByte(CP_UTF8)
         * - macOS/Linux: 使用 path::u8string()
         *
         * @param path 文件系统路径
         * @return UTF-8 编码的字符串
         */
        UTILITY_API std::string pathToUtf8(const std::filesystem::path& path);

        /**
         * @brief UTF-8 字符串转路径
         *
         * 跨平台实现：
         * - Windows: 使用 MultiByteToWideChar(CP_UTF8)
         * - macOS/Linux: 使用 std::filesystem::u8path()
         *
         * @param utf8 UTF-8 编码的字符串
         * @return 文件系统路径
         */
        UTILITY_API std::filesystem::path utf8ToPath(const std::string& utf8);
    }
}
