#include "borderimage.h"
#include <QPainter>
#include "borderpixmap.h"

BorderImage::BorderImage()
{
}

QImage BorderImage::borderImage(const QImage &imageOriginal, const QImage &imageBorder, const QSize ASize, const int borderwidth, const int radius)
{
    return BorderPixmap::borderPixmap(QPixmap::fromImage(imageOriginal), QPixmap::fromImage(imageBorder),
                                      ASize, borderwidth, radius).toImage();
}

QImage BorderImage::circleBorderImage(const QImage &imageOriginal, const QImage &imageBorder, const QSize ASize, const int borderwidth)
{
    return BorderPixmap::circleBorderPixmap(QPixmap::fromImage(imageOriginal), QPixmap::fromImage(imageBorder),
                                            ASize, borderwidth).toImage();
}

QImage BorderImage::circleBorderImage(const QImage &imageOriginal, const QColor &borderColor, const QSize ASize, const int borderwidth, const QColor &lightColor)
{
    return BorderPixmap::circleBorderPixmap(QPixmap::fromImage(imageOriginal), borderColor,
                                            ASize, borderwidth, lightColor).toImage();
}
