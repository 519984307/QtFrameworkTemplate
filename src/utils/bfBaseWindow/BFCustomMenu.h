//主要封装下文件夹和资源菜单(中间视图所需要)
#pragma once
#include <QObject>
#include<QMenu>
/// <summary>
/// 继承的窗体
/// </summary>
class BFCustomMenu : public QMenu {
	Q_OBJECT

public:
	BFCustomMenu(QWidget *parent);
	~BFCustomMenu();
};
