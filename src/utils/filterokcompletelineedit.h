#ifndef FILTEROKCOMPLETELINEEDIT_H
#define FILTEROKCOMPLETELINEEDIT_H

#include "utilsexport.h"
#include "FilterOkLineEdit.h"
#include <QSortFilterProxyModel>
#include <QInputMethodEvent>

class QListView;
class QModelIndex;
class QAbstractItemModel;

class UTILS_EXPORT FilterOkCompleteLineEdit : public FilterOkLineEdit
{  
	Q_OBJECT  

public:  
	FilterOkCompleteLineEdit(QWidget *parent = 0);

    QListView *view();

	void setModel(QAbstractItemModel *model);
	QAbstractItemModel* model() const;
    void setColorPlaceholderText(const QString &text, const QColor &color);
    void refreshListViewPos();

public slots:  
	void setCompleter(const QString &text);
	void completeText(const QModelIndex &index);

protected:  
	virtual void keyPressEvent(QKeyEvent *e);  
    virtual void focusOutEvent(QFocusEvent *e);
    virtual void paintEvent(QPaintEvent *e);

    void inputMethodEvent(QInputMethodEvent *e);

private:  
	QListView             *m_listView;
	QAbstractItemModel    *m_model;
	QSortFilterProxyModel *m_proxyModel;
    QString m_colorPlaceHolderText;
    QColor m_colorPlaceHolderColor;
    bool m_hidePlaceHolder;
};  

class SearchItemFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	SearchItemFilterProxyModel(QObject *parent);

protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // FILTEROKCOMPLETELINEEDIT_H
