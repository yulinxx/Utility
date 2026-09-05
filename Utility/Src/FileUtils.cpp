#include "Ut/FileUtils.h"

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif

namespace Ut::FileUtils
{
    std::string pathToUtf8(const std::filesystem::path& path)
    {
#ifdef _WIN32
        auto wstr = path.wstring();
        if (wstr.empty())
        {
            return {};
        }

        int size = WideCharToMultiByte(
            CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()),
            nullptr, 0, nullptr, nullptr);

        if (size <= 0)
        {
            return {};
        }

        std::string result(size, 0);
        WideCharToMultiByte(
            CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()),
            &result[0], size, nullptr, nullptr);

        return result;
#else
        return path.u8string();
#endif
    }

    std::filesystem::path utf8ToPath(const std::string& utf8)
    {
#ifdef _WIN32
        if (utf8.empty())
        {
            return {};
        }

        int wsize = MultiByteToWideChar(
            CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()),
            nullptr, 0);

        if (wsize <= 0)
        {
            return {};
        }

        std::wstring wstr(wsize, 0);
        MultiByteToWideChar(
            CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()),
            &wstr[0], wsize);

        return std::filesystem::path(wstr);
#else
        return std::filesystem::u8path(utf8);
#endif
    }
}
