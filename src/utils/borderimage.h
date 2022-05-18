#ifndef BORDERIMAGE_H
#define BORDERIMAGE_H

#include <QPixmap>
#include "utilsexport.h"

class UTILS_EXPORT BorderImage
{
public:
    BorderImage();

    static QImage borderImage(const QImage& imageOriginal, const QImage& imageBorder, const QSize ASize,
                                const int borderwidth, const int radius);
    static QImage circleBorderImage(const QImage& imageOriginal, const QImage& imageBorder, const QSize ASize,
                                    const int borderwidth);
    static QImage circleBorderImage(const QImage &pixmapOriginal, const QColor &borderColor,
                                      const QSize ASize, const int borderwidth, const QColor &lightColor = QColor());
};

#endif // BORDERIMAGE_H
