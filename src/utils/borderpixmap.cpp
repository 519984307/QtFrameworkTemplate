#include "borderpixmap.h"
#include <QPainter>
#include <QPainterPath>
#include "tools.h"
#include "colors.h"

BorderPixmap::BorderPixmap()
{
}

QPixmap BorderPixmap::borderPixmap(const QPixmap &pixmapOriginal, const QPixmap &pixmapBorder, const QSize pixmapSize, const int borderwidth, const int radius)
{
    if(pixmapOriginal.isNull() || pixmapBorder.isNull() || (borderwidth == 0 && radius == 0.0))
        return pixmapOriginal;
    QPixmap pixmapResult(pixmapSize);
    pixmapResult.fill(Qt::transparent);
    QPainter painter(&pixmapResult);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    double cornerWidth = borderwidth + radius;
    QPixmap pixmapTemp = pixmapBorder.copy(QRect(0,0,
                                                 cornerWidth,
                                                 cornerWidth));
    painter.drawPixmap(pixmapTemp.rect(), pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(cornerWidth,
                                         0,
                                         pixmapBorder.width()- cornerWidth * 2,
                                         borderwidth));
    painter.drawPixmap(QRect(cornerWidth,
                             0,
                             pixmapSize.width() - cornerWidth * 2,
                             pixmapTemp.height()), pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(pixmapBorder.width() - cornerWidth,
                                         0,
                                         cornerWidth,
                                         cornerWidth));
    painter.drawPixmap(QRect(pixmapSize.width() - pixmapTemp.width(),
                             0,
                             pixmapTemp.width(),
                             pixmapTemp.height()),
                       pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(0,
                                         cornerWidth,
                                         borderwidth,
                                         pixmapBorder.height() - cornerWidth * 2));
    painter.drawPixmap(QRect(0,
                             cornerWidth,
                             pixmapTemp.width(),
                             pixmapSize.height()- cornerWidth * 2),
                       pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(pixmapBorder.width() - borderwidth,
                                         cornerWidth ,
                                         borderwidth,
                                         pixmapBorder.height() - cornerWidth * 2));
    painter.drawPixmap(QRect(pixmapSize.width() - pixmapTemp.width(),
                             cornerWidth ,
                             pixmapTemp.width(),
                             pixmapSize.height()- cornerWidth * 2),
                       pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(0,
                                         pixmapBorder.height() - cornerWidth,
                                         cornerWidth,
                                         cornerWidth));
    painter.drawPixmap(QRect(0 ,
                             pixmapSize.height() - pixmapTemp.height(),
                             pixmapTemp.width(),
                             pixmapTemp.height()),
                       pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(cornerWidth ,
                                         pixmapBorder.height() - borderwidth,
                                         pixmapBorder.width() - cornerWidth*2,
                                         borderwidth));
    painter.drawPixmap(QRect(cornerWidth,
                             pixmapSize.height() - pixmapTemp.height(),
                             pixmapSize.width() - cornerWidth*2,
                             pixmapTemp.height()), pixmapTemp);
    pixmapTemp = pixmapBorder.copy(QRect(pixmapBorder.width() - cornerWidth,
                                         pixmapBorder.height() - cornerWidth,
                                         cornerWidth,
                                         cornerWidth));
    painter.drawPixmap(QRect(pixmapSize.width()-pixmapTemp.width(),
                             pixmapSize.height() - pixmapTemp.height(),
                             pixmapTemp.width(),
                             pixmapTemp.height()),
                       pixmapTemp);
    pixmapTemp = pixmapOriginal;
    if (!pixmapTemp.isNull())
    {
        QRect paintRect = QRect(borderwidth, borderwidth,
                                pixmapSize.width() - borderwidth - borderwidth,
                                pixmapSize.height() - borderwidth - borderwidth);
        pixmapTemp = pixmapTemp.scaled(paintRect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.setBrush(QBrush(pixmapTemp));
        painter.setBrushOrigin(paintRect.topLeft());
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(paintRect, radius, radius);
    }
    return pixmapResult;
}

QPixmap BorderPixmap::circleBorderPixmap(const QPixmap &pixmapOriginal, const QPixmap &pixmapBorder, const QSize ASize, const int borderwidth)
{
    QPixmap pixmap(ASize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::TextAntialiasing);
    QSize circlePixmapSize = ASize;
    circlePixmapSize.setWidth(circlePixmapSize.width() - (borderwidth) * 2);
    circlePixmapSize.setHeight(circlePixmapSize.height() - (borderwidth) * 2);
    QPixmap circlePixmapTemp = circlePixmap(pixmapOriginal, circlePixmapSize);
    painter.drawPixmap(QRect(QPoint(borderwidth, borderwidth), circlePixmapSize), circlePixmapTemp);
    painter.drawPixmap(QRect(QPoint(0,0), ASize), pixmapBorder.scaled(ASize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //painter.setPen(Colors::colorFromText("#d1d1d1"));
    //painter.drawEllipse(QRect(QPoint(0,0), ASize));
    return pixmap;

}

QPixmap BorderPixmap::circleBorderPixmap(const QPixmap &pixmapOriginal, const QColor &borderColor, const QSize ASize, const int borderwidth, const QColor &lightColor)
{
    QPixmap pixmap(ASize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::TextAntialiasing);
    QSize circlePixmapSize = ASize;
    circlePixmapSize.setWidth(circlePixmapSize.width() - (borderwidth-1) * 2);
    circlePixmapSize.setHeight(circlePixmapSize.height() - (borderwidth-1) * 2);
    QPixmap circlePixmapTemp = circlePixmap(pixmapOriginal, circlePixmapSize);

    painter.drawPixmap(QRect(QPoint(borderwidth-1, borderwidth-1), circlePixmapSize), circlePixmapTemp);

    if(!lightColor.isValid())
    {
        painter.setPen(borderColor);
        painter.drawEllipse(QRect(QPoint(borderwidth-1,borderwidth-1), QSize(ASize.width()-(borderwidth-1) * 2, ASize.width()-(borderwidth-1) * 2)));
    }
    else
    {
        if(borderwidth > 1 && lightColor.isValid())
        {
            QColor tempLightColor = lightColor;
            float alpha = 1.0/(borderwidth+4);
            for(int i=0; i<borderwidth; i++)
            {
                tempLightColor.setAlpha(255*alpha*(i+2));
                painter.setPen(tempLightColor);
                painter.drawEllipse(QRect(QPoint(i,i), QSize(ASize.width()-i * 2, ASize.width()-i * 2)));
            }
        }
    }
    //painter.drawPixmap(QRect(QPoint(0,0), ASize), pixmapBorder.scaled(ASize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    return pixmap;
}

QPixmap BorderPixmap::circlePixmap(const QPixmap &pixmap, const QSize &size)
{
    QPixmap pixmapCircle(size);
    pixmapCircle.fill(Qt::transparent);
    QPainter painter(&pixmapCircle);
    //painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    QPainterPath path;
    path.addEllipse(pixmapCircle.rect());
    QPixmap scaledPixmap = pixmap;
    if(scaledPixmap.size() != size)
    {
        scaledPixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    painter.fillPath(path, QBrush(scaledPixmap));
    //painter.end();
    return pixmapCircle;
}
