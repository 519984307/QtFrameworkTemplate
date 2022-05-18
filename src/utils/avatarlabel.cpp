#include "avatarlabel.h"
#include <QPainter>
#include "borderpixmap.h"
#include <QMovie>
#include "colors.h"

AvatarLabel::AvatarLabel(QWidget *parent) :
    ClickableLabel(parent)
{
    setObjectName("labelAvatar");
    setClickable(false);
    m_borderWidth = 1;
    m_borderNormalColor = Colors::colorFromText("#d1d1d1");
    m_bDrawSelf = true;
}

void AvatarLabel::setNormalBorderColor(const QColor &clr)
{
    m_borderNormalColor = clr;
}

void AvatarLabel::setHoverBorderColor(const QColor &clr)
{
    m_borderHoverColor = clr;
}

void AvatarLabel::setBorderWidth(const int width)
{
    m_borderWidth = width;
}


void AvatarLabel::setPixmap(const QPixmap &pix)
{
    QLabel::setPixmap(pix);
    if(!m_pixmapNormal.isNull())
    {
        m_pixmapNormal = BorderPixmap::circleBorderPixmap(pix, m_borderNormalColor, rect().size(), m_borderWidth);
    }
    if(!m_pixmapHover.isNull())
    {
        m_pixmapHover = BorderPixmap::circleBorderPixmap(pix, m_borderNormalColor, rect().size(), m_borderWidth, m_borderHoverColor);
    }
    m_bDrawSelf = true;
}

void AvatarLabel::setNormalHoverPixmap(const QPixmap &normal, const QPixmap &hover)
{
    m_pixmapHover = hover;
    m_pixmapNormal = normal;
    m_bDrawSelf = false;
}

void AvatarLabel::paintEvent(QPaintEvent *ev)
{
    QRect paintRect = rect();
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    if (paintRect.contains(mapFromGlobal(QCursor::pos())) && isClickable())
    {
        if(m_borderNormalColor.isValid() && m_bDrawSelf)
        {
            if(movie() != NULL)
            {
                QPixmap pixmapOriginal = movie()->currentPixmap();
                m_pixmapHover = BorderPixmap::circleBorderPixmap(pixmapOriginal, m_borderNormalColor, paintRect.size(), m_borderWidth, m_borderHoverColor);
                painter.drawPixmap(paintRect, m_pixmapHover);
            }
            else
            {
                if(m_pixmapHover.isNull() || m_pixmapHover.size() != paintRect.size())
                    m_pixmapHover = BorderPixmap::circleBorderPixmap(*pixmap(), m_borderNormalColor, paintRect.size(), m_borderWidth, m_borderHoverColor);
                painter.drawPixmap(paintRect, m_pixmapHover);
            }

            //painter.end();
            return;
        }
        else if(!m_bDrawSelf && !m_pixmapHover.isNull())
        {
            if(paintRect.size() != m_pixmapHover.size())
            {
                m_pixmapHover = m_pixmapHover.scaled(paintRect.size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
            }
            painter.drawPixmap(paintRect, m_pixmapHover);
            return;
        }

    }
    else
    {
        if(m_borderNormalColor.isValid() && m_bDrawSelf)
        {
            if(movie() != NULL)
            {
                QPixmap pixmapOriginal = movie()->currentPixmap();
                m_pixmapNormal = BorderPixmap::circleBorderPixmap(pixmapOriginal, m_borderNormalColor, paintRect.size(), m_borderWidth);
                painter.drawPixmap(paintRect, m_pixmapNormal);
            }
            else
            {
                if(m_pixmapNormal.isNull() || m_pixmapNormal.size() != paintRect.size())
                    m_pixmapNormal = BorderPixmap::circleBorderPixmap(*pixmap(), m_borderNormalColor, paintRect.size(), m_borderWidth);
                painter.drawPixmap(paintRect, m_pixmapNormal);
            }
            //painter.end();
            return;
        }
        else if(!m_bDrawSelf && !m_pixmapNormal.isNull())
        {
            if(paintRect.size() != m_pixmapNormal.size())
            {
                m_pixmapNormal = m_pixmapNormal.scaled(paintRect.size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
            }
            painter.drawPixmap(paintRect, m_pixmapNormal);
            return;
        }
    }
    //painter.end();
    QLabel::paintEvent(ev);
}
