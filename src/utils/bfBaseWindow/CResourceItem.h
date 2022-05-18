#ifndef CResourceItem_H
#define CResourceItem_H


#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

class QMovie;


const int nRotateCoverWidth = 360;

//[2020.10.27 Tom]
//不同的图片处理情况，目前是用枚举类型控制，之后各个类型操作实在不太一样，直接另写一个类。
enum FileMode
{
	GifMode,       //GIF图
	PPTXMode,      //PPTX格式
	PSDMode,       //PSD格式
	CustomMode,    //普通图 
	AudioMode,     //音频类型
	VideoMode,     //视频类型
	FontMode,
	ImportMode,		//支持导入的类型
};


class CResourceItem : public QGraphicsItem
{
public:
	CResourceItem(QPixmap* pixmap, const QSize sz);
	~CResourceItem();
	const QPixmap GetPixmap() { return m_pix; }

	float LoadItem(QPixmap* pixmap, const QSize sz,QString local_path,float scale = 1);
	float LoadItemReset();
	void ScaleItem(float scale);
	void RotateItem();

	void rotateItemByAngle(int nAngle);    //单次旋转多少度

	void ResetRotation();

	void animationRotate(qreal realAngle);    //音频播放动态效果

	float reloadItem(QPixmap* pixmap, const QSize sz, QString local_path, float scale = 1);   //设置(音频)封面后，重新加载

	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	void wheelEvent(QGraphicsSceneWheelEvent* event);

	/*void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);*/

	void ResetPos();

	float calcScale(const QSize sz);

	void SetMode(FileMode mode);

    void setPixMirrored();

    bool isMirroredOrRotated();

    void resetValues();

    bool saveTransFormedImg();     //保存旋转&翻转后的图片到磁盘

    FileMode getFileMode();        //获取素材类型

	qreal getAnimationRotatedAngle();

	QSize getPixOriginalSize();

    void Stop();

private:
	void drawCirclePixMap(QPainter *painter);

private:
	QPointF     m_pos;
	QPointF     m_pressedPos;
	QPointF     m_startPos;

	qreal       m_scaleValue;
	qreal		m_defaultScaleValue;
	QPixmap     m_pix;

	int         m_zoomState;
	bool        m_isMove;
	QSize		m_sz;

    int			m_Rotation;

    int m_nRotatedAngle = 0;   //已旋转角度

	QString     m_path;                 //目前主要用于保存gif原图路径

	FileMode    cur_mode;              //模式选择
	QMovie *    movie;                 //gif模式下的gif操作类

	qreal m_AnimationRotated = 0;

    bool m_bMirrored = false;          //水平翻转&镜像

    bool m_bRotated = false;
};

#endif
