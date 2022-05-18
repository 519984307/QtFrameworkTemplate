#include "bfqtutils.h"
#include <QApplication>
#include <QBitmap>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include "bfskinmodule/bfskinsetting.h"
#include <QFontMetrics>
#include <QGuiApplication>
#include <QLocale>
#include <QMimeDatabase>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QProcess>
#include <QPixmap>
#include <QStyle>
#include <QUrl>
#include <QWindow>
#include <QPainter>
#include <QPainterPath>
#include <unordered_set>
#include <string>
#include <QSvgRenderer>
#include "bfcrossplatformutils.h"
#ifdef _WIN32
#include "bfBaseWindow/BFFileAndFolderDialog.h"
#include <shlwapi.h>
#include <shobjidl.h>
#include <stdlib.h>
#include <strsafe.h>
#include <windows.h>

#pragma comment(lib, "shlwapi.lib")
#endif  // _WIN32

#ifdef __APPLE__
//#include "../BFBuryPointsManger/MacOs/EventTrackCInterface.h"
#include "Platform/MacOs/SystemUtilsCInterface.h"
#include "Platform/MacOs/os_define.h"
#endif

#pragma execution_character_set("utf-8")

using namespace std;
QString BfQtUtils::FontAdjustWidth(QFont font, int lab_wid, QString ori_str) {
  if (lab_wid == 0 || ori_str.isEmpty()) {
    //信息不全，不处理
    return ori_str;
  }

  QFontMetrics metrix(font);
  QRect font_rect = metrix.boundingRect(ori_str);

  //当控件宽度小于文字矩形宽度
  while (lab_wid < font_rect.width()) {
    //默认取1/2的字符加上"..."
    if (ori_str.length() < 4) {
      return ori_str;
    }
    ori_str = ori_str.left(ori_str.length() - 4) + QString("..");
    font_rect = metrix.boundingRect(ori_str);
  }
  return ori_str;
}

void BfQtUtils::showInGraphicalShell(const QString& pathIn) {
  //默认传入的参数是：目录+文件路径
  //处理方法：
  //如果是短路径（长度<=256,应该是260，这里用256区分)，使用方法1
  //如果是长路径（长度>256),对路径进行去文件处理，并使用方法2
  QString _pathIn = pathIn;
  QFileInfo fileInfo(_pathIn);
  _pathIn = fileInfo.absoluteFilePath();
  auto _path_length = _pathIn.length();
  int _type = 1;
  if (_path_length > 256) {
    _type = 2;
    _pathIn = _pathIn.mid(0, _pathIn.lastIndexOf("\\"));
  }

#ifdef __APPLE__
  QStringList scriptArgs;
  scriptArgs << QLatin1String("-e")
             << QString::fromLatin1(
                    "tell application \"Finder\" to reveal POSIX file \"%1\"")
                    .arg(fileInfo.canonicalFilePath());
  QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
  scriptArgs.clear();
  scriptArgs << QLatin1String("-e")
             << QLatin1String("tell application \"Finder\" to activate");
  QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
#else
  if (1 == _type) {
    //方法1：打开资源管理器，并找到指定文件。（不支持长路径，路径是目录+文件）
    /*const QString explorer = "explorer";
    QStringList param;
    if (!QFileInfo(_pathIn).isDir()) param << QLatin1String("/select,");
    param << QDir::toNativeSeparators(_pathIn);
    qInfo() << "BfQtUtils::showInGraphicalShell org_path " << pathIn << " type1 cmd " << param;
    QProcess::startDetached(explorer, param);*/
    std::wstring cmd;
    if (!fileInfo.isDir()) {
      cmd += L"/select,";
    }
    cmd += L"\"";
    cmd += QDir::toNativeSeparators(_pathIn).toStdWString();
    cmd += L"\"";
    ShellExecuteW(0, L"open", L"Explorer.exe", cmd.c_str(), 0, SW_NORMAL);
  } else if (2 == _type) {
    //方法2：打开资源管理器，支持长路径（不能找到指定文件。路径是目录）
    QDesktopServices::openUrl(QUrl::fromLocalFile(_pathIn));
    qInfo() << "BfQtUtils::showInGraphicalShell org_path " << pathIn << " type2 cmd " << QUrl::fromLocalFile(_pathIn);
  }
#endif
}

int BfQtUtils::WidthWithFixString(QFont font, QString str) {
  if (str.isEmpty()) {
    return 0;
  }

  QFontMetrics metrix(font);
  QRect font_rect = metrix.boundingRect(str);
  return font_rect.width();
}

int BfQtUtils::HeightWithFixString(QFont font, QString str) {
  if (str.isEmpty()) {
    return 0;
  }

  QFontMetrics metrix(font);
  QRect font_rect = metrix.boundingRect(str);
  return font_rect.height();
}

void BfQtUtils::Crash() {
  char* p = nullptr;
  *p = 0;
}

void BfQtUtils::SetPixmapToRound(QPixmap& src, QSize size, int radius) {
  //方法一:
  // if (src.isNull())
  //{
  //	return;
  //}
  // QBitmap mask(size);
  // QPainter painter(&mask);
  //// 抗锯齿 + 平滑边缘处理
  // painter.setRenderHints(QPainter::Antialiasing, true);
  // painter.setRenderHints(QPainter::SmoothPixmapTransform, true);

  ////遮罩部分用白色区域
  // painter.fillRect(0, 0, size.width(), size.height(), Qt::white);

  ////显示部分用黑色区域
  // painter.setBrush(QColor(0, 0, 0));
  // painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius,
  // Qt::AbsoluteSize);

  // src.setMask(mask);
  //方法二:
  // 无效图片不处理
  if (src.isNull()) {
    return;
  }

  //压缩图片
  QPixmap dest(size.width(), size.height());
  dest.fill(Qt::transparent);
  QPainter painter(&dest);
  // 抗锯齿 + 平滑边缘处理
  painter.setRenderHints(QPainter::Antialiasing, true);
  painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
  // 裁剪为圆角
  QPainterPath path;
  path.addRoundedRect(0, 0, size.width(), size.height(), radius, radius,
                      Qt::AbsoluteSize);
  painter.setClipPath(path);
  painter.drawPixmap(0, 0, size.width(), size.height(), src);
  src = dest;
  return;
}

QString BfQtUtils::formattedDataSize(uint64_t bytes, int precision) {
  QLocale locale("en_us");
  return locale
      .formattedDataSize(bytes, precision,
                         QLocale::DataSizeFormat::DataSizeTraditionalFormat)
      .toUpper();
}

QString BfQtUtils::TimeToQString(int duration) {
  int ss = 1000;
  int mi = ss * 60;
  int hh = mi * 60;
  int dd = hh * 24;

  long day = duration / dd;
  long hour = (duration - day * dd) / hh;
  long minute = (duration - day * dd - hour * hh) / mi;
  long second = (duration - day * dd - hour * hh - minute * mi) / ss;
  long milliSecond =
      duration - day * dd - hour * hh - minute * mi - second * ss;

  /*QString hou = QString::number(hour, 10);
  QString min = QString::number(minute, 10);
  QString sec = QString::number(second, 10);
  QString msec = QString::number(milliSecond, 10);*/

  QString hou = QString("%1").arg(hour, 2, 10, QLatin1Char('0'));
  QString min = QString("%1").arg(minute, 2, 10, QLatin1Char('0'));
  QString sec = QString("%1").arg(second, 2, 10, QLatin1Char('0'));
  QString msec = QString("%1").arg(milliSecond, 2, 10, QLatin1Char('0'));

  QString result;
  if (hou == "00") {
    result = min + ":" + sec;
  } else {
    result = hou + ":" + min + ":" + sec;
  }
  return result;
}

QString BfQtUtils::GetSizeWithUnit(int64_t size) {
  if (size < 0) return QString();

  const char* lpszUnitsName[] = {"Bytes", "KB", "MB", "GB", "TB", "PB"};

  int32_t i, c, iUnitIdx = 0, iMod = 0;
  for (i = 0, c = _countof(lpszUnitsName); i < c; i++) {
    if (size < 1000) {
      break;
    } else {
      iMod = size & 0x3ff;
      size >>= 10;  // /1024
      iUnitIdx++;
    }
  }

  if (iUnitIdx >= _countof(lpszUnitsName)) return QString();

  char szText[128];
  if (iUnitIdx) {
    snprintf(szText, _countof(szText), "%d.%1d %s", (int32_t)size, iMod / 100,
             lpszUnitsName[iUnitIdx]);
  } else {
    snprintf(szText, _countof(szText), "%d %s", (int32_t)size,
             lpszUnitsName[iUnitIdx]);
  }

  return QString(szText);
}

QString BfQtUtils::RemoveStrSepcialChar(QString str) {
  str = RemoveInvalidFileNameChars(str);

  if (str.isEmpty()) {
    str = '_';
  }

  return str;
}

QString BfQtUtils::GetExistingDirectory(QWidget* widget, const QString& title,
                                        const QString& dir) {
  QString ret;
#ifdef _WIN32
  IFileOpenDialog* pFileOpen;
  HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                                IID_IFileOpenDialog,
                                reinterpret_cast<void**>(&pFileOpen));

  if (SUCCEEDED(hr)) {
    DWORD dwOptions;

    pFileOpen->SetTitle(title.toStdWString().c_str());

    if (SUCCEEDED(pFileOpen->GetOptions(&dwOptions))) {
      pFileOpen->SetOptions(dwOptions | FOS_PICKFOLDERS);
    }

    // Show the Open dialog box.
    // hr = pFileOpen->Show((HWND)widget->windowHandle());
    QWindow* wid = widget->windowHandle();
    if (wid) {
    } else {
      wid = QGuiApplication::focusWindow();
    }
    hr = pFileOpen->Show((HWND)(wid->winId()));

    // Get the file name from the dialog box.
    if (SUCCEEDED(hr)) {
      IShellItem* pItem;
      hr = pFileOpen->GetResult(&pItem);
      if (SUCCEEDED(hr)) {
        PWSTR pszFilePath;
        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

        // Display the file name to the user.
        if (SUCCEEDED(hr)) {
          ret = QString::fromWCharArray(pszFilePath);
          CoTaskMemFree(pszFilePath);
        }
        pItem->Release();
      }
    }
    pFileOpen->Release();
  }
#else
  ret = QFileDialog::getExistingDirectory(widget, title, dir);
#endif

  return ret;
}

QStringList BfQtUtils::GetOpenFileNamesAndDirectory(
    QWidget* widget, const QString& title /*= QString()*/,
    const QString& dir /*= QString()*/) {
      QStringList ret;
#ifdef WIN32
  extern QStringList s_result_path_list;
  PickFilesAndFolders(widget, title);
  ret = s_result_path_list;

#else
  Q_UNUSED(widget);
  Q_UNUSED(dir);
  // 特殊需求 mac 最好不要传dir 使用系统自己记录的
  ret = GetOpenOpenFileNameAndDir(title);
#endif
  return ret;
}

QPoint BfQtUtils::MenuBoundController(QRect menu_rect, QPoint pt) {
  // TODO: 这里多显示器有问题
  int desktop_width = QApplication::desktop()->width();
  int desktop_height = QApplication::desktop()->height();

  int need_x = pt.x();
  if (pt.x() + menu_rect.width() > desktop_width) {
    need_x = desktop_width - menu_rect.width();
  } else if (pt.x() < 0) {
    need_x = 0;
  }
  int need_y = pt.y();
  if (pt.y() + menu_rect.height() > desktop_height) {
    need_y = desktop_height - menu_rect.height();
  } else if (need_y < 0) {
    need_y = 0;
  }
  return QPoint(need_x, need_y);
}

QPoint BfQtUtils::SubMenuBoundController(QRect menu_rect, QPoint pt) {
  return QPoint();
}


int BfQtUtils::StringCompare(const QString& str1, const QString& str2) {
#ifdef _WIN32
  return StrCmpLogicalW((const wchar_t*)str1.utf16(),
                        (const wchar_t*)str2.utf16());
#else
  return localizedStandardCompare(str1, str2);
#endif
}

QString BfQtUtils::ColorToHex(QColor color) {
  QString redStr = QString("%1").arg(color.red(), 2, 16, QChar('0'));
  QString greenStr = QString("%1").arg(color.green(), 2, 16, QChar('0'));
  QString blueStr = QString("%1").arg(color.blue(), 2, 16, QChar('0'));
  QString hexStr = "#" + redStr + greenStr + "blueStr";
  return hexStr;
}

QString BfQtUtils::GetAppConfigLocation() {
  return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)
      .at(0);
}

bool BfQtUtils::CreateFileIfNotExists(const QString& dir_path,
                                      const QString& file_name) {
  const QString file_path = dir_path + "/" + file_name;
  QDir dir(dir_path);
  bool ret = false;
  if (!dir.exists()) {
    ret = dir.mkpath(".");
  }
  if (!ret) {
    return ret;
  }

  QFileInfo info(file_path);
  if (!info.exists()) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
      Q_ASSERT(0);
      return false;
    }
    ret = true;
    file.close();
  }

  return ret;
}

void BfQtUtils::openBillfishUrl(const QString& oldurl) {
#ifdef __APPLE__
  QUrl url(oldurl);
  QDesktopServices::openUrl(url);
#else
  QUrl url(oldurl);
  QDesktopServices::openUrl(url);
#endif
}

static QLocale s_formattedQLocale("en_us");
QString BfQtUtils::formattedDataSize(qint64 bytes, int precision) {
  return s_formattedQLocale
      .formattedDataSize(bytes, precision,
                         QLocale::DataSizeFormat::DataSizeTraditionalFormat)
      .toUpper();
}

QString BfQtUtils::removeSdkPathPrefix(QString path) {
  QString _result = QString();
  QString _prefix = "\\\\?\\";
  if (path.startsWith(_prefix)) {
    _result = path.remove(_prefix);
  } else {
    _result = path;
  }
  return _result;
}

int BfQtUtils::ScreenCount() {
  QDesktopWidget* desktopWidget = QApplication::desktop();
  int g_nScreenCount = desktopWidget->screenCount();
  return g_nScreenCount;
}

QRect BfQtUtils::ScreenRect(int i) {
  int n = ScreenCount();
  if (i >= n) {
    //超过最大屏幕数
    return QRect();
  }
  QDesktopWidget* desktopWidget = QApplication::desktop();
  QRect rect = desktopWidget->screenGeometry(i);
  return rect;
}

QRect BfQtUtils::ScreenAvailableRect(int i) {
  int n = ScreenCount();
  if (i >= n) {
    //超过最大屏幕数
    return QRect();
  }
  QDesktopWidget* desktopWidget = QApplication::desktop();
  QRect rect = desktopWidget->availableGeometry(i);
  return rect;
}

int BfQtUtils::PointAtScreenNum(QPoint glo_point) {
  //因为点存在很多种情况，这里只用第一个屏最右侧的位置判断X
  QDesktopWidget* desktopWidget = QApplication::desktop();
  int g_nScreenCount = desktopWidget->screenCount();
  for (int i = 0; i < g_nScreenCount; i++) {
    QRect rect = desktopWidget->screenGeometry(i);

    int point_x = glo_point.x();

    //大于屏幕的x点，小于x点坐标+宽度
    if (point_x > rect.x() && point_x < rect.x() + rect.width()) {
      return i;
    }
  }

  //找不到返回-1；
  return -1;
}

QString BfQtUtils::RemoveInvalidFileNameChars(const QString& filename) {
  /**
          char 0-31
          char 34 60 62 124 58 42 63 92 47
  */

  QString ret = filename;
  for (int32_t i = 0; i <= 31; ++i) {
    ret.remove(QChar(i));
  }
  ret.remove(QChar(34));
  ret.remove(QChar(60));
  ret.remove(QChar(62));
  ret.remove(QChar(124));
  ret.remove(QChar(58));
  ret.remove(QChar(42));
  ret.remove(QChar(63));
  ret.remove(QChar(92));
  ret.remove(QChar(47));

  //第二步  去除 前后空格
  ret = ret.simplified();

  //第三部 去除 尾部的.
  QString tmp = ret;
  do {
    tmp = ret;
    while (ret.endsWith(QChar('.'))) {
      ret = ret.left(ret.size() - 1);
    }
    ret = ret.trimmed();

  } while (tmp != ret);

  return ret;
}

QString BfQtUtils::GetFileExtWithMimetype(const QString& mimetype) {
  static QMimeDatabase mime_db;
  QString ret = "jpg";
  auto type = mime_db.mimeTypeForName(mimetype);
  if (type.isValid()) {
    auto exts = type.suffixes();
    if (exts.size() > 0) {
      ret = exts.at(0);
    }
  }
  return ret;
}

void BfQtUtils::MoveWidgetToVaildPos(QWidget* widget, const QPoint& point) {
  auto available_rect = qApp->desktop()->availableGeometry(widget);
  auto top_left_rect = point;
  auto widget_size = widget->size();
  QRect widget_global_rect(top_left_rect, widget_size);

  if (!available_rect.contains(widget_global_rect)) {
    widget->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                            widget_size, available_rect));
  }
}

quint64 BfQtUtils::CalcDirsSize(QStringList dirPathList) {
  quint64 size = 0;
  foreach (auto dirpath, dirPathList) { size += CalcDirSize(dirpath); }
  return size;
}

quint64 BfQtUtils::CalcDirSize(QString dirPath) {
  quint64 size = 0;
  QDir dir(dirPath);
  // calculate total size of current directories' files
  QDir::Filters fileFilters = QDir::Files | QDir::System | QDir::Hidden;
  for (QString filePath : dir.entryList(fileFilters)) {
    QFileInfo fi(dir, filePath);
    size += fi.size();
  }
  // add size of child directories recursively
  QDir::Filters dirFilters =
      QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden;
  for (QString childDirPath : dir.entryList(dirFilters)) {
    if (childDirPath != ".bf")
      size += CalcDirSize(dirPath + QDir::separator() + childDirPath);
  }
  return size;
}

QStringList BfQtUtils::UrlsToLocalFiles(const QList<QUrl>& url_list) {
  QStringList str_list;
  int count = url_list.size();
  if (count > 1) {
    auto li = url_list.constBegin();
    auto le = url_list.constEnd();
    for (; li != le; li++) {
      str_list.append(li->toLocalFile());
    }
  } else if (1 == count) {
    str_list.append(url_list.at(0).toLocalFile());
  }
  return str_list;
}

bool BfQtUtils::GetDiskSpace(QString strDisk, float& dTotalBytes,
                             float& dFreeBytes) {
#ifdef _WIN32
  LPCWSTR lpcwstrDriver = (LPCWSTR)strDisk.utf16();
  ULARGE_INTEGER lFreeBytesAvailable, lTotalBytesTemp, lTotalFreeBytes;

  if (!GetDiskFreeSpaceEx(lpcwstrDriver, &lFreeBytesAvailable, &lTotalBytesTemp,
                          &lTotalFreeBytes)) {
    return false;
  }

  // unit : GB
  dTotalBytes = lTotalBytesTemp.QuadPart / 1024.0 / 1024 / 1024;
  dFreeBytes = lTotalFreeBytes.QuadPart / 1024.0 / 1024 / 1024;
#endif
  return true;
}

void getNext(const QString& strMode, QByteArray& arrNext) {
  int iModeLen = strMode.length();
  int cn = 0, post = 0;
  arrNext.resize(iModeLen);
  arrNext[0] = -1;
  arrNext[1] = 0;
  post = 2;

  while (post < iModeLen) {
    if (strMode.at(post - 1) == strMode.at(cn)) {
      arrNext[post++] = ++cn;
    } else if (cn > 0) {
      cn = arrNext.at(cn);
    } else {
      arrNext[post++] = 0;
    }
  }
}

int BfQtUtils::FindSubStr(const QString& strSrc, const QString& strMode) {
  int si = 0;
  int mi = 0;
  int iSrcLen = strSrc.length();
  int iModeLen = strMode.length();
  QByteArray arrNext;
  getNext(strMode, arrNext);
  while (si < iSrcLen && mi < iModeLen) {
    if (strSrc.at(si).toUpper() == strMode.at(mi).toUpper()) {
      si++;
      mi++;
    } else if (arrNext.at(mi) == -1) {
      si++;
    } else {
      mi = arrNext.at(mi);
    }
  }
  return (mi == iModeLen) ? si - mi : -1;
}


  QString BfQtUtils::converRGB2HexStr(QColor _rgb) {
  QString redStr = QString("%1").arg(_rgb.red(), 2, 16, QChar('0'));
  QString greenStr = QString("%1").arg(_rgb.green(), 2, 16, QChar('0'));
  QString blueStr = QString("%1").arg(_rgb.blue(), 2, 16, QChar('0'));
  QString hexStr = "#" + redStr + greenStr + blueStr;
  return hexStr;
  }

static std::unordered_set<std::string> s_ExtSet{"jpg", "jpeg", "png", "webp"};

QString BfQtUtils::CreateThumbnailsWithPath(const QString &imagePath, uint32_t &outWidth, uint32_t &outHeight)
{
    const size_t minFileSize = 256 * 1024;
    QFileInfo fileInfo(imagePath);
    if (fileInfo.exists())
    {
        QString suffix = fileInfo.suffix().toLower();
        if (s_ExtSet.find(suffix.toStdString()) == s_ExtSet.end())
        {
            return QString();
        }
        QPixmap pixmap;
        pixmap.load(imagePath);
        int width = pixmap.width();
        int height = pixmap.height();
        outWidth = width;
        outHeight = height;

        if (fileInfo.size() <= minFileSize)
        {
            // 小于256K 直接使用
            QString tmpPath = QDir::tempPath();
            tmpPath.replace("/","\\");
            QString ext = ".webp";
            QString tmpFile = QString::fromStdString(BfCrossPlatformUtils::GetTmpFileName(tmpPath.toStdString().c_str(),ext.toStdString().c_str()));
            if (pixmap.save(tmpFile, "webp"))
            {
                return tmpFile;
            }
            return imagePath;
        }

        if (pixmap.width() <= 900 || pixmap.height() <= 900)
        {
            // 长宽 <= 900 不生成
            QString tmpPath = QDir::tempPath();
            tmpPath.replace("/","\\");
            QString ext = ".webp";
            QString tmpFile = QString::fromStdString(BfCrossPlatformUtils::GetTmpFileName(tmpPath.toStdString().c_str(),ext.toStdString().c_str()));
            if (pixmap.save(tmpFile, "webp"))
            {
                return tmpFile;
            }
            return imagePath;
        }

        if (pixmap.width() <= pixmap.height())
        {
            width = 320;
            double ratio = pixmap.height() / (1.0f * pixmap.width());
            height = width * ratio;
        } else
        {
            height = 320;
            double ratio = pixmap.width() / (1.0f * pixmap.height());
            width = height * ratio;
        }
        outWidth = width;
        outHeight = height;
        QPixmap newPix = pixmap.scaled(width, height, Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation);
        QString tmpPath = QDir::tempPath();
        tmpPath.replace("/","\\");
        QString ext = ".webp";
        QString tmpFile =
            QString::fromStdString(BfCrossPlatformUtils::GetTmpFileName(
                tmpPath.toStdString().c_str(), ext.toStdString().c_str()));
        if (newPix.save(tmpFile, "webp")) {
          return tmpFile;
        }
    }
    return QString();
}

typedef struct SepicalPath {
  SepicalPath(QString path, QString name) {
    sPath = path;
    sName = name;
  }
  QString sPath;  //特殊名称	eg.Pictures
  QString sName;  //特殊库名称	eg.图片
} SEPCIALPATH;

QString BfQtUtils::getLibNameBySpecialPath(const QString& path) {
  QStringList deskTopPath =
      QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
  int lastSlashIndex = deskTopPath.at(0).lastIndexOf("/");
  QString basePath = deskTopPath.at(0).mid(0, lastSlashIndex);

  //构造特殊文件夹及其对应名称
  QList<SEPCIALPATH> sepcialNameList;
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
      QString::fromUtf8("桌面")));
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).at(0),
      QString::fromUtf8("图片")));
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).at(0),
      QString::fromUtf8("视频")));
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0),
      QString::fromUtf8("音乐")));
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0),
      QString::fromUtf8("下载")));
  sepcialNameList.append(SEPCIALPATH(
      QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)
          .at(0),
      QString::fromUtf8("文档")));

  for (int i = 0; i < sepcialNameList.size(); ++i) {
    //拼接特殊路径
    QString sPath = sepcialNameList.at(i).sPath;
    sPath = QDir::toNativeSeparators(sPath);

    //判断当前路径是否是特殊路径
    if (path == sPath) {
      return sepcialNameList.at(i).sName;
    }
  }

  return QString();
}

void BfQtUtils::SetFolderIconFromPath(const QString& imageName,
                                      const QString& folderPath) {
#ifdef _WIN32
  QFileInfo fileInfo(folderPath);
  if (!fileInfo.exists()) return;

  if (!fileInfo.isDir()) return;

  QFile desktopIni(folderPath + "/desktop.ini");
  if (desktopIni.exists()) {
    if (!desktopIni.remove()) {
      return;
    }
  }

  if (!desktopIni.open(QIODevice::Text | QIODevice::WriteOnly)) return;

  QString filePath =
      QDir::toNativeSeparators(QCoreApplication::applicationDirPath() +
                               "/Resources/") +
      imageName;
  QString writefilePath = QString::fromUtf8(".bf/") + imageName;
  QString content = QString(
                        "[.ShellClassInfo]\n"
                        "IconFile=%1\n"
                        "IconIndex=0\n"
                        "[ViewState]\n"
                        "Mode=\n"
                        "Vid=\n"
                        "FolderType=Generic\n")
                        .arg(writefilePath);

  QString newPath = folderPath + QString::fromUtf8("/") + writefilePath;
  QFile::copy(filePath, newPath);

  QTextStream out;
  out.setDevice(&desktopIni);
  out.setCodec("UTF-16");  ///< hould use the utf-16
  out.setGenerateByteOrderMark(true);
  out << content;
  desktopIni.close();

  SetFileAttributes((LPCWSTR)(QDir::toNativeSeparators(desktopIni.fileName())
                                  .toStdWString()
                                  .c_str()),
                    (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM));

  QFile::setPermissions(folderPath, QFile::ReadOwner);
#else
  QString filePath =
      QDir::toNativeSeparators(QCoreApplication::applicationDirPath() +
                               "/../Resources/") +
      imageName;
  setFolderIcon(filePath, folderPath);
#endif
}

void BfQtUtils::UtilsRemoveFolderIcon(const QString &folderPath)
{
#ifdef _WIN32
    QFileInfo fileInfo(folderPath);
    if (!fileInfo.exists()) return;

    if (!fileInfo.isDir()) return;

    QFile desktopIni(folderPath + "/desktop.ini");
    if (desktopIni.exists()) {
      if (desktopIni.remove()) {
        return;
      }
    }


#else
    removeFolderIcon(folderPath);
#endif
}

void BfQtUtils::AddDefaultLibIdentifyFile(const QString& libBfPath) {
  QDir dir(libBfPath);
  if (dir.exists()) {
    QFile file(libBfPath + "/firstRunDefaultLib");
    if (!file.exists()) {
      file.open(QIODevice::ReadWrite | QIODevice::Text);
      file.close();
    }
  }
}

DefaultLibStatus BfQtUtils::CheckIsDefaultLib(const QString& libPath) {
  QString libBfPath = libPath + "/.bf";
  QDir dir(libBfPath);
  if (dir.exists()) {
    QFile file(libBfPath + "/firstRunDefaultLib");
    QFile file2(libBfPath + "/DefaultLib");
    if (file.exists()) {
      file.rename(libBfPath + "/DefaultLib");
      return DefaultLibStatus::E_New;
    }
    if (file2.exists()) {
      return DefaultLibStatus::E_Old;
    }
  }
  return DefaultLibStatus::E_None;
}

bool BfQtUtils::FolderIconExist(const QString& folderPath) {
#ifdef _WIN32
  QFile desktopIni(folderPath + "/.bf/folder.ico");
  if (desktopIni.exists()) {
    return true;
  }
  return false;
#else
  return folderIconExist(folderPath);
#endif
}

void BfQtUtils::CalcDirSubFilesAndSize(QString dirPath, qint64& file_counts,
                                       qint64& total_size) {
  QDir dir(dirPath);
  // calculate total size of current directories' files
  QDir::Filters fileFilters = QDir::Files | QDir::System | QDir::Hidden;
  for (QString filePath : dir.entryList(fileFilters)) {
    QFileInfo fi(dir, filePath);
    total_size += fi.size();
    file_counts++;
  }
  // add size of child directories recursively
  QDir::Filters dirFilters =
      QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden;
  for (QString childDirPath : dir.entryList(dirFilters)) {
    CalcDirSubFilesAndSize(dirPath + QDir::separator() + childDirPath,
                           file_counts, total_size);
  }
}
void BfQtUtils::CalcDirSubFilesAndSizeWithOutSubDir(QString dirPath,
                                                    qint64& file_counts,
                                                    qint64& total_size,
                                                    QString sub_dir) {
  QDir dir(dirPath);
  // calculate total size of current directories' files
  QDir::Filters fileFilters = QDir::Files | QDir::System | QDir::Hidden;
  for (QString filePath : dir.entryList(fileFilters)) {
    QFileInfo fi(dir, filePath);
    total_size += fi.size();
    file_counts++;
  }
  // add size of child directories recursively
  QDir::Filters dirFilters =
      QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden;
  for (QString childDirPath : dir.entryList(dirFilters)) {
    if (childDirPath.compare(sub_dir, Qt::CaseInsensitive) == 0) {
      continue;
    }
    CalcDirSubFilesAndSize(dirPath + QDir::separator() + childDirPath,
                           file_counts, total_size);
  }
}
void BfQtUtils::ShowMenuAtCursorPos(QMenu* menu) {
  QPoint need_pos = BfQtUtils::AdjustMenuPosAtCursorPos(menu);
  menu->popup(QCursor::pos());
  menu->raise();
}
QPoint BfQtUtils::AdjustMenuPosAtCursorPos(QMenu* menu) {
  menu->setAttribute(Qt::WA_DontShowOnScreen);
  menu->show();
  menu->hide();
  menu->setAttribute(Qt::WA_DontShowOnScreen, false);
  QPoint pos = QCursor::pos();
  QRect rect = QRect(menu->pos(), menu->size());

  return BfQtUtils::MenuBoundController(rect, pos);
}

BFBenchmarkTimer::BFBenchmarkTimer(const QString& str) : preStr_(str) {
  timer_.start();
}

BFBenchmarkTimer::~BFBenchmarkTimer() { stop(); }

void BFBenchmarkTimer::stop() {
  auto duration = timer_.elapsed();
  qInfo() << "BFBenchmarkTimer" << preStr_ << "   "
          << QString::fromUtf8(" 耗时:") << duration << "ms\n";
}
