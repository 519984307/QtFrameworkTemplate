#ifndef CIRCLEAVATARLABEL_H
#define CIRCLEAVATARLABEL_H

#include "clickablelabel.h"
#include "utilsexport.h"

class UTILS_EXPORT CircleAvatarLabel : public ClickableLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor normalBorderColor READ normalBorderColor WRITE setNormalBorderColor)
    Q_PROPERTY(QColor hoverBorderColor READ hoverBorderColor WRITE setHoverBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)

public:
    explicit CircleAvatarLabel(QWidget *parent = 0);

    void setNormalBorderColor(const QColor& clr);
    QColor normalBorderColor() {return m_borderNormalColor;}
    void setHoverBorderColor(const QColor& clr);
    QColor hoverBorderColor() {return m_borderHoverColor;}

    void setBorderWidth(const int width);
    int borderWidth(){return m_borderWidth;}

    void setNormalHoverPixmap(const QPixmap &normal, const QPixmap &hover);

signals:

public slots:
    void setPixmap(const QPixmap &pix);

protected:
    void generatePixmaps();
    void paintEvent(QPaintEvent *ev);

private:
    QPixmap m_pixmapNormal;
    QPixmap m_pixmapHover;
    int m_borderWidth;
    QColor m_borderNormalColor;
    QColor m_borderHoverColor;
    bool m_bDrawSelf;

};

#endif // CIRCLEAVATARLABEL_H
