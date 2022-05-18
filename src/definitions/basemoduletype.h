#ifndef BASEMODULETYPE_H
#define BASEMODULETYPE_H
#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include <QDebug>

static const qint32 kInvalid = -1;      //无效
static const qint32 kAllFiles = 0;      // 全部
static const qint32 kUnclassified = 1;  // 未分类
static const qint32 kNoTags = 2;        // 无标签
static const qint32 kTagsMgr = 3;       // 标签管理
static const qint32 kRecycle = 4;       // 回收站
static const qint32 kFolder = 5;        // 普通文件夹
static const qint32 kfileRepeat = 6;    // 文件重复
static const qint32 kIndexFailed = 7;   // 索引失败

class BFProviderSelectedParam {
 public:
  BFProviderSelectedParam() = default;
  BFProviderSelectedParam(const BFProviderSelectedParam& other) {
    type = other.type;
    folder_id = other.folder_id;
  }
  ~BFProviderSelectedParam() = default;
  BFProviderSelectedParam(qint32 t, qint64 id = -1) : type(t), folder_id(id) {}

  bool operator<(const BFProviderSelectedParam& other) const {
    if (type == other.type) {
      return folder_id < other.folder_id;
    }
    return type < other.type;
  }

  bool operator==(const BFProviderSelectedParam& other) const {
    return type == other.type && folder_id == other.folder_id;
  }

 public:
  qint32 type{kInvalid};
  qint64 folder_id{-1};
};

Q_DECLARE_METATYPE(BFProviderSelectedParam);
Q_DECLARE_METATYPE(QVector<BFProviderSelectedParam>);

struct BFUpdateParam {
 public:
  enum class UpdateType {
    kProvider,
    kFolder,
    kFile,
  };

  UpdateType type{
      UpdateType::kProvider};  // 0表示provider 1表示 folder 2表示file
  QVector<qint64> ids;         // 对应的id
};

Q_DECLARE_METATYPE(BFUpdateParam);
Q_DECLARE_METATYPE(QVector<BFUpdateParam>);
#endif
