#include "bubble.h"
#include <QPainter>
#include <QFontMetrics>

QPixmap Bubble::bubble(const QString &text, const QColor &bgClr, const QColor &borderClr,
                       const QColor &textClr, int radius, int borderWidth, int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    QFontMetrics fontMetrics(font);
    int hMargin = (radius * 2 - fontMetrics.width("G"))/2.0;
    int vMargin = (radius * 2 - fontMetrics.height())/2.0;
    int textWidth = fontMetrics.width(text);
    if(textWidth < fontMetrics.width("G"))
    {
        hMargin = (radius * 2 - textWidth) / 2.0;
    }
    int textHeight = fontMetrics.height();
    QRect rect(0, 0, textWidth + (radius-hMargin)*2, textHeight + vMargin*2);
    if(rect.width() < 2*radius)
    {
        rect.setWidth(2*radius);
    }
    if(rect.height() < 2*radius)
    {
        rect.setHeight(2*radius);
    }
    QPixmap pixmapResult(rect.size());
    pixmapResult.fill(Qt::transparent);
    QPainter painter(&pixmapResult);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform|QPainter::HighQualityAntialiasing);
    QPen pen(borderClr);
    pen.setWidth(borderWidth);
    painter.setPen(pen);
    QBrush brush(bgClr);
    painter.setBrush(brush);
    painter.drawRoundedRect(rect, radius, radius);
    painter.setFont(font);
    pen.setColor(textClr);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(Qt::transparent);
    painter.drawText(rect, Qt::AlignCenter|Qt::TextSingleLine, text);
    painter.end();
    return pixmapResult;
}
