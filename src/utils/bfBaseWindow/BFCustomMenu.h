//��Ҫ��װ���ļ��к���Դ�˵�(�м���ͼ����Ҫ)
#pragma once
#include <QObject>
#include<QMenu>
/// <summary>
/// �̳еĴ���
/// </summary>
class BFCustomMenu : public QMenu {
	Q_OBJECT

public:
	BFCustomMenu(QWidget *parent);
	~BFCustomMenu();
};
