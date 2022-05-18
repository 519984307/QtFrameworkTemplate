#ifndef _H_PIXMAPCONVERTER_H_
#define _H_PIXMAPCONVERTER_H_

#include <QPainter>
#include <QBitmap>



class ImgAlgorithm
{
public:
    static QImage imageGraytoImg(const QImage &img);     //图片灰化

    static QPixmap imageGraytoPixmap(const QImage& img); //图片灰化

    static QImage imageThumbnail_BK_Color(const QImage& img);    //缩略图波形图背景色()

    static QPixmap imageThumbnail_BK_ToPixmap(const QImage& img);

    static QImage imageLarge_BK_Color(const QImage& img);        //大图预览波形图背景色

    static QPixmap imageLarge_BK_ToPixmap(const QImage& img);

    static QImage createDefaultImg(int nWidth, int nHeight, const QColor& bkColor, const QColor& textColor, const QString& strText, int nFontWidth, int nFontSize);   //生成默认图片(文本居中)
};


QPixmap PixmapToRound(QPixmap& src, int radius);



#endif


