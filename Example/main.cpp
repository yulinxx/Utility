#include "AppPathManager.h"
#include "Ut/FileUtils.h"

#include <filesystem>
#include <iostream>

// ============================================================
//  Utility 使用示例
//  编译后执行 SyUtilityExample.exe
//
//  演示：
//    1. Ut::FileUtils —— UTF-8 与 filesystem::path 的跨平台转换
//    2. AppPathManager —— 应用路径唯一控制源（配置/资源/插件/临时目录）
// ============================================================

int main()
{
    std::cout << "=== SyUtilityExample ===" << std::endl;

    // ---- 1. FileUtils：UTF-8 <-> path 往返 --------------------------------
    const std::filesystem::path original = Ut::FileUtils::utf8ToPath(u8"图纸/示例.dxf");
    const std::string roundTrip = Ut::FileUtils::pathToUtf8(original);
    std::cout << "utf8 -> path -> utf8 : " << roundTrip << std::endl;

    const std::filesystem::path fromAscii = Ut::FileUtils::utf8ToPath("C:/Temp/data.bin");
    std::cout << "ascii round trip     : " << Ut::FileUtils::pathToUtf8(fromAscii) << std::endl;

    // ---- 2. AppPathManager：应用路径 -------------------------------------
    std::cout << "appLocalDataDir : "
              << AppPathManager::appLocalDataDir().toStdString() << std::endl;
    std::cout << "configDir       : "
              << AppPathManager::configDir().toStdString() << std::endl;
    std::cout << "tempDir         : "
              << AppPathManager::tempDir().toStdString() << std::endl;
    std::cout << "appRootDir      : "
              << AppPathManager::appRootDir().toStdString() << std::endl;

    return 0;
}
