#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include <QList>
#include <QString>
#include <QFont>
#include <QStringList>

#include "utilsexport.h"

class QSslCertificate;
class QFontMetrics;
class QPixmap;
class QIcon;
class QWidget;
class QUrl;
class QString;

namespace Utils
{

struct Signatures
{
    qint64 timestamp;
    int nonce;
    QString signature;
};

Signatures UTILS_EXPORT genarateSignatures(const QString &token, const QStringList &customerParams = QStringList());

quint16 UTILS_EXPORT byteArrayToQuint16(QByteArray array);
QByteArray UTILS_EXPORT quint16ToByteArrary(const quint16 var);
quint32 UTILS_EXPORT byteArrayToQuint32(QByteArray array);
QByteArray UTILS_EXPORT quint32ToByteArrary(const quint32 var);
quint64 UTILS_EXPORT byteArrayToQuint64(QByteArray array);
QByteArray UTILS_EXPORT quint64ToByteArrary(const quint64 var);

QString UTILS_EXPORT dataDir();
QString UTILS_EXPORT profileDir();
QString UTILS_EXPORT translationDir();
QString UTILS_EXPORT themesDir();
QString UTILS_EXPORT tempPath();
void UTILS_EXPORT clearTempPath();

QByteArray UTILS_EXPORT pixmapToByteArray(const QPixmap &pix, const QString &type ="jpeg");
QPixmap UTILS_EXPORT pixmapFromByteArray(const QByteArray &data);
QByteArray UTILS_EXPORT getFileMd5(const QString &filePath);
QByteArray UTILS_EXPORT getFileHash(const QString &filePath);

QString UTILS_EXPORT readAllFileContents(const QString &filename);

void UTILS_EXPORT centerWidgetOnScreen(QWidget* w);
void UTILS_EXPORT centerWidgetToParent(QWidget* w, QWidget* parent);

bool UTILS_EXPORT removeFile(const QString &fullFileName);
void UTILS_EXPORT removeDir(const QString &d);

QString UTILS_EXPORT samePartOfStrings(const QString &one, const QString &other);
QString UTILS_EXPORT urlEncodeQueryString(const QUrl &url);

QString UTILS_EXPORT ensureUniqueFilename(const QString &name, const QString &appendFormat = QString("(%1)"));
QString UTILS_EXPORT getFileNameFromUrl(const QUrl &url);
QString UTILS_EXPORT filterCharsFromFilename(const QString &name);

QString UTILS_EXPORT alignTextToWidth(const QString &string, const QString &text, const QFontMetrics &metrics, int width);
QString UTILS_EXPORT fileSizeToString(qint64 size);

QPixmap UTILS_EXPORT createPixmapForSite(const QIcon &icon, const QString &title, const QString &url);
QString UTILS_EXPORT applyDirectionToPage(QString &pageContents);

QString UTILS_EXPORT resolveFromPath(const QString &name);
QStringList UTILS_EXPORT splitCommandArguments(const QString &command);
bool UTILS_EXPORT startExternalProcess(const QString &executable, const QString &args);

QString UTILS_EXPORT loadFileData(const QString &AFileName, const QString &DefValue);

QIcon UTILS_EXPORT iconFromFileName(const QString &fileName);
bool UTILS_EXPORT isUtf8(const char* string);

bool UTILS_EXPORT matchDomain(const QString &pattern, const QString &domain);

QString UTILS_EXPORT operatingSystem();

QString UTILS_EXPORT wrapText(const QFont &font, const QString &text, int maxWidth);

// Qt5 migration help functions
bool UTILS_EXPORT isCertificateValid(const QSslCertificate &cert);
QString UTILS_EXPORT escape(const QString &string);

#if defined(QZ_WS_X11) && !defined(NO_X11)
void UTILS_EXPORT* X11Display(const QWidget* widget);
#endif

template <typename T>
bool listContainsIndex(const QList<T> &list, int index)
{
    return (index >= 0 && list.count() > index);
}

template <typename T>
bool vectorContainsIndex(const QVector<T> &list, int index)
{
    return (index >= 0 && list.count() > index);
}

} // namespace

#endif // GLOBALFUNCTIONS_H
