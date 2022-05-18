#ifndef DEF_VERSION_H
#define DEF_VERSION_H
#include <QtGlobal>
#include <QStringList>

#define ORGANIZATION_NAME           "Billfish"
#define APPLICATION_NAME            "Billfish"
#define MANAGER_APPLICATION_NAME    "BillfishManager"

#define CLIENT_NAME             "Billfish"
#define CLIENT_VERSION          "1.0.0"
#define CLIENT_VERSION_SUFIX    ""
#define CLIENT_HOME_PAGE        "https://www.billfish.cn"

#define IS_PACKAGE_BUILD    0

namespace BasicDef {

typedef struct _UpdateInfo
{
    QString os;
    QString buildVersion;
    QString releaseVersion;
    QString releaseDateTime;
    QStringList releaseDescription;
    QString packageDownloadUrl;
    QString packageFileSize;
    QString systemRequirements;
}UpdateInfo;

const static QString UpdateInfoPacket_Os = "OS";
const static QString UpdateInfoPacket_BuildVersion = "BuildVersion";
const static QString UpdateInfoPacket_ReleaseVersion = "ReleaseVersion";
const static QString UpdateInfoPacket_ReleaseDateTime = "ReleaseDateTime";
const static QString UpdateInfoPacket_ReleaseDescription = "ReleaseDescription";
const static QString UpdateInfoPacket_PackageDownloadUrl = "PackageDownloadUrl";
const static QString UpdateInfoPacket_PackageFileSize = "PackageFileSize";
const static QString UpdateInfoPacket_SystemRequirements = "SystemRequirements";

}

#endif
