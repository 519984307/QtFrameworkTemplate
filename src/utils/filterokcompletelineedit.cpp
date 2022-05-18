#include "FilterOkCompleteLineEdit.h"  
#include <QKeyEvent>  
#include <QListView>  
#include <QAbstractItemModel>
#include <QPainter>
#include <QDebug>

#include "chineseletterhelper.h"

//////////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS OF CLASS FilterOkCompleteLineEdit
FilterOkCompleteLineEdit::FilterOkCompleteLineEdit(QWidget *parent)  
	: FilterOkLineEdit(parent), m_model(0)
{  
	m_listView = new QListView(this);
    m_listView->setWindowFlags(Qt::ToolTip);

	m_proxyModel = new SearchItemFilterProxyModel(this);

	bool connected = false;
	connected = connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(setCompleter(const QString &)));  
	Q_ASSERT(connected);

	connected = connect(m_listView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));  
	Q_ASSERT(connected);

	connected = connect(m_listView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));
	Q_ASSERT(connected);

    m_hidePlaceHolder = false;
}

QListView * FilterOkCompleteLineEdit::view()
{
	return m_listView;
}

void FilterOkCompleteLineEdit::setModel(QAbstractItemModel *model)
{
	if (model)
	{
		if (m_model)
		{
			delete m_model;
			m_model = 0;
		}
		m_model = model;
		m_proxyModel->setSourceModel(m_model);
		m_listView->setModel(m_proxyModel);
	}
}

QAbstractItemModel* FilterOkCompleteLineEdit::model() const
{
	return m_model;
}

void FilterOkCompleteLineEdit::setColorPlaceholderText(const QString &text, const QColor &color)
{
    setPlaceholderText(QString());
    m_colorPlaceHolderColor = color;
    m_colorPlaceHolderText = text;
}

void FilterOkCompleteLineEdit::paintEvent(QPaintEvent *e)
{
    FilterOkLineEdit::paintEvent(e);
    if(text().isEmpty() && !m_colorPlaceHolderText.isEmpty() && placeholderText().isEmpty())
    {
        QPainter p(this);
        QRect r = rect();
        QStyleOptionFrameV2 panel;
        initStyleOption(&panel);
        style()->drawPrimitive(QStyle::PE_PanelLineEdit, &panel, &p, this);
        r = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);
        r.setX(r.x() + textMargins().left());
        r.setY(r.y() + textMargins().top());
        r.setRight(r.right() - textMargins().right());
        r.setBottom(r.bottom() - textMargins().bottom());
        p.setClipRect(r);

        QFontMetrics fm = fontMetrics();
        Qt::Alignment va = QStyle::visualAlignment(layoutDirection(), QFlag(alignment()));
        int vscroll = 0;
        int verticalMargin = 5;
        int horizontalMargin = 5;
        switch (va & Qt::AlignVertical_Mask) {
         case Qt::AlignBottom:
             vscroll = r.y() + r.height() - fm.height() - verticalMargin;
             break;
         case Qt::AlignTop:
             vscroll = r.y() + verticalMargin;
             break;
         default:
             //center
             vscroll = r.y() + (r.height() - fm.height() + 1) / 2;
             break;
        }
        QRect lineRect(r.x() + horizontalMargin, vscroll, r.width() - 2*horizontalMargin, fm.height());

        QPen oldpen = p.pen();
        p.setPen(m_colorPlaceHolderColor);
        if(!m_hidePlaceHolder)
        {
            p.drawText(lineRect, va, m_colorPlaceHolderText);
        }
        p.setPen(oldpen);
        return;
    }
}

void FilterOkCompleteLineEdit::inputMethodEvent(QInputMethodEvent *e)
{
    QLineEdit::inputMethodEvent(e);
    if(!e->preeditString().isEmpty())
    {
        m_hidePlaceHolder = true;
    }
    else if(!e->commitString().isEmpty())
    {
        m_hidePlaceHolder =false;
    }

    if ( e->preeditString().isEmpty()
        && e->commitString().isEmpty() )
    {
        m_hidePlaceHolder = false;
    }
}

void FilterOkCompleteLineEdit::focusOutEvent(QFocusEvent *e) 
{
    if (!m_listView->isHidden() && !m_listView->hasFocus())
        m_listView->hide();

    FilterOkLineEdit::focusOutEvent(e);
}

void FilterOkCompleteLineEdit::keyPressEvent(QKeyEvent *e) 
{
	if (!m_listView->isHidden()) 
	{  
		int key = e->key();  
		int count = m_listView->model()->rowCount();  
		QModelIndex currentIndex = m_listView->currentIndex();  
		if (Qt::Key_Down == key) 
		{
			int row = currentIndex.row() + 1;  
			if (row >= count) {  
				row = 0;  
			}  
			QModelIndex index = m_listView->model()->index(row, 0);  
			m_listView->setCurrentIndex(index);
		} 
		else if (Qt::Key_Up == key) 
		{  
			int row = currentIndex.row() - 1;  
			if (row < 0) {  
				row = count - 1;  
			}  
			QModelIndex index = m_listView->model()->index(row, 0);  
			m_listView->setCurrentIndex(index);  
		} 
		else if (Qt::Key_Escape == key) 
		{  
			m_listView->hide();  
		} 
		else if (Qt::Key_Enter == key || Qt::Key_Return == key) 
		{  
			if (currentIndex.isValid()) {  
				QString text = m_listView->currentIndex().data().toString();  
				setText(text);  
			}  
            m_listView->hide();

			QLineEdit::keyPressEvent(e);
		} else {  
            m_listView->hide();
			QLineEdit::keyPressEvent(e);  
		}  
	} 
	else 
	{  
		QLineEdit::keyPressEvent(e);  
	}  
}  

void FilterOkCompleteLineEdit::setCompleter(const QString &text) 
{  
	if (text.isEmpty()) 
	{  
		m_listView->hide();  
		return;  
	}

	m_proxyModel->setFilterRegExp(text);
	m_proxyModel->invalidate();

	if (m_proxyModel->rowCount() == 0) 
	{  
		if (!m_listView->isHidden())
			m_listView->hide();
		return;  
	}  

	// Position the text edit  
	if (m_listView->isHidden())
	{
		m_listView->setMinimumWidth(width());  
		m_listView->setMaximumWidth(width());  
		QPoint p(0, height());  
		int x = mapToGlobal(p).x();  
		int y = mapToGlobal(p).y() + 1;  
		m_listView->move(x, y);  
		m_listView->show();
        m_listView->setFocus();
        setFocus();
	}
}  

void FilterOkCompleteLineEdit::completeText(const QModelIndex &index) 
{
	if (index.isValid())
	{
		QString text = index.data().toString();  
		setText(text);

		emit rightButtonClicked();
        m_listView->hide();
    }
}

void FilterOkCompleteLineEdit::refreshListViewPos()
{
    if(!m_listView->isHidden())
    {
        QPoint p(0, height());
        int x = mapToGlobal(p).x();
        int y = mapToGlobal(p).y() + 1;
        m_listView->move(x, y);
    }
}

//////////////////////////////////////////////////////////////////////////
// MEMBER FUNCTIONS OF CLASS SearchItemFilterProxyModel
SearchItemFilterProxyModel::SearchItemFilterProxyModel(QObject *parent)
: QSortFilterProxyModel(parent)
{

}

bool SearchItemFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
	QString patternString = filterRegExp().pattern();

    QString src = sourceModel()->data(index).toString();
    QString firstLetters = ChineseLetterHelper::GetFirstLetters(src);
    QString pinyins = ChineseLetterHelper::GetPinyins(src);

    if(patternString.isEmpty())
    {
        return false;
    }

    //qDebug() << QString("====== filter = %1, src = %2, src_spell = %3").arg(patternString).arg(src).arg(spell);
    return (src.contains(patternString, Qt::CaseInsensitive) // 搜索文字匹配
            || firstLetters.contains(patternString, Qt::CaseInsensitive) // 搜索汉字首字母匹配
            || (pinyins.contains(patternString, Qt::CaseInsensitive) && firstLetters.contains(patternString.at(0), Qt::CaseInsensitive))); // 搜索汉字拼音匹配，且搜索项首字母匹配被搜索文字首字母
}
