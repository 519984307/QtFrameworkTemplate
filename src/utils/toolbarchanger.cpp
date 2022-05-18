#include "toolbarchanger.h"

#include <QTimer>
#include <QLayout>

ToolBarChanger::ToolBarChanger(QToolBar *AToolBar) : QObject(AToolBar)
{
	FSeparatorsVisible = true;
	FAutoHideIfEmpty = true;

	FToolBar = AToolBar;
	FToolBar->clear();

	QWidget *widget = new QWidget(FToolBar);
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	FAllignChange = insertWidget(widget, TBG_ALLIGN_CHANGE);
	FAllignChange->setVisible(false);

	updateVisible();
}

ToolBarChanger::~ToolBarChanger()
{
	emit toolBarChangerDestroyed(this);
}

bool ToolBarChanger::isEmpty() const
{
	return FWidgets.count() < 2;
}

bool ToolBarChanger::separatorsVisible() const
{
	return FSeparatorsVisible;
}

void ToolBarChanger::setSeparatorsVisible(bool ASeparatorsVisible)
{
	FSeparatorsVisible = ASeparatorsVisible;
	foreach(QAction *separator, FSeparators.values())
		separator->setVisible(ASeparatorsVisible);
	updateSeparatorVisible();
}

bool ToolBarChanger::autoHideEmptyToolbar() const
{
	return FAutoHideIfEmpty;
}

void ToolBarChanger::setAutoHideEmptyToolbar(bool AAutoHide)
{
	FAutoHideIfEmpty = AAutoHide;
	updateVisible();
}

QToolBar *ToolBarChanger::toolBar() const
{
	return FToolBar;
}

int ToolBarChanger::itemGroup(QAction *AHandle) const
{
	return FWidgets.key(FHandles.key(AHandle));
}

QList<QAction *> ToolBarChanger::groupItems(int AGroup) const
{
	QList<QAction *> handles;
	QList<QWidget *> widgets = AGroup!=TBG_NULL ? FWidgets.values(AGroup) : FWidgets.values();
	foreach(QWidget *widget, widgets)
		handles.append(FHandles.value(widget));
	return handles;
}

QAction *ToolBarChanger::widgetHandle(QWidget *AWidget) const
{
	return FHandles.value(AWidget);
}

QWidget *ToolBarChanger::handleWidget(QAction *AHandle) const
{
	return FHandles.key(AHandle);
}

QAction *ToolBarChanger::actionHandle(Action *AAction) const
{
	return FHandles.value(FButtons.value(AAction));
}

Action *ToolBarChanger::handleAction(QAction *AHandle) const
{
	return FButtons.key(qobject_cast<QToolButton *>(FHandles.key(AHandle)));
}

QAction *ToolBarChanger::insertWidget(QWidget *AWidget, int AGroup)
{
	if (!FWidgets.values().contains(AWidget))
	{
		if (AGroup > TBG_ALLIGN_CHANGE)
			FAllignChange->setVisible(true);

		QMap<int, QAction *>::const_iterator it = FSeparators.upperBound(AGroup);
		QAction *before = it!=FSeparators.end() ? it.value() : NULL;

		QAction *handle = before!=NULL ? FToolBar->insertWidget(before, AWidget) : FToolBar->addWidget(AWidget);
		if (!FSeparators.contains(AGroup))
		{
			QAction *separator = FToolBar->insertSeparator(handle);
			separator->setVisible(FSeparatorsVisible);
			FSeparators.insert(AGroup, separator);
			updateSeparatorVisible();
		}
		FWidgets.insertMulti(AGroup,AWidget);
		FHandles.insert(AWidget, handle);
		connect(AWidget,SIGNAL(destroyed(QObject *)),SLOT(onWidgetDestroyed(QObject *)));

		emit itemInserted(before,handle,FButtons.key(qobject_cast<QToolButton *>(AWidget)),AWidget,AGroup);
		updateVisible();
	}
	return FHandles.value(AWidget);
}

ToolButton *ToolBarChanger::insertAction(Action *AAction, int AGroup)
{
    ToolButton *button = new ToolButton(FToolBar);
	button->setToolButtonStyle(FToolBar->toolButtonStyle());
	button->setDefaultAction(AAction);
	FButtons.insert(AAction, button);
	insertWidget(button, AGroup);
	return button;
}

void ToolBarChanger::removeItem(QAction *AHandle)
{
	QWidget *widget = FHandles.key(AHandle, NULL);
	if (widget && AHandle!=FAllignChange)
	{
		AHandle->deleteLater();
		FToolBar->removeAction(AHandle);
		disconnect(widget,SIGNAL(destroyed(QObject *)),this,SLOT(onWidgetDestroyed(QObject *)));

		Action *action = FButtons.key(qobject_cast<QToolButton *>(widget), NULL);
		if (action)
			FButtons.take(action)->deleteLater();

		int group = FWidgets.key(widget);
		FWidgets.remove(group,widget);
		if (!FWidgets.contains(group))
		{
			QAction *separator = FSeparators.take(group);
			FToolBar->removeAction(separator);
			delete separator;
			updateSeparatorVisible();
		}
		if (FWidgets.keys().last()<=TBG_ALLIGN_CHANGE)
		{
			FAllignChange->setVisible(false);
		}

		FHandles.remove(widget);
		emit itemRemoved(AHandle);
		updateVisible();
	}
}

void ToolBarChanger::clear()
{
	foreach(QAction *handle, FHandles.values())
		removeItem(handle);
	FToolBar->clear();
}

void ToolBarChanger::updateVisible()
{
	FToolBar->setMaximumWidth(!FAutoHideIfEmpty || !isEmpty() ? QWIDGETSIZE_MAX : 0);
	FToolBar->setMaximumHeight(!FAutoHideIfEmpty || !isEmpty() ? QWIDGETSIZE_MAX : 0);
}

void ToolBarChanger::updateSeparatorVisible()
{
	const QList<QAction *> separators = FSeparators.values();
	if (FSeparators.count() > 2)
		separators.at(1)->setVisible(FSeparatorsVisible);
	separators.first()->setVisible(false);
	FSeparators.value(TBG_ALLIGN_CHANGE)->setVisible(false);
}

void ToolBarChanger::onWidgetDestroyed(QObject *AObject)
{
	foreach(QWidget *widget, FWidgets.values())
		if (qobject_cast<QObject *>(widget) == AObject)
			removeItem(FHandles.value(widget));
}