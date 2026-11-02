/**
 * @file AppPathManager.cpp
 * @brief 应用程序路径管理器实现
 *
 * 所有应用数据路径都从 appLocalDataDir() 派生，确保路径统一管理。
 */

#include "AppPathManager.h"

#include <QDir>
#include <QCoreApplication>
#include <QStandardPaths>

/// 应用名称常量（唯一路径控制源）
static const QString kAppName = QStringLiteral("SanYiCAD");

/**
 * @brief 获取应用程序本地数据根目录（唯一路径控制源）
 *
 * 所有应用数据（配置、日志、崩溃dump）都从这个目录派生。
 *
 * Windows: C:/Users/<user>/AppData/Local/SanYiCAD/
 * macOS:   ~/Library/Application Support/SanYiCAD/
 * Linux:   ~/.local/share/SanYiCAD/
 */
QString AppPathManager::appLocalDataDir()
{
#ifdef _WIN32
    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    if (baseDir.isEmpty())
    {
        return QCoreApplication::applicationDirPath() + QStringLiteral("/") + kAppName;
    }
    return baseDir + QStringLiteral("/") + kAppName;
#else
    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    if (baseDir.isEmpty())
    {
        return QCoreApplication::applicationDirPath() + QStringLiteral("/") + kAppName;
    }
    // 移除 Qt 默认添加的组织名/应用名后缀，只保留基础路径
    QString result = baseDir;
    if (result.endsWith(QStringLiteral("/") + kAppName))
    {
        result.chop(kAppName.length() + 1);
    }
    const QString orgName = QCoreApplication::organizationName();
    if (result.endsWith(QStringLiteral("/") + orgName))
    {
        result.chop(orgName.length() + 1);
    }
    return result + QStringLiteral("/") + kAppName;
#endif
}

QString AppPathManager::configDir()
{
    return appLocalDataDir() + QStringLiteral("/config");
}

QString AppPathManager::resourcesDir()
{
    return QCoreApplication::applicationDirPath() + QStringLiteral("/resources");
}

QString AppPathManager::pluginsDir()
{
    return QCoreApplication::applicationDirPath() + QStringLiteral("/plugins");
}

QString AppPathManager::tempDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::TempLocation);
}

QString AppPathManager::appExecutablePath()
{
    return QCoreApplication::applicationFilePath();
}

QString AppPathManager::appRootDir()
{
    return QCoreApplication::applicationDirPath();
}

QString AppPathManager::crashDumpsDir()
{
    return appLocalDataDir() + QStringLiteral("/crashes");
}

QString AppPathManager::logsDir()
{
    return appLocalDataDir() + QStringLiteral("/logs");
}

QString AppPathManager::dataDir()
{
    return appLocalDataDir() + QStringLiteral("/data");
}

// 业务数据（Engine/Persistence）与设置（UI/Common 的 SettingsService）共用同一个库文件，路径只在这里定义一处。
QString AppPathManager::databasePath()
{
    return dataDir() + QStringLiteral("/cad_database.sqlite");
}

QString AppPathManager::safetyConfigPath()
{
    return configDir() + QStringLiteral("/safety_users.conf");
}

QString AppPathManager::materialDatabasePath()
{
    return configDir() + QStringLiteral("/materials.json");
}

QString AppPathManager::cacheDir()
{
    return appLocalDataDir() + QStringLiteral("/cache");
}