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

    //@brief:����listWidget
    void SetListWidget(QListWidget* list_wid) { m_list_widget = list_wid; };
    //@brief:����������ʾ����
    void SetSearchTipText(QString);
    //@brief:���
    void ClearSearch(bool is_send_sig=true);
    //@brief:������������
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
   
    //@brief:��Ҫ������listWidget
    QListWidget* m_list_widget;

    //@brief:������ʾ�ַ���
    QString m_tips_text;
};
