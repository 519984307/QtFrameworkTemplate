#include "circleavatarlabel.h"
#include <QPainter>
#include "borderpixmap.h"
#include "colors.h"

CircleAvatarLabel::CircleAvatarLabel(QWidget *parent) :
    ClickableLabel(parent)
{
    setObjectName("circleavatarlabel");
    setClickable(false);
    m_borderWidth = 0;
    m_borderNormalColor = Colors::colorFromText("#d1d1d1");
    m_bDrawSelf = true;
}


void CircleAvatarLabel::setNormalBorderColor(const QColor &clr)
{
    m_borderNormalColor = clr;
    update();
}

void CircleAvatarLabel::setHoverBorderColor(const QColor &clr)
{
    m_borderHoverColor = clr;
    update();
}

void CircleAvatarLabel::setBorderWidth(const int width)
{
    m_borderWidth = width;
    if(m_borderWidth < 0)
        m_borderWidth = 0;
    update();
}

void CircleAvatarLabel::generatePixmaps()
{
    if(!pixmap())
        return;
    QPixmap originalPixmap = *pixmap();
    if(m_borderWidth <= 0)
    {
        m_pixmapNormal = BorderPixmap::circlePixmap(originalPixmap, rect().size());
        m_pixmapHover = m_pixmapNormal;
    }
    else{
        Q_ASSERT(m_borderNormalColor.isValid());
        m_pixmapNormal = BorderPixmap::circleBorderPixmap(originalPixmap, m_borderNormalColor, rect().size(), m_borderWidth);

        if(m_borderHoverColor.isValid())
        {
            m_pixmapHover = BorderPixmap::circleBorderPixmap(originalPixmap, m_borderNormalColor, rect().size(), m_borderWidth, m_borderHoverColor);
        }
        else{
            m_pixmapHover = m_pixmapNormal;
        }

    }
}

void CircleAvatarLabel::setPixmap(const QPixmap &pix)
{
    QLabel::setPixmap(pix);
    generatePixmaps();
    m_bDrawSelf = true;
    update();
}

void CircleAvatarLabel::setNormalHoverPixmap(const QPixmap &normal, const QPixmap &hover)
{
    m_pixmapNormal = normal;
    m_pixmapHover = hover;
    m_bDrawSelf = false;
}

void CircleAvatarLabel::paintEvent(QPaintEvent *ev)
{
    if(pixmap() && m_bDrawSelf)
    {
        QRect paintRect = rect();
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
        if (paintRect.contains(mapFromGlobal(QCursor::pos())))
        {
            if(paintRect.size() != m_pixmapHover.size())
            {
                generatePixmaps();

            }
            painter.drawPixmap(paintRect, m_pixmapHover);
        }
        else
        {
            if(paintRect.size() != m_pixmapNormal.size())
            {
                generatePixmaps();

            }
            painter.drawPixmap(paintRect, m_pixmapNormal);

        }
        //painter.end();
        return;
    }

    else if(!m_bDrawSelf && !m_pixmapHover.isNull() && !m_pixmapNormal.isNull())
    {
        QRect paintRect = rect();
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
        if (paintRect.contains(mapFromGlobal(QCursor::pos())))
        {
            if(paintRect.size() != m_pixmapHover.size())
            {
                m_pixmapHover = m_pixmapHover.scaled(paintRect.size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
            }
            painter.drawPixmap(paintRect, m_pixmapHover);
        }
        else
        {
            if(paintRect.size() != m_pixmapNormal.size())
            {
                m_pixmapNormal = m_pixmapNormal.scaled(paintRect.size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
            }
            painter.drawPixmap(paintRect, m_pixmapNormal);
        }
        return;
    }

    QLabel::paintEvent(ev);
}
