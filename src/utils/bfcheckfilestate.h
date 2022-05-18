#ifndef BILLFISH_CHECK_FILE_STATE_H__
#define BILLFISH_CHECK_FILE_STATE_H__

#include <QSharedPointer>
#include "interfaces/datacenter/data/ifileinfo.h"
#include <QFileInfo>

namespace Billfish {

// 检测是否是无效的索引文件
// 返回true表示是索引文件且索引文件已经失效
static inline bool isInvalidIndexFile(
    const QSharedPointer<const IFileInfo>& file_info) {
  if (file_info->isLink()) {
    return !QFileInfo::exists(file_info->getSourcePath());
    ;
  }

  return false;
}

// 文件预览类型
enum class FilePreviewType {
  kFPTNormal = 0, // 正常预览
  kFPTInvalidIndex, // 索引失效
  kFPTNotSupport, // 不支持分析
  kFPTNoAnalyze, // 未分析
  kFPTAnalyzeFailed, // 分析失败
};

// 检测文件预览类型 checkFilePreviewType 这个接口不能判断索引失效
static inline FilePreviewType checkFilePreviewType(
    const QSharedPointer<const IFileInfo>& file_info) {
    if (file_info->canAnalyze()) {
      switch (file_info->getAnalyzeStatus()) {
        case FILE_ANALYZE_STATUS_SUCCESS:
          return FilePreviewType::kFPTNormal;
        case FILE_ANALYZE_STATUS_NONE:
          return FilePreviewType::kFPTNoAnalyze;
        case FILE_ANALYZE_STATUS_FAILED:
          return FilePreviewType::kFPTAnalyzeFailed;
        default:
          Q_ASSERT(0);
          return FilePreviewType::kFPTAnalyzeFailed;
      }
    } else {
      if (file_info->getCoverTid() > 0) {
        return FilePreviewType::kFPTNormal;
      } else {
        return FilePreviewType::kFPTNotSupport;
      }
    }
}


// 是否能够正常预览
static inline bool isValidPreviewFile(
    const QSharedPointer<const IFileInfo>& file_info) {
  if (file_info->canAnalyze()) {
    // 支持分析
    if (FILE_ANALYZE_STATUS_SUCCESS == file_info->getAnalyzeStatus()) {
      // 分析成功
      return true;
    }
  } else {
    // 不支持分析
    if (file_info->getCoverTid() > 0) {
      // 用户设置了封面
      return true;
    }
  }
  return false;
}

}

#endif
