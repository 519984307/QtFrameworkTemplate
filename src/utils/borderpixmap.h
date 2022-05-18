#ifndef BORDERPIXMAP_H
#define BORDERPIXMAP_H

#include <QPixmap>
#include "utilsexport.h"

class UTILS_EXPORT BorderPixmap
{
public:
    BorderPixmap();

    static QPixmap borderPixmap(const QPixmap& pixmapOriginal, const QPixmap& pixmapBorder, const QSize pixmapSize,
                                const int borderwidth, const int radius);
    static QPixmap circleBorderPixmap(const QPixmap& pixmapOriginal, const QPixmap& pixmapBorder, const QSize ASize,
                                     const int borderwidth);
    static QPixmap circleBorderPixmap(const QPixmap &pixmapOriginal, const QColor &borderColor,
                                      const QSize ASize, const int borderwidth, const QColor &lightColor = QColor());
    static QPixmap circlePixmap(const QPixmap &pixmap, const QSize &size);
};

#endif // BORDERPIXMAP_H
