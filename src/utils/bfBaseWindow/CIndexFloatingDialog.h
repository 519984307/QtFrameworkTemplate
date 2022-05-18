#pragma once
#include "CPopupDialog.h"
#include <QLabel>
#include <QTextEdit>

#pragma execution_character_set("utf-8")

#define TEXT_WHAT_INDEX                                                     \
  QString::fromUtf8("<font style='color:") +                                \
      BFSkinSetting::GetInstance()->GetRightFont1().name(QColor::HexArgb) + \
      QString::fromUtf8(";'>该素材为索引素材</font>")
#define TEXT_WHAT_INDEX_SECOND                                                \
  QString::fromUtf8(                                                          \
      "<style> a {text-decoration: none} </style><a style='color: #4F84FA;' " \
      "href = 什么是索引素材 > 什么是索引素材?</a>")
#define TEXT_LOST_INDEX                 \
  QString::fromUtf8(                    \
      "该素材为索引模式素材," \
      "当前检测到该素材原始路径丢失，您可以尝试右键素材对路径重新进行加载")
#define TEXT_SUPPORT_IMPORT                                                                  \
  QString::fromUtf8(                                                                         \
      "<p "                                                                                  \
      "style='line-height:20px'>"                                                            \
      "该格式\n素材暂时仅支持导入不支持生成缩略图，您可以自定义 " \
      "设置素材封面，还可以在偏好设置中设置更多您希望导入的格式</p>")
#define TEXT_DIFFERENT_ANY_IMP QString::fromUtf8("支持导入和支持解析的区别")

#define TEXT_CLEAR_FILTER_CONDITION QString::fromUtf8(\
 "<style> a {text-decoration: none} </style><a style='color: rgba(162,171,195,255);'"\
    "href = 右键清空条件 > 右键清空条件</a>")


class CIndexFloatingDialog : public CPopupDialog {
  Q_OBJECT
 public:
  static CIndexFloatingDialog* getInstance(QWidget* parent);
  ~CIndexFloatingDialog();
  //设置文本，显示悬浮窗口
  void showFloatingDialog(const QString& text);
  //显示色值块悬浮窗
  void showColorFloating(const QString& colorText, const QString& percentText);
  //显示色值块悬浮窗
  void showColorFloating(const QString& tip);
  //显示网址修改悬浮窗
  void showUrlFloating(const QString& text);
  //显示备注修改悬浮窗
  void showNoteFloating(const QString& text);
  //显示文件夹描述修改悬浮窗
  void showFolderDesFloating(const QString& text);
  //显示文件夹标签提示悬浮窗
  void showFolderTagFloatingDialog(const QString& text1, const QString& text2, const QString& text3);
  //显示白色皮肤悬浮窗
  void showWhiteFloatDialog(const QString&);
  //显示导入时提示悬浮窗
  void showImportTipsFloatDialog(const QString&);
  //显示格式设置悬浮窗
  void showFormatFloating(const QRect& iconRect);
  //设置网址控件是否可用
  void setUrlEnable(bool enable);
  //设置备注控件是否可用
  void setNoteEnable(bool enable);
  //设置文件夹描述是否可用
  void setFolderDesEnable(bool enable);
  //显示素材库操作按钮不可用时的悬浮窗
  void showLibBtnFloatDialog(const QString& text);
  //获得悬浮窗所属file_id
  qint64 GetFileId() { return m_file_id; }
  //设置悬浮窗所属file_id
  void SetFileId(qint64 id) { m_file_id = id; }
  //获得悬浮窗模式（根据内容判断）
  QString getDialogMode();
  //样式切换
  void SwitchStyleSheet();
  //获得url控件中的url信息
  QString getUrl();
  //判断网址内容是否改变
  bool getUrlChanged() { return m_urlChanged; }
  //获得note控件中的note信息
  QString getNote() { return m_noteEdit->toPlainText(); }
  //判断备注内容是否改变
  bool getNoteChanged() { return m_noteChanged; }
  //获得文件夹描述信息
  QString getFolderDes();
  //判断备注内容是否改变
  bool getDesChanged() { return m_desChanged; }
  //
  void setUrlMode(bool value) { m_bUrl = value; }
  bool getUrlMode() { return m_bUrl; }
  //
  void setNoteMode(bool value) { m_bNote = value; }
  bool getNoteMode() { return m_bNote; }
  //
  void setFolderDesMode(bool value) { m_bFolderDes = value; }
  bool getFolderDesMode() { return m_bFolderDes; }
  //
  void setRightIndexMode(bool value) { m_bRightIndex = value; }
  bool getRightIndexMode() { return m_bRightIndex; }
  //
  void setFolderTagMode(bool value) { m_bFolderTag = value; }
  bool getFolderTagMode() { return m_bFolderTag; }
  //
  void setLibBtnMode(bool value) { m_bLibBtn = value; }
  bool getLibBtnMode() { return m_bLibBtn; }

 signals:
  void signSetSourceCoverByFloat();  //通知视图,设置素材封面
  void SigOpenSettingWin();          //通知视图,打开偏好设置页面

 protected:
  bool eventFilter(QObject* obj, QEvent* event);
  void hideEvent(QHideEvent* event);
  virtual void closeEvent(QCloseEvent* event);
  virtual void leaveEvent(QEvent* event);

 public:
  void move(int x, int y);
  void move(const QPoint& p);
  void show();

 private:
  CIndexFloatingDialog(QString text, QWidget* parent = 0, bool bClose = false,
                       bool bTitle = false, bool bRepaint = false /*,
                                             bool bDelete = true,
                                             bool bIcon = true*/
  );
  //隐藏所有子控件
  void hideAllWidget();

 private:
  static CIndexFloatingDialog* m_instance;

  //文字文案
  QLabel* m_textLabel;        //文字文案
  QLabel* m_secondTextLabel;  //第二行文字文案
  QLabel* m_thirdTextLabel;   //第三行文字文案
  QLabel* m_fourthTextLabel;  //第四行文字文案

  //网址控件
  QTextEdit* m_urlEdit;           //网址输入框
  QPushButton* m_browserLookBtn;  //浏览器查看按钮
  bool m_urlChanged;              //标志位：网址改变

  //备注控件
  QTextEdit* m_noteEdit;  //备注输入查看框
  bool m_noteChanged;     //标志位：备注改变

  //文件夹描述控件
  QTextEdit* m_folderDesEdit;  //文件夹描述输入查看框
  bool m_desChanged;           //标志位：描述改变

  //显示方式标志位
  bool m_bUrl;         //修改网址模式
  bool m_bNote;        //修改备注模式
  bool m_bRightIndex;  //右侧栏索引模式
  bool m_bFolderDes;   //文件夹描述模式
  bool m_bFolderTag;   //文件夹标签模式
  bool m_bLibBtn;      //素材库管理按钮模式

  //需要用到的字体
  QFont font_10;
  QFont font_11;
  QFont font_12;
  QFont font_13;


  qint64  m_file_id=0;  //支持导入的格式悬浮窗 所属 file_id

  QTimer* m_format_check_timer;  //格式设置提示窗口检查定时器

 private slots:
  //各个label超链接槽
  void SlotFirstLabLinkActivated(QString);
  void SlotSecondLabLinkActivated(QString);
  void SlotThirdLabLinkActivated(QString);
  void SlotFourthLabLinkActivated(QString);
};
