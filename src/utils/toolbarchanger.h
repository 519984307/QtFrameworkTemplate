#ifndef TOOLBARCHANGER_H
#define TOOLBARCHANGER_H

#include <QEvent>
#if QT_VERSION < 0x050000
#include <QToolBar>
#include <QToolButton>
#else
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#endif
#include <QMultiMap>
#include "utilsexport.h"
#include "action.h"
#include "toolbutton.h"

#define TBG_NULL            -1
#define TBG_DEFAULT         500
#define TBG_ALLIGN_CHANGE   10000

class UTILS_EXPORT ToolBarChanger :
			public QObject
{
    Q_OBJECT
public:
	ToolBarChanger(QToolBar *AToolBar);
	~ToolBarChanger();
	bool isEmpty() const;
	bool separatorsVisible() const;
	void setSeparatorsVisible(bool ASeparatorsVisible);
	bool autoHideEmptyToolbar() const;
	void setAutoHideEmptyToolbar(bool AAutoHide);
	QToolBar *toolBar() const;
	int itemGroup(QAction *AHandle) const;
	QList<QAction *> groupItems(int AGroup = TBG_NULL) const;
	QAction *widgetHandle(QWidget *AWidget) const;
	QWidget *handleWidget(QAction *AHandle) const;
	QAction *actionHandle(Action *AAction) const;
	Action *handleAction(QAction *AHandle) const;
	QAction *insertWidget(QWidget *AWidget, int AGroup = TBG_DEFAULT);
    ToolButton *insertAction(Action *AAction, int AGroup = TBG_DEFAULT);
	void removeItem(QAction *AHandle);
	void clear();
signals:
	void itemInserted(QAction *ABefore, QAction *AHandle, Action *AAction, QWidget *AWidget, int AGroup);
	void itemRemoved(QAction *AHandle);
	void toolBarChangerDestroyed(ToolBarChanger *AToolBarChanger);
protected:
	void updateVisible();
	void updateSeparatorVisible();
protected slots:
	void onWidgetDestroyed(QObject *AObject);
private:
	QToolBar *FToolBar;
	bool FAutoHideIfEmpty;
	bool FSeparatorsVisible;
	QAction *FAllignChange;
	QMap<int, QAction *> FSeparators;
	QMap<QWidget *, QAction *> FHandles;
	QMultiMap<int, QWidget *> FWidgets;
	QMap<Action *, QToolButton *> FButtons;
};

#endif // TOOLBARCHANGER_H
