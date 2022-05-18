#include "action.h"

Action::Action(QObject *AParent) : QAction(AParent)
{
	FMenu = NULL;
}

Action::~Action()
{
	emit actionDestroyed(this);
}

Menu *Action::menu() const
{
	return FMenu;
}

void Action::setMenu(Menu *AMenu)
{
	if (FMenu)
	{
		disconnect(FMenu,SIGNAL(menuDestroyed(Menu *)),this,SLOT(onMenuDestroyed(Menu *)));
		if (FMenu!=AMenu && FMenu->parent()==this)
			delete FMenu;
	}
	if (AMenu)
	{
		connect(AMenu,SIGNAL(menuDestroyed(Menu *)),SLOT(onMenuDestroyed(Menu *)));
	}
	QAction::setMenu(AMenu);
	FMenu = AMenu;
}

void Action::setIcon(const QIcon &AIcon)
{
	QAction::setIcon(AIcon);
}


QVariant Action::data(int ARole) const
{
	return FData.value(ARole);
}

void Action::setData(int ARole, const QVariant &AData)
{
	if (AData.isValid())
		FData.insert(ARole,AData);
	else
		FData.remove(ARole);
}

void Action::setData(const QHash<int,QVariant> &AData)
{
	FData.unite(AData);
}

QString Action::shortcutId() const
{
	return FShortcutId;
}

void Action::setShortcutId(const QString &AId)
{
	FShortcutId = AId;
	Shortcuts::bindObjectShortcut(AId, this);
}

void Action::onMenuDestroyed(Menu *AMenu)
{
	Q_UNUSED(AMenu);
	FMenu = NULL;
	QAction::setMenu(NULL);
}
