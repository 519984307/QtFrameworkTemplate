/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2012  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "clickablelabel.h"

#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
    setAttribute(Qt::WA_Hover, true);
    setMouseTracking(true);
    setClickable(true);
    m_bLeftPressed = false;
    m_bMiddlePressed = false;
}


void ClickableLabel::setClickable(bool bAble /* = true */)
{
    m_bClickable = bAble;
    if (m_bClickable)
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void ClickableLabel::mousePressEvent(QMouseEvent *ev)
{
    if (m_bClickable)
    {
        if (ev->button() == Qt::LeftButton && rect().contains(ev->pos())) {
            if (ev->modifiers() == Qt::ControlModifier) {
                m_bMiddlePressed = true;
                m_bLeftPressed = false;
            }
            else {
                m_bMiddlePressed = false;
                m_bLeftPressed = true;
            }
        }
        else if (ev->button() == Qt::MiddleButton && rect().contains(ev->pos())) {
            m_bMiddlePressed = true;
            m_bLeftPressed = false;
        }
        else {
            m_bMiddlePressed = false;
            m_bLeftPressed = false;
        }
    }
    QLabel::mousePressEvent(ev);

}


void ClickableLabel::mouseReleaseEvent(QMouseEvent* ev)
{
    if (m_bClickable)
    {
        if (ev->button() == Qt::LeftButton && rect().contains(ev->pos())) {
            if (ev->modifiers() == Qt::ControlModifier && m_bMiddlePressed) {
                emit middleClicked(ev->globalPos());
            }
            else if(m_bLeftPressed){
                emit clicked(ev->globalPos());
                emit clicked();
            }
        }
        else if (ev->button() == Qt::MiddleButton && rect().contains(ev->pos()) && m_bMiddlePressed) {
            emit middleClicked(ev->globalPos());
        }
        m_bMiddlePressed = false;
        m_bLeftPressed = false;
    }

    QLabel::mouseReleaseEvent(ev);
}


void ClickableLabel::enterEvent(QEvent *ev)
{
    emit hoverEnter();
    QLabel::enterEvent(ev);
}

void ClickableLabel::leaveEvent(QEvent *ev)
{
    emit hoverLeave();
    QLabel::leaveEvent(ev);
}


void ClickableLabel::setThemeIcon(const QString &name)
{
    QIcon icon = QIcon::fromTheme(name);

    if (!icon.isNull()) {
        adjustSize();
        setPixmap(icon.pixmap(size()));
    }
}

QIcon ClickableLabel::fallbackIcon() const
{
    return pixmap() ? QIcon(*pixmap()) : QIcon();
}

void ClickableLabel::setFallbackIcon(const QIcon &image)
{
    if (!pixmap() || pixmap()->isNull()) {
        adjustSize();
        setPixmap(image.pixmap(size()));
    }
}

QString ClickableLabel::themeIcon() const
{
    return m_themeIcon;
}

