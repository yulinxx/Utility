#pragma once

#include <QString>
#include "UtilityAPI.h"

/**
 * @file AppPathManager.h
 * @brief 应用程序路径管理器定义
 *
 * 定义了应用程序路径管理类，负责管理配置文件、资源文件、插件等路径。
 */

class UTILITY_API AppPathManager
{
public:
    /// 获取应用程序本地数据根目录（唯一路径控制源）
    /// Windows: C:/Users/<user>/AppData/Local/SanYiCAD/
    /// macOS:   ~/Library/Application Support/SanYiCAD/
    /// Linux:   ~/.local/share/SanYiCAD/
    static QString appLocalDataDir();

    static QString configDir();

    static QString resourcesDir();

    static QString pluginsDir();

    static QString tempDir();

    static QString appExecutablePath();

    static QString appRootDir();

    static QString crashDumpsDir();

    static QString logsDir();

    static QString dataDir();

    /// 主数据库文件路径。唯一来源：AppInitializer（业务库）与 SettingsService（设置库）都从这里取路径。
    static QString databasePath();

    static QString safetyConfigPath();

    static QString materialDatabasePath();

    static QString cacheDir();
};
