#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
namespace Ui { class CListSearchLineEdit; };

class CListSearchLineEdit : public QWidget
{
	Q_OBJECT

public:
	CListSearchLineEdit(QWidget *parent = Q_NULLPTR);
	~CListSearchLineEdit();

    //@brief:设置listWidget
    void SetListWidget(QListWidget* list_wid) { m_list_widget = list_wid; };
    //@brief:设置搜搜提示文字
    void SetSearchTipText(QString);
    //@brief:清空
    void ClearSearch(bool is_send_sig=true);
    //@brief:搜索现有文字
    void ReSearchCurText();

private:
    void InitUi();
    void SwitchStyleSheet();

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private slots:
    void SlotSearchTextChanged(QString);



private:
	Ui::CListSearchLineEdit *ui;
   
    //@brief:需要搜索的listWidget
    QListWidget* m_list_widget;

    //@brief:搜索提示字符串
    QString m_tips_text;
};
