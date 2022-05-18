#ifndef BFQTUTILS_H
#define BFQTUTILS_H
#include "utilsexport.h"
#include <QElapsedTimer>
#include <QFont>
#include <QMenu>
#include <QPixmap>

enum class DefaultLibStatus { E_None = 0, E_New, E_Old };

class UTILS_EXPORT BfQtUtils
{
public:
    /// @brief 创建文件如果不存在
    /// @param dir_path 文件路径  例如c:\\ddddd
    /// @param file_name 文件名字 例如 lib_info.ini 最终会创建
    /// c:\\ddddd\\lib_info.ini
    /// @return
    static bool CreateFileIfNotExists(const QString& dir_path,
                                      const QString& file_name);
    static int WidthWithFixString(QFont font, QString str);

    static void SetPixmapToRound(QPixmap& src, QSize size, int radius = 25);
    static QString CreateThumbnailsWithPath(
        const QString& imagePath, uint32_t& outWidth,
        uint32_t& outHeight);  //传入图片必须是内置类型 当字符串为空时 失败

    static QString FontAdjustWidth(QFont font, int lab_wid, QString ori_str);
    
     public:
  // showInGraphicalShell windows 在explore 显示 mac 就是showinfinder
  static void showInGraphicalShell(const QString& pathIn);
  static int HeightWithFixString(QFont font, QString str);
  static void Crash();  //崩溃测试
  static QString formattedDataSize(uint64_t bytes, int precision = 2);
  //时长int转字符串
  static QString TimeToQString(int duration);
  //获得转换单位之后的大小。参数size为字节大小。
  static QString GetSizeWithUnit(int64_t size);
  static QString RemoveStrSepcialChar(QString str);
  static QString GetExistingDirectory(QWidget* widget, const QString& title,
                                      const QString& dir);


    // 支持复选 同时选择 文件 和文件夹
  static QStringList GetOpenFileNamesAndDirectory(
      QWidget* widget, const QString& title = QString(),
      const QString& dir = QString());

  //菜单边界控制项，传入菜单移动的点和大小，当超出右边界或者下边界的时候移动上去
  static QPoint MenuBoundController(QRect menu_rect, QPoint pt);

  //子菜单边界控制项，传入触发那一项父菜单的item_rect，子菜单的rect以及
  static QPoint SubMenuBoundController(QRect menu_rect, QPoint pt);
  /*
  和windows资源管理器一致
  字符串比较函数
  str1>str2       1
  str1==str2    0
  str1<str2     -1
  */
  static int StringCompare(const QString& str1, const QString& str2);

  //给定颜色转换成：#XXXXXX的形式
  static QString ColorToHex(QColor color);

  static QString GetAppConfigLocation();

  static void openBillfishUrl(const QString& strUrl);

  static QString formattedDataSize(qint64 bytes, int precision = 2);

  //去除sdk路径前缀
  static QString removeSdkPathPrefix(QString path);

  //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓多屏相关↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
  static int ScreenCount();        //获取屏幕数量
  static QRect ScreenRect(int i);  //获取第i个屏幕的总体区域
  static QRect ScreenAvailableRect(
      int i);  //获取第i个屏幕的可用区域(不带任务栏)

  /*!
  @brief  判断点在第几个屏幕
                  如果说软件适用的右屏的属性，但是点在左屏，认为该点非法，返回-1
  */
  static int PointAtScreenNum(QPoint glo_point);  //判断点在第几个屏幕区域

  /// @brief 这里会去掉文件名不符合的字符
  /// 这里可能返回 空字符串 需要注意处理

  static QString RemoveInvalidFileNameChars(const QString& filename);

  static QString GetFileExtWithMimetype(const QString& mimetype);

  /// @brief 移动widget到合适位置
  /// @param widget
  /// @param point 将要移动的点 这个点必须是全局点
  /// 注意 widget 必须是一个 窗体
  static void MoveWidgetToVaildPos(QWidget* widget, const QPoint& global_pos);

  static quint64 CalcDirsSize(QStringList dirPathList);
  static quint64 CalcDirSize(QString dirPath);

  // QList<Qurl> toLoacalFile -> QStringList
  static QStringList UrlsToLocalFiles(const QList<QUrl>& url_list);

  //@brief 获取磁盘空间strDisk传入 C:,D:....即可
  static bool GetDiskSpace(QString strDisk, float& dTotalBytes,
                           float& dFreeBytes);

  //查找strSrc是否含有子串strMode
  //@param >=0 含有 <0不含有
  static int FindSubStr(const QString& strSrc, const QString& strMode);

  // QColor转#000000
  static QString converRGB2HexStr(QColor _rgb);

  static QString getLibNameBySpecialPath(const QString& path);
  static void SetFolderIconFromPath(const QString& imageName,
                                    const QString& folderPath);

  static void UtilsRemoveFolderIcon(const QString& folderPath);

  //向默认库中添加标识文件
  static void AddDefaultLibIdentifyFile(const QString& libBfPath);

  //检测素材库是不是默认库
  static DefaultLibStatus CheckIsDefaultLib(const QString& libPath);

  static bool FolderIconExist(const QString& folderPath);

  static void CalcDirSubFilesAndSize(QString dirPath, qint64& file_counts,
                                     qint64& total_size);

  static void CalcDirSubFilesAndSizeWithOutSubDir(QString dirPath,
                                                  qint64& file_counts,
                                                  qint64& total_size,
                                                  QString sub_dir);

  static void ShowMenuAtCursorPos(QMenu* menu);

  static QPoint AdjustMenuPosAtCursorPos(QMenu* menu);
};

class UTILS_EXPORT BFBenchmarkTimer {
 public:
  explicit BFBenchmarkTimer(const QString& str);
  ~BFBenchmarkTimer();
  void stop();

 private:
  QElapsedTimer timer_;
  QString preStr_;
};

#if defined(NDEBUG)
#define BFBenchmark(variblename, str)
#else
#define BFBenchmark(variblename, str) BFBenchmarkTimer variblename(str)
#endif

#endif  // BFQTUTILS_H
