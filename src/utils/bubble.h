#ifndef BUBBLE_H
#define BUBBLE_H

#include <QtGlobal>
#include <QColor>
#include <QPixmap>
#include "utilsexport.h"

class UTILS_EXPORT Bubble
{
public:
    static QPixmap bubble(const QString &text, const QColor& bgClr = Qt::red, const QColor& borderClr = Qt::white,
                          const QColor& textClr = Qt::white, int radius = 8, int borderWidth = 2, int fontSize = 10);
};

#endif // BUBBLE_H
