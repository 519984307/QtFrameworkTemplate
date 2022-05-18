#include "skinmanager.h"
#include <QPainter>
#include <QLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "widgetmanager.h"


SkinManager::SkinManager(QObject *parent) :
    QObject(parent)
{
    m_framelessHelper = new NcFramelessHelper(this);
}

SkinManager* SkinManager::sharedManager()
{
    ISkinManagerHolder* skinManagerHolder = qobject_cast<ISkinManagerHolder*>(qApp);
    if(skinManagerHolder)
    {
        return skinManagerHolder->skinManager();
    }
    static SkinManager* _sharedManager = NULL;
    if(_sharedManager == NULL)
    {
        _sharedManager = new SkinManager();
    }
    return _sharedManager;
}

QPixmap SkinManager::generateWidgetBG(ISkinWidget *widget) const
{
    QString objName = widget->instance()->objectName();
    SkinWidgetSubBGs subBGs = m_widgetSubBGs[objName];

    int offset = widget->skinData().bgSizes.radius - widget->skinData().bgSizes.border;

    if(widget->skinData().bTopBottomFirst)
    {
        if(widget->isMaximized())
        {
            QPixmap pixmap(widget->instance()->size());
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
            if(subBGs.topBar.height() > 0)
            {
                QRect paintRect = QRect(0,
                                        0,
                                        pixmap.width(),
                                        subBGs.topBar.height() + offset);
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.topBar.width())
                {
                    QPixmap pix = subBGs.topBar.copy(subBGs.topBar.width()- paintRect.width(), 0, paintRect.width(), subBGs.topBar.height());
                    painter.drawPixmap(paintRect, pix);
                }else
                {
                    painter.drawPixmap(paintRect, subBGs.topBar);
                }
            }
            if(subBGs.leftBar.width() > 0)
            {
                QRect paintRect = QRect(0,
                                        subBGs.topBar.height() + offset,
                                        subBGs.leftBar.width(),
                                        pixmap.height() - subBGs.topBar.height() - subBGs.bottomBar.height() - 2 * offset);
                painter.drawPixmap(paintRect, subBGs.leftBar);
            }
            if(subBGs.rightBar.width() > 0)
            {
                QRect paintRect = QRect(pixmap.width() - subBGs.rightBar.width(),
                                        subBGs.topBar.height() + offset,
                                        subBGs.rightBar.width(),
                                        pixmap.height() - subBGs.topBar.height() - subBGs.bottomBar.height() - 2 * offset);
                painter.drawPixmap(paintRect, subBGs.rightBar);
            }
            if(subBGs.bottomBar.height() > 0)
            {
                QRect paintRect = QRect(0,
                                        pixmap.height() - subBGs.bottomBar.height() - offset,
                                        pixmap.width(),
                                        subBGs.bottomBar.height() + offset);
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.bottomBar.width())
                {
                    QPixmap pix = subBGs.bottomBar.copy(subBGs.bottomBar.width()-paintRect.width(), 0, paintRect.width(), subBGs.bottomBar.height());
                    painter.drawPixmap(paintRect, pix);
                }else
                {
                    painter.drawPixmap(paintRect, subBGs.bottomBar);
                }
            }
            QRect paintRect = QRect(subBGs.leftBar.width(),
                                    subBGs.topBar.height() + offset,
                                    pixmap.width()-subBGs.leftBar.width()-subBGs.rightBar.width(),
                                    pixmap.height() -subBGs.topBar.height() - subBGs.bottomBar.height() - 2 * offset);
            painter.drawPixmap(paintRect, subBGs.central);
            //painter.end();
            return pixmap;
        }
        else
        {
            QPixmap pixmap(widget->instance()->size());
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            QRect paintRect;
            painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
            if(!subBGs.topLeftCorner.isNull())
            {
                paintRect = QRect(0,
                                  0,
                                  subBGs.topLeftCorner.width(),
                                  subBGs.topLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.topLeftCorner);
            }
            if(!subBGs.topBorder.isNull())
            {
                paintRect = QRect(subBGs.topLeftCorner.width(),
                                  0,
                                  pixmap.width() - subBGs.topLeftCorner.width() *2,
                                  subBGs.topBorder.height());
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.topBorder.width())
                {
                    QPixmap pix = subBGs.topBorder.copy(subBGs.topBorder.width()-paintRect.width(), 0, paintRect.width(), subBGs.topBorder.height());
                    painter.drawPixmap(paintRect, pix);
                }
                else
                {
                    painter.drawPixmap(paintRect, subBGs.topBorder);
                }
            }
            if(!subBGs.topRightCorner.isNull())
            {
                paintRect = QRect(pixmap.width() - subBGs.topRightCorner.width(),
                                  0,
                                  subBGs.topRightCorner.width(),
                                  subBGs.topRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.topRightCorner);
            }
            if(subBGs.topBar.height() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width(),
                                  subBGs.topBorder.height(),
                                  pixmap.width() - subBGs.leftBorder.width() - subBGs.rightBorder.width(),
                                  subBGs.topBar.height());
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.topBar.width())
                {
                    QPixmap pix = subBGs.topBar.copy(subBGs.topBar.width()-paintRect.width(), 0, paintRect.width(), subBGs.topBar.height());
                    painter.drawPixmap(paintRect, pix);
                }
                else
                {
                    painter.drawPixmap(paintRect, subBGs.topBar);
                }

            }
            if(subBGs.leftBorder.width() > 0)
            {
                paintRect = QRect(0,
                                  subBGs.topLeftCorner.height(),
                                  subBGs.leftBorder.width(),
                                  pixmap.height() - subBGs.topLeftCorner.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.leftBorder);
            }
            if(subBGs.leftBar.width() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width(),
                                  subBGs.topLeftCorner.height() + subBGs.topBar.height(),
                                  subBGs.leftBar.width(),
                                  pixmap.height() - subBGs.topBar.height() - subBGs.topLeftCorner.height() - subBGs.bottomBar.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.leftBar);
            }
            if(subBGs.rightBorder.width() > 0)
            {
                paintRect = QRect(pixmap.width() - subBGs.rightBorder.width(),
                                  subBGs.topLeftCorner.height(),
                                  subBGs.rightBorder.width(),
                                  pixmap.height() - subBGs.topLeftCorner.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.rightBorder);
            }
            if(subBGs.rightBar.width() > 0)
            {
                paintRect = QRect(pixmap.width() - subBGs.rightBar.width() - subBGs.rightBorder.width(),
                                  subBGs.topBar.height() + subBGs.topRightCorner.height(),
                                  subBGs.rightBar.width(),
                                  pixmap.height() - subBGs.topBar.height() - subBGs.topRightCorner.height() - subBGs.bottomBar.height() - subBGs.bottomRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.rightBar);
            }
            if(!subBGs.bottomLeftCorner.isNull())
            {
                paintRect = QRect(0,
                                  pixmap.height() - subBGs.bottomLeftCorner.height(),
                                  subBGs.bottomLeftCorner.width(),
                                  subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.bottomLeftCorner);
            }
            if(!subBGs.bottomBorder.isNull())
            {
                paintRect = QRect(subBGs.bottomLeftCorner.width(),
                                  pixmap.height() - subBGs.bottomBorder.height(),
                                  pixmap.width() - subBGs.bottomLeftCorner.width() - subBGs.bottomRightCorner.width(),
                                  subBGs.bottomBorder.height());
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.bottomBorder.width())
                {
                    QPixmap pix = subBGs.bottomBorder.copy(subBGs.bottomBorder.width()-paintRect.width(), 0, paintRect.width(), subBGs.bottomBorder.height());
                    painter.drawPixmap(paintRect, pix);
                }
                else
                {
                    painter.drawPixmap(paintRect, subBGs.bottomBorder);
                }
            }
            if(!subBGs.bottomRightCorner.isNull())
            {
                paintRect = QRect(pixmap.width() - subBGs.bottomRightCorner.width(),
                                  pixmap.height() - subBGs.bottomRightCorner.height(),
                                  subBGs.bottomRightCorner.width(),
                                  subBGs.bottomRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.bottomRightCorner);
            }
            if(subBGs.bottomBar.height() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width(),
                                  pixmap.height() - subBGs.bottomBar.height() - subBGs.bottomBorder.height(),
                                  pixmap.width() - subBGs.leftBorder.width() - subBGs.rightBorder.width(),
                                  subBGs.bottomBar.height());
                if(!widget->skinData().bCompressPixmap && paintRect.width() < subBGs.bottomBar.width())
                {
                    QPixmap pix = subBGs.bottomBar.copy(subBGs.bottomBar.width()-paintRect.width(), 0, paintRect.width(), subBGs.bottomBar.height());
                    painter.drawPixmap(paintRect, pix);
                }
                else
                {
                    painter.drawPixmap(paintRect, subBGs.bottomBar);
                }

            }
            paintRect = QRect(subBGs.leftBar.width()+subBGs.leftBorder.width(),
                              subBGs.topBar.height() + subBGs.topBorder.height(),
                              pixmap.width()-subBGs.leftBar.width()-subBGs.leftBorder.width()-subBGs.rightBar.width()-subBGs.rightBorder.width(),
                              pixmap.height() -subBGs.topBar.height()- subBGs.topBorder.height() - subBGs.bottomBar.height() - subBGs.bottomBorder.height());
            painter.drawPixmap(paintRect, subBGs.central);
            //painter.end();
            return pixmap;
        }
    }
    else
    {
        if(widget->isMaximized())
        {
            QPixmap pixmap(widget->instance()->size());
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
            if(subBGs.leftBar.width() > 0)
            {
                QRect paintRect = QRect(0,
                                        0,
                                        subBGs.leftBar.width(),
                                        pixmap.height());
                painter.drawPixmap(paintRect, subBGs.leftBar);
            }
            if(subBGs.topBar.height() > 0)
            {
                QRect paintRect = QRect(subBGs.leftBar.width(),
                                        0,
                                        pixmap.width() - subBGs.leftBar.width() - subBGs.rightBar.width(),
                                        subBGs.topBar.height());
                painter.drawPixmap(paintRect, subBGs.topBar);
            }

            if(subBGs.rightBar.width() > 0)
            {
                QRect paintRect = QRect(pixmap.width() - subBGs.rightBar.width(),
                                        0,
                                        subBGs.rightBar.width(),
                                        pixmap.height());
                painter.drawPixmap(paintRect, subBGs.rightBar);
            }
            if(subBGs.bottomBar.height() > 0)
            {
                QRect paintRect = QRect(subBGs.leftBar.width(),
                                        pixmap.height() - subBGs.bottomBar.height(),
                                        pixmap.width() - subBGs.leftBar.width() - subBGs.rightBar.width(),
                                        subBGs.bottomBar.height());
                painter.drawPixmap(paintRect, subBGs.bottomBar);
            }
            QRect paintRect = QRect(subBGs.leftBar.width(),
                                    subBGs.topBar.height(),
                                    pixmap.width()-subBGs.leftBar.width()-subBGs.rightBar.width(),
                                    pixmap.height() -subBGs.topBar.height() - subBGs.bottomBar.height());
            painter.drawPixmap(paintRect, subBGs.central);
            //painter.end();
            return pixmap;
        }
        else
        {
            QPixmap pixmap(widget->instance()->size());
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            QRect paintRect;
            painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
            if(!subBGs.topLeftCorner.isNull())
            {
                paintRect = QRect(0,
                                  0,
                                  subBGs.topLeftCorner.width(),
                                  subBGs.topLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.topLeftCorner);
            }
            if(!subBGs.topBorder.isNull())
            {
                paintRect = QRect(subBGs.topLeftCorner.width(),
                                  0,
                                  pixmap.width() - subBGs.topLeftCorner.width() *2,
                                  subBGs.topBorder.height());
                painter.drawPixmap(paintRect, subBGs.topBorder);
            }
            if(!subBGs.topRightCorner.isNull())
            {
                paintRect = QRect(pixmap.width() - subBGs.topRightCorner.width(),
                                  0,
                                  subBGs.topRightCorner.width(),
                                  subBGs.topRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.topRightCorner);
            }
            if(subBGs.topBar.height() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width() + subBGs.leftBar.width(),
                                  subBGs.topBorder.height(),
                                  pixmap.width() - subBGs.leftBorder.width() - subBGs.leftBar.width() - subBGs.rightBorder.width() - subBGs.rightBar.width(),
                                  subBGs.topBar.height());
                painter.drawPixmap(paintRect, subBGs.topBar);
            }
            if(subBGs.leftBorder.width() > 0)
            {
                paintRect = QRect(0,
                                  subBGs.topLeftCorner.height(),
                                  subBGs.leftBorder.width(),
                                  pixmap.height() - subBGs.topLeftCorner.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.leftBorder);
            }
            if(subBGs.leftBar.width() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width(),
                                  subBGs.topLeftCorner.height(),
                                  subBGs.leftBar.width(),
                                  pixmap.height() - subBGs.topLeftCorner.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.leftBar);
            }
            if(subBGs.rightBorder.width() > 0)
            {
                paintRect = QRect(pixmap.width() - subBGs.rightBorder.width(),
                                  subBGs.topLeftCorner.height(),
                                  subBGs.rightBorder.width(),
                                  pixmap.height() - subBGs.topLeftCorner.height() - subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.rightBorder);
            }
            if(subBGs.rightBar.width() > 0)
            {
                paintRect = QRect(pixmap.width() - subBGs.rightBar.width() - subBGs.rightBorder.width(),
                                  subBGs.topRightCorner.height(),
                                  subBGs.rightBar.width(),
                                  pixmap.height() - subBGs.topRightCorner.height() - subBGs.bottomRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.rightBar);
            }
            if(!subBGs.bottomLeftCorner.isNull())
            {
                paintRect = QRect(0,
                                  pixmap.height() - subBGs.bottomLeftCorner.height(),
                                  subBGs.bottomLeftCorner.width(),
                                  subBGs.bottomLeftCorner.height());
                painter.drawPixmap(paintRect, subBGs.bottomLeftCorner);
            }
            if(!subBGs.bottomBorder.isNull())
            {
                paintRect = QRect(subBGs.bottomLeftCorner.width(),
                                  pixmap.height() - subBGs.bottomBorder.height(),
                                  pixmap.width() - subBGs.bottomLeftCorner.width() - subBGs.bottomRightCorner.width(),
                                  subBGs.bottomBorder.height());
                painter.drawPixmap(paintRect, subBGs.bottomBorder);
            }
            if(!subBGs.bottomRightCorner.isNull())
            {
                paintRect = QRect(pixmap.width() - subBGs.bottomRightCorner.width(),
                                  pixmap.height() - subBGs.bottomRightCorner.height(),
                                  subBGs.bottomRightCorner.width(),
                                  subBGs.bottomRightCorner.height());
                painter.drawPixmap(paintRect, subBGs.bottomRightCorner);
            }
            if(subBGs.bottomBar.height() > 0)
            {
                paintRect = QRect(subBGs.leftBorder.width() + subBGs.leftBar.width(),
                                  pixmap.height() - subBGs.bottomBar.height() - subBGs.bottomBorder.height(),
                                  pixmap.width() - subBGs.leftBorder.width() - subBGs.leftBar.width() - subBGs.rightBorder.width() - subBGs.rightBar.width(),
                                  subBGs.bottomBar.height());
                painter.drawPixmap(paintRect, subBGs.bottomBar);

            }
            paintRect = QRect(subBGs.leftBar.width()+subBGs.leftBorder.width(),
                              subBGs.topBar.height() + subBGs.topBorder.height(),
                              pixmap.width()-subBGs.leftBar.width()-subBGs.leftBorder.width()-subBGs.rightBar.width()-subBGs.rightBorder.width(),
                              pixmap.height() -subBGs.topBar.height()- subBGs.topBorder.height() - subBGs.bottomBar.height() - subBGs.bottomBorder.height());
            painter.drawPixmap(paintRect, subBGs.central);
            //painter.end();
            return pixmap;
        }
    }

}

QPixmap SkinManager::getWidgetBG(ISkinWidget *widget)
{
    QString objectName = widget->instance()->objectName();
    if(!m_widgetSubBGs.contains(objectName))
    {
        m_widgetSubBGs[objectName] = generateWidgetSubBGs(widget);
    }
    if(widget->isMaximized())
    {
        if(!m_widgetMaximizeBGs.contains(objectName))
            m_widgetMaximizeBGs[objectName] = generateWidgetBG(widget);
        return m_widgetMaximizeBGs[objectName];
    }
    else
    {
        if(m_widgetRecommendedBGs.contains(objectName))
        {
            if(m_widgetRecommendedBGs[objectName].size() == widget->instance()->size())
                return m_widgetRecommendedBGs[objectName];
            QMap<ISkinWidget*, QPixmap> bgs = m_widgetBGs[objectName];
            if(bgs.contains(widget) && bgs[widget].size() == widget->instance()->size())
                return bgs[widget];
            QPixmap pixmap = generateWidgetBG(widget);
            bgs[widget] = pixmap;
            return pixmap;
        }
        else
        {
            QPixmap pixmap = generateWidgetBG(widget);
            m_widgetRecommendedBGs[objectName] = pixmap;
            return pixmap;
        }

    }
}

SkinWidgetSubBGs SkinManager::generateWidgetSubBGs(ISkinWidget* skinWidget)
{
    SkinWidgetData data = skinWidget->skinData();
    SkinWidgetSubBGs subBGs;
    SkinWidgetBGSizes sizes = data.bgSizes;
    QPixmap sourceBG = data.pixmapSourceBG;
    Q_ASSERT(sizes.radius >= sizes.border);
    if(data.bTopBottomFirst)
    {
        if(sizes.border > 0)
        {
            subBGs.leftBorder = sourceBG.copy(0, sizes.radius,
                                              sizes.border,
                                              sourceBG.height() - sizes.radius*2);
//            subBGs.leftBorder = sourceBG.copy(0, sizes.radius,
//                                              sizes.radius,
//                                              sourceBG.height() - sizes.radius*2);
            subBGs.rightBorder = sourceBG.copy(sourceBG.width()-sizes.border, sizes.radius,
                                               sizes.border,
                                               sourceBG.height() - sizes.radius*2);
//            subBGs.rightBorder = sourceBG.copy(sourceBG.width()-sizes.radius, sizes.radius,
//                                               sizes.radius,
//                                               sourceBG.height() - sizes.radius*2);
        }
        if(sizes.radius > 0)
        {
            subBGs.topBorder = sourceBG.copy(sizes.radius, 0, sourceBG.width()-sizes.radius*2,
                                             sizes.radius);
//            subBGs.topBorder = sourceBG.copy(sizes.radius, 0, sourceBG.width()-sizes.radius*2,
//                                             sizes.border);
            subBGs.topLeftCorner = sourceBG.copy(0, 0, sizes.radius,
                                                 sizes.radius);
            subBGs.topRightCorner = sourceBG.copy(sourceBG.width()-sizes.radius, 0,
                                                  sizes.radius,
                                                  sizes.radius);
            subBGs.bottomLeftCorner = sourceBG.copy(0, sourceBG.height()-sizes.radius,
                                                    sizes.radius,
                                                    sizes.radius);
            subBGs.bottomRightCorner = sourceBG.copy(sourceBG.width()-sizes.radius, sourceBG.height()-sizes.radius,
                                                     sizes.radius,
                                                     sizes.radius);
            subBGs.bottomBorder = sourceBG.copy(sizes.radius, sourceBG.height()-sizes.radius,
                                                sourceBG.width()-sizes.radius*2,
                                                sizes.radius);
//            subBGs.bottomBorder = sourceBG.copy(sizes.radius, sourceBG.height()-sizes.border,
//                                                sourceBG.width()-sizes.radius*2,
//                                                sizes.border);
        }
        if(sizes.topBarHeight > 0)
        {
            subBGs.topBar = sourceBG.copy(sizes.border, sizes.radius,
                                          sourceBG.width()-sizes.border*2, sizes.topBarHeight);
//            subBGs.topBar = sourceBG.copy(sizes.radius, sizes.border,
//                                          sourceBG.width()-sizes.radius*2, sizes.topBarHeight);
        }
        if(sizes.rightBarWidth > 0)
        {
            subBGs.rightBar = sourceBG.copy(sourceBG.width() - sizes.border - sizes.rightBarWidth,
                                            sizes.topBarHeight + sizes.radius,
                                            sizes.rightBarWidth,
                                            sourceBG.height() - sizes.radius*2 - sizes.topBarHeight - sizes.bottomBarHeight);
//            subBGs.rightBar = sourceBG.copy(sourceBG.width() - sizes.radius - sizes.rightBarWidth,
//                                            sizes.topBarHeight + sizes.border,
//                                            sizes.rightBarWidth,
//                                            sourceBG.height() - sizes.border*2 - sizes.topBarHeight - sizes.bottomBarHeight);
        }
        if(sizes.bottomBarHeight > 0)
        {
            subBGs.bottomBar = sourceBG.copy(sizes.border, sourceBG.height() - sizes.radius - sizes.bottomBarHeight,
                                             sourceBG.width()-sizes.border*2,
                                             sizes.bottomBarHeight);
//            subBGs.bottomBar = sourceBG.copy(sizes.radius, sourceBG.height() - sizes.border - sizes.bottomBarHeight,
//                                             sourceBG.width()-sizes.radius*2,
//                                             sizes.bottomBarHeight);
        }
        if(sizes.leftBarWidth > 0)
        {
            subBGs.leftBar = sourceBG.copy(sizes.border, sizes.topBarHeight + sizes.radius,
                                           sizes.leftBarWidth,
                                           sourceBG.height() - sizes.radius*2 - sizes.topBarHeight - sizes.bottomBarHeight);
//            subBGs.leftBar = sourceBG.copy(sizes.radius, sizes.topBarHeight + sizes.border,
//                                           sizes.leftBarWidth,
//                                           sourceBG.height() - sizes.border*2 - sizes.topBarHeight - sizes.bottomBarHeight);
        }
        subBGs.central = sourceBG.copy(sizes.border+sizes.leftBarWidth,
                                       sizes.radius+sizes.topBarHeight,
                                       sourceBG.width() - sizes.border*2 - sizes.leftBarWidth - sizes.rightBarWidth,
                                       sourceBG.height() - sizes.radius*2 - sizes.topBarHeight - sizes.bottomBarHeight);
//        subBGs.central = sourceBG.copy(sizes.radius+sizes.leftBarWidth,
//                                       sizes.border+sizes.topBarHeight,
//                                       sourceBG.width() - sizes.radius*2 - sizes.leftBarWidth - sizes.rightBarWidth,
//                                       sourceBG.height() - sizes.border*2 - sizes.topBarHeight - sizes.bottomBarHeight);
    }
    else
    {
        if(sizes.border > 0)
        {
            subBGs.leftBorder = sourceBG.copy(0, sizes.radius,
                                              sizes.border,
                                              sourceBG.height() - sizes.radius*2);
            subBGs.rightBorder = sourceBG.copy(sourceBG.width()-sizes.border, sizes.radius,
                                               sizes.border,
                                               sourceBG.height() - sizes.radius*2);
        }
        if(sizes.radius > 0)
        {
            subBGs.topBorder = sourceBG.copy(sizes.radius, 0, sourceBG.width()-sizes.radius*2,
                                             sizes.radius);
            subBGs.topLeftCorner = sourceBG.copy(0, 0, sizes.radius,
                                                 sizes.radius);
            subBGs.topRightCorner = sourceBG.copy(sourceBG.width()-sizes.radius, 0,
                                                  sizes.radius,
                                                  sizes.radius);
            subBGs.bottomLeftCorner = sourceBG.copy(0, sourceBG.height()-sizes.radius,
                                                    sizes.radius,
                                                    sizes.radius);
            subBGs.bottomRightCorner = sourceBG.copy(sourceBG.width()-sizes.radius, sourceBG.height()-sizes.radius,
                                                     sizes.radius,
                                                     sizes.radius);
            subBGs.bottomBorder = sourceBG.copy(sizes.radius, sourceBG.height()-sizes.radius,
                                                sourceBG.width()-sizes.radius*2,
                                                sizes.radius);
        }
        if(sizes.topBarHeight > 0)
        {
            subBGs.topBar = sourceBG.copy(sizes.border + sizes.leftBarWidth, sizes.radius,
                                          sourceBG.width()-sizes.border*2 - sizes.leftBarWidth - sizes.rightBarWidth,
                                          sizes.topBarHeight);
        }
        if(sizes.rightBarWidth > 0)
        {
            subBGs.rightBar = sourceBG.copy(sourceBG.width() - sizes.border - sizes.rightBarWidth,
                                            sizes.radius,
                                            sizes.rightBarWidth,
                                            sourceBG.height() - sizes.radius*2);
        }
        if(sizes.bottomBarHeight > 0)
        {
            subBGs.bottomBar = sourceBG.copy(sizes.border + sizes.leftBarWidth, sourceBG.height() - sizes.radius - sizes.bottomBarHeight,
                                             sourceBG.width()-sizes.border*2 - sizes.leftBarWidth - sizes.rightBarWidth,
                                             sizes.bottomBarHeight);
        }
        if(sizes.leftBarWidth > 0)
        {
            subBGs.leftBar = sourceBG.copy(sizes.border,  sizes.radius,
                                           sizes.leftBarWidth,
                                           sourceBG.height() - sizes.radius*2);
        }
        subBGs.central = sourceBG.copy(sizes.border+sizes.leftBarWidth,
                                       sizes.radius+sizes.topBarHeight,
                                       sourceBG.width() - sizes.border*2 - sizes.leftBarWidth - sizes.rightBarWidth,
                                       sourceBG.height() - sizes.radius*2 - sizes.topBarHeight - sizes.bottomBarHeight);
    }

    return subBGs;
}

void SkinManager::onWidgetDestroyed()
{
    ISkinWidget* widget = qobject_cast<ISkinWidget *> (sender());
    if(widget)
    {
        QString objName = widget->instance()->objectName();
        QMap<ISkinWidget*, QPixmap>& bgs = m_widgetBGs[objName];
        bgs.remove(widget);
        if(bgs.size() == 0)
        {
            m_widgetBGs.remove(objName);
        }
        m_framelessHelper->removeFrom(widget->instance());
        widget->instance()->removeEventFilter(this);
    }
}

void SkinManager::registSkinWidget(ISkinWidget *widget)
{
    m_framelessHelper->activateOn(widget->instance());
    m_framelessHelper->setWidgetMovable(widget->instance(), true);
    m_framelessHelper->setWidgetResizable(widget->instance(), widget->isResizable());
    m_framelessHelper->setBorderWidth(widget->instance(), widget->resizeBorderWidth());
    if(widget->isMaximized())
    {
        m_framelessHelper->setWidgetMovable(widget->instance(), false);
        m_framelessHelper->setWidgetResizable(widget->instance(), false);
    }
    else
    {
        QMargins margins = widget->instance()->layout()->contentsMargins();
        margins.setLeft(margins.left() + widget->resizeBorderWidth());
        margins.setTop(margins.top() + widget->resizeBorderWidth());
        margins.setRight(margins.right() + widget->resizeBorderWidth());
        margins.setBottom(margins.bottom() + widget->resizeBorderWidth());
        widget->instance()->layout()->setContentsMargins(margins);
        m_framelessHelper->setWidgetMovable(widget->instance(), true);
        m_framelessHelper->setWidgetResizable(widget->instance(), widget->isResizable());
    }
    widget->instance()->installEventFilter(this);
    connect(widget->instance(), SIGNAL(widgetDestroyed()), this, SLOT(onWidgetDestroyed()));
    connect(widget->instance(), SIGNAL(maximizeButtonClicked()), this, SLOT(onWidgetMaximizeButtonClicked()));
    connect(widget->instance(), SIGNAL(minimizeButtonClicked()), this, SLOT(onWidgetMinimizeButtonClicked()));

    QString objectName = widget->instance()->objectName();
    m_widgetBGs.remove(objectName);
    m_widgetSubBGs.remove(objectName);
    m_widgetRecommendedBGs.remove(objectName);
    m_widgetMaximizeBGs.remove(objectName);
}

void SkinManager::setWidgetResizable(ISkinWidget *widget)
{
    m_framelessHelper->setWidgetResizable(widget->instance(), false);
}

void SkinManager::showWidgetMaximize(ISkinWidget *widget)
{
    QMargins margins = widget->instance()->layout()->contentsMargins();
    margins.setLeft(margins.left() - widget->resizeBorderWidth());
    margins.setTop(margins.top() - widget->resizeBorderWidth());
    margins.setRight(margins.right() - widget->resizeBorderWidth());
    margins.setBottom(margins.bottom() - widget->resizeBorderWidth());
    widget->instance()->layout()->setContentsMargins(margins);
    widget->setRestoreRect(widget->instance()->frameGeometry());
    QRect rc =  QApplication::desktop()->availableGeometry();
    widget->instance()->move(rc.topLeft());
    widget->instance()->resize(rc.size());

    widget->setMaximized(true);
    m_framelessHelper->setWidgetMovable(widget->instance(), false);
    m_framelessHelper->setWidgetResizable(widget->instance(), false);
}

void SkinManager::showWidgetNormal(ISkinWidget *widget)
{
    QMargins margins = widget->instance()->layout()->contentsMargins();
    margins.setLeft(margins.left() + widget->resizeBorderWidth());
    margins.setTop(margins.top() + widget->resizeBorderWidth());
    margins.setRight(margins.right() + widget->resizeBorderWidth());
    margins.setBottom(margins.bottom() + widget->resizeBorderWidth());
    widget->instance()->layout()->setContentsMargins(margins);
    QRect rc = widget->restoreRect();
    widget->instance()->move(rc.topLeft());
    widget->instance()->resize(rc.size());
    //    qDebug() << rc.size();
    //    qDebug() << widget->instance()->size();

    widget->setMaximized(false);
    m_framelessHelper->setWidgetMovable(widget->instance(), true);
    m_framelessHelper->setWidgetResizable(widget->instance(), widget->isResizable());

}

void SkinManager::onWidgetMaximizeButtonClicked()
{
    ISkinWidget* widget = qobject_cast<ISkinWidget *> (sender());
    if(widget)
    {
        if(widget->isMaximized())
        {
            showWidgetNormal(widget);
        }
        else
        {
            showWidgetMaximize(widget);
        }
    }
}

void SkinManager::onWidgetMinimizeButtonClicked()
{
    ISkinWidget* widget = qobject_cast<ISkinWidget *> (sender());
    if(widget)
    {
        WidgetManager::minimiseWindow(widget->instance());
    }
}

bool SkinManager::eventFilter( QObject *obj, QEvent *event )
{
    if(event->type() == QEvent::Paint)
    {
        ISkinWidget* widget = qobject_cast<ISkinWidget*>(obj);
        if(widget)
        {
            paintWidget(widget);
            return true;
        }
    }
    if(event->type() == QEvent::Show)
    {
        QApplication::postEvent(obj, new QEvent(QEvent::UpdateRequest), Qt::LowEventPriority);
    }
    return false;
}

void SkinManager::paintWidget(ISkinWidget *widget)
{
    QPainter painter(widget->instance());
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(widget->instance()->rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);
    painter.fillRect(widget->instance()->rect(), Qt::transparent);
//    painter.setCompositionMode(QPainter::CompositionMode_Clear);
//    painter.eraseRect(widget->instance()->rect());
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    painter.drawPixmap(widget->instance()->rect(), getWidgetBG(widget));
}
