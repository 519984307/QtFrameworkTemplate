//
// Created by luqi on 2021/12/12.
//

#ifndef BILLFISH_BFTYPEUTILS_H
#define BILLFISH_BFTYPEUTILS_H
#include "utilsexport.h"
#include <QObject>
#include <QString>

class UTILS_EXPORT BFTypeUtils {
 public:
  static bool isVideo(qint64 tid) noexcept;
  static bool isAudio(qint64 tid) noexcept;
  static bool isSvg(qint64 tid) noexcept;
  static bool isGif(qint64 tid) noexcept;
  static bool isPsd(qint64 tid) noexcept;
  static bool isPpt(qint64 tid) noexcept;
  static bool isBuiltInImageType(qint64) noexcept;
  static bool isShowBigPrivewBtn(qint64 tid) noexcept;
};

#endif  // BILLFISH_BFTYPEUTILS_H
