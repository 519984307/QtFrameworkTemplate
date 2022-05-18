#include <QPainter>
#include <QBitmap>
#include <QPainterPath>
#include "PixmapConverter.h"

QPixmap PixmapToRound(QPixmap& src, int radius)
{
    QPixmap pixmap(2 * radius, 2 * radius);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 2 * radius, 2 * radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 2 * radius, 2 * radius, src);
    return pixmap;
}



QImage ImgAlgorithm::imageGraytoImg(const QImage &img)
{
    int w = img.width();
    int h = img.height();
    QImage copyedImg = img.copy(0, 0, w, h);
    //遍历图像的每一个像素
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            //获取像素的 RGBA 颜色分量
            QRgb color = copyedImg.pixel(x, y);
            int r = qRed(color);
            int g = qGreen(color);
            int b = qBlue(color);
            int a = qAlpha(color);


            //计算灰色的颜色: 3 个颜色分量的平均值
            int rr = (r + g + b) / 3;
            int rg = rr;
            int rb = rr;
            color = qRgba(rr, rg, rb, a);

            //设置图像的像素
            copyedImg.setPixel(x, y, color);
        }
    }
    return copyedImg;
}

QPixmap ImgAlgorithm::imageGraytoPixmap(const QImage& img)
{
    QImage grayImg = imageGraytoImg(img);
    return QPixmap::fromImage(grayImg);
}

QImage ImgAlgorithm::imageThumbnail_BK_Color(const QImage& img)
{
    int w = img.width();
    int h = img.height();
    QImage copyedImg = img.copy(0, 0, w, h);
    //遍历图像的每一个像素
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            QColor color = copyedImg.pixelColor(x, y);
            if (0 != color.alpha())
            {
                color.setRed(224);
                color.setGreen(231);
                color.setBlue(250);
                color.setAlpha(255);
                copyedImg.setPixelColor(x, y, color);
            }
        }
    }
    return copyedImg;
}

QPixmap ImgAlgorithm::imageThumbnail_BK_ToPixmap(const QImage& img)
{
    QImage resultImg = imageThumbnail_BK_Color(img);
    return QPixmap::fromImage(resultImg);
}

QImage ImgAlgorithm::imageLarge_BK_Color(const QImage& img)
{
    int w = img.width();
    int h = img.height();
    QImage copyedImg = img.copy(0, 0, w, h);
    //遍历图像的每一个像素
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            QColor color = copyedImg.pixelColor(x, y);
            if (0 != color.alpha())
            {
                color.setRed(162);
                color.setGreen(171);
                color.setBlue(195);
                color.setAlpha(255);
                copyedImg.setPixelColor(x, y, color);
            }
        }
    }
    return copyedImg;
}

QPixmap ImgAlgorithm::imageLarge_BK_ToPixmap(const QImage& img)
{
    QImage resultImg = imageLarge_BK_Color(img);
    return QPixmap::fromImage(resultImg);
}

QImage ImgAlgorithm::createDefaultImg(int nWidth, int nHeight, const QColor& bkColor, const QColor& textColor, const QString& strText, int nFontWidth, int nFontSize)
{
    QImage defaultImage(nWidth, nHeight, QImage::Format_ARGB32);
    QPainter ImagePainter(&defaultImage);
    ImagePainter.setBrush(bkColor);
    ImagePainter.drawRect(defaultImage.rect());

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPixelSize(nFontSize);
    font.setBold(true);

    QFontMetrics fms(font);
    int fontHeight = fms.height() + 10;

    //计算文字位置，设置字体并绘制。
    QPoint textTopLeftPoint((defaultImage.width() - nFontWidth) / 2, (defaultImage.height() - fontHeight) / 2);
    QRect fontRect(textTopLeftPoint, QSize(nFontWidth, fontHeight));
    ImagePainter.setFont(font);
    ImagePainter.setPen(textColor);
    ImagePainter.drawText(fontRect, Qt::AlignCenter, strText);

    return defaultImage;
}
