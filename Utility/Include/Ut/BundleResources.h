#pragma once

#include "Ut/Def.h"

#include <QString>
#include <QCoreApplication>
#include <QDir>

/// App Bundle 内部资源查找工具
/// 用于定位打包进 App 的 pdftocairo、gs 等外部工具及其依赖库
namespace Ut
{
    namespace BundleResources
    {
        /// 查找打包在 App Bundle 内的工具可执行文件
        /// 优先级：Resources/bin/ > 同级目录 > tools/ 子目录 > PATH
        inline QString findBundledTool(const QString& toolName)
        {
            // 1. App Bundle 内 Resources/bin/
            QString bundleBin = QCoreApplication::applicationDirPath() + "/../Resources/bin/" + toolName;
            if (QFile::exists(bundleBin))
            {
                return bundleBin;
            }

            // 2. 同级目录 (Windows 便携部署 / 扁平结构)
            QString flatBin = QCoreApplication::applicationDirPath() + "/" + toolName;
            if (QFile::exists(flatBin))
            {
                return flatBin;
            }

            // 3. tools/ 子目录 (结构化部署)
            QString toolBin = QCoreApplication::applicationDirPath() + "/tools/" + toolName;
            if (QFile::exists(toolBin))
            {
                return toolBin;
            }

            // 4. 结构化部署: tools/<tool>/bin/
            QString structuredBin = QCoreApplication::applicationDirPath() + "/tools/" + toolName + "/bin/" + toolName;
            if (QFile::exists(structuredBin))
            {
                return structuredBin;
            }

            // 4. 回退到系统 PATH (由 QProcess 自动解析)
            return toolName;
        }

        /// 查找打包的库目录
        inline QString findBundledLibDir()
        {
            QString libDir = QCoreApplication::applicationDirPath() + "/../Resources/lib";
            if (QDir(libDir).exists())
            {
                return libDir;
            }
            return QString();
        }

        /// 查找 Ghostscript 资源目录 (字体、初始化文件等)
        inline QString findGhostscriptResourceDir()
        {
            QString gsRes = QCoreApplication::applicationDirPath() + "/../Resources/share/ghostscript";
            if (QDir(gsRes).exists())
            {
                return gsRes;
            }
            return QString();
        }

        /// 设置动态库搜索路径 (必须在 QApplication 构造前调用)
        inline void setupLibraryPath()
        {
            QString libDir = findBundledLibDir();
            if (libDir.isEmpty())
            {
                return;
            }

            QByteArray current = qgetenv("DYLD_LIBRARY_PATH");
            if (!current.contains(libDir.toUtf8()))
            {
                qputenv("DYLD_LIBRARY_PATH", (libDir + ":" + current).toUtf8());
            }
        }

        /// 设置 Ghostscript 资源路径 (必须在 QApplication 构造前调用)
        inline void setupGhostscriptPath()
        {
            QString gsRes = findGhostscriptResourceDir();
            if (gsRes.isEmpty())
            {
                return;
            }

            qputenv("GS_LIB", gsRes.toUtf8());
            qputenv("GS_FONTPATH", (gsRes + "/fonts").toUtf8());
        }

        /// 一次性初始化所有路径 (main() 入口最早调用)
        inline void initialize()
        {
            setupLibraryPath();
            setupGhostscriptPath();
        }
    }
}