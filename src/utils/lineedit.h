#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include "utilsexport.h"

class QHBoxLayout;

/*
LineEdit is a subclass of QLineEdit that provides an easy and simple
way to add widgets on the left or right hand side of the text.

The layout of the widgets on either side are handled by a QHBoxLayout.
You can set the spacing around the widgets with setWidgetSpacing().

As widgets are added to the class they are inserted from the outside
into the center of the widget.
*/
class SideWidget;
class UTILS_EXPORT LineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin)

public:
    enum WidgetPosition {
        LeftSide,
        RightSide
    };

    LineEdit(QWidget* parent = 0);
    LineEdit(const QString &contents, QWidget* parent = 0);

    void addWidget(QWidget* widget, WidgetPosition position);
    void removeWidget(QWidget* widget);
    void setWidgetSpacing(int spacing);
    int widgetSpacing() const;
    int textMargin(WidgetPosition position) const;

    int leftMargin() { return m_leftMargin; }
    void setSelectAllOnClick(bool bSelect);

public slots:
    void setLeftMargin(int margin);
    void updateTextMargins();

protected:
    void focusInEvent(QFocusEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    bool event(QEvent* event);

private:
    void init();

    SideWidget* m_leftWidget;
    SideWidget* m_rightWidget;
    QHBoxLayout* m_leftLayout;
    QHBoxLayout* m_rightLayout;
    QHBoxLayout* mainLayout;

    int m_leftMargin;
    bool m_ignoreMousePress;
    bool m_bSelectAllOnClick;
};


class UTILS_EXPORT SideWidget : public QWidget
{
    Q_OBJECT

signals:
    void sizeHintChanged();

public:
    SideWidget(QWidget* parent = 0);

protected:
    bool event(QEvent* event);

};

#endif // LINEEDIT_H
