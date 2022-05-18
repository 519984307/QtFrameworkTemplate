#pragma once
#include"CPopupDialog.h"
#include<QCheckBox>
#include<QLabel>
#include<QPushButton>


#define NO_DEL_FILE 0       //不删除索引丢失文件
#define DEL_FILE 1          //删除索引丢失文件
#define RE_LOACATION 2      //重新加载路径
#define CheckFailedFile 3   //查看转换失败的文件


//@brief:索引丢失和索引转备份结果共用该窗口
class CIndexToCopyResultDialog :public CPopupDialog
{
	Q_OBJECT
public:
	CIndexToCopyResultDialog(QWidget* parent = 0);
	~CIndexToCopyResultDialog();
  //样式表切换
  void SwitchStyleSheet();
	//【路径失效窗口】
	int showIndexLostDialog();
	//【索引转备份结果窗口】
	int showIndexToCopyResultDialog();
	//设置失败素材,用于查看转换失败的素材
        void setSucAndFailedCount(QVector<qint64> fail_pho_vec, int failedCount,
                                  int sucCount);
  //初始化Ui
  void InitUi();

signals:
  void SigIntoIndexToCopyFailedPage(QVector<qint64>);


public slots:
	//slot:确定按钮
	void slotOkClicked();
	//slot:点击【失败素材】按钮
	void slotFailedClicked();
	//slot:点击取消按钮
	void slotCancelClicked();
	//slot:点击重选路径按钮
	void slotRelocationPaht();
	//slot:点击删除素材按钮
	void slotDelSouce();

protected:
	bool eventFilter(QObject* target, QEvent* event) override;

private:
  //索引转备份转换结果弹窗
  QLabel*              m_lab_title;
  QLabel*              m_lab_success_title;
  QLabel*              m_lab_failed_title;
  QLabel*              m_lab_success;
  QLabel*              m_lab_failed;
  QLabel*              m_linkLabel;
  QPushButton*         m_okBtn;                        //好的按钮
  QPushButton*         m_failedResBtn;                 //失败素材按钮
  QLabel*              m_failed_why_lab;               //转换失败lab

  //索引素材路径丢失弹窗
  QLabel*           m_lose_lab_title;               //标题
  QLabel*           m_lab_context;                  //内容
  QLabel*           m_why_lost_icon;                //为什么丢失图标 
  QLabel*           m_why_lose_text;                //为什么丢失文字
  QPushButton* m_load_path;                         //加载路径按钮
  QPushButton* m_delete_source;                     //删除资源按钮
  QPushButton* m_not_handle;                        //不处理按钮
  QVector<qint64> m_failed_pho_vec;                 //失败素材Iphoto
  int             m_failedCount;                    //失败素材个数
  int			  m_sucCount = 0;				    //成功素材个数
};

//class CIndexToCopyDelSourceDialog :public CPopupDialog
//{
//	Q_OBJECT
//public:
//	CIndexToCopyDelSourceDialog(QWidget* parent = 0);
//	~CIndexToCopyDelSourceDialog();
//
//
//  void SwitchStyleSheet();
//
//
//public:
//
//public slots:
//	void slotNoDel();  //不删除
//	void slotDel();       //删除
//    void SlotNoCation(bool);
//
//private:
//  void InitUi();
//
//private:
//  QLabel*            m_lab_title;
//  QLabel*            m_lab_context;
//  QCheckBox*     m_is_no_caution_box;
//  QPushButton * m_noDelBtn;
//  QPushButton * m_delBtn;
//};
//
