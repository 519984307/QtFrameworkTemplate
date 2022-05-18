#include "CResourceItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QMovie>


////////////////////////////////////////////////////////////////////////////////////
CResourceItem::CResourceItem(QPixmap* pixmap, const QSize sz)
{
	m_scaleValue = 1;
	m_isMove = false;
	m_sz = sz;

	LoadItem( pixmap,sz,"" );
	m_Rotation = 1;

	//初始化为普通图片 
	cur_mode = CustomMode;
	movie = NULL;
	m_path = "";
}

CResourceItem::~CResourceItem()
{
	if (movie)
	{
		delete movie;
		movie = NULL;
	}
}

void CResourceItem::ResetPos()
{
	setPos(0, 0);
}

float CResourceItem::calcScale( const QSize rect )
{
	//rect是画布view大小

	m_scaleValue = 1;

	/*if (m_pix.isQBitmap())
	{*/
		//图片大小
		int iWidth = m_pix.width();
		int iHeight = m_pix.height();

		float imageScale = (float)iWidth / (float)iHeight;

		if (rect.width() > iWidth && rect.height() > iHeight)
		{
			//长宽都比画布小,那就用原始大小
			m_scaleValue = 1;
		}
		else
		{
			if (imageScale < 0.4)
			{
				//细长图并且图片高大于画布高做适配
				if (iHeight > rect.height())
				{
					//图片高是画布高的几倍
					float rate = (float)iHeight / (float)rect.height();

					//高几倍就缩小几倍
					m_scaleValue = 1 / rate;
					return m_scaleValue;
				}
				return 1;
			}
			else
			{
				//rect是画布view大小
				float fStageWidth = (float)rect.width();
				float fStageHeight = (float)rect.height();
				float stageScale = fStageWidth / fStageHeight;
				int leftHight = 0, leftWidth = 0;
				if (imageScale > stageScale)
				{
					leftHight = fStageHeight - (int)(fStageWidth / imageScale);
				}
				else
				{
					leftWidth = fStageWidth - (int)(fStageHeight * imageScale);
				}

				if (leftHight > 0)	// 宽图( 高 < 宽 )
				{
					m_scaleValue = (float)fStageWidth / (float)m_pix.width();
				}
				else if (leftWidth > 0)
				{
					m_scaleValue = (float)fStageHeight / (float)m_pix.height();
				}
			}
		}
	//}
	
	return m_scaleValue;
}


void CResourceItem::SetMode(FileMode mode)
{
	this->cur_mode = mode;

	switch (cur_mode)
	{
	case GifMode:
		if (movie)
		{
			delete movie;
			movie = NULL;
		}
		movie = new QMovie(m_path);
		movie->setSpeed(121);
		movie->start();
		break;

	case PPTXMode:
		if (movie)
		{
			delete movie;
			movie = NULL;
		}
		break;

	case PSDMode:
		if (movie)
		{
			delete movie;
			movie = NULL;
		}
		break;

	case CustomMode:
		if (movie)
		{
			delete movie;
			movie = NULL;
		}
		break;
	case AudioMode:
		if (movie)
		{
			delete movie;
			movie = NULL;
		}
		break;
	case VideoMode:
		break;
	default:
		break;
	}
}

void CResourceItem::drawCirclePixMap(QPainter *painter)
{
	if (!m_pix.isNull())
	{
		if (nRotateCoverWidth == m_pix.width() && nRotateCoverWidth == m_pix.height())
		{
			QRect paintRect = QRect(-nRotateCoverWidth / 2, -nRotateCoverWidth / 2, nRotateCoverWidth, nRotateCoverWidth);
			QPainterPath path;
			path.addRoundedRect(paintRect, nRotateCoverWidth / 2, nRotateCoverWidth / 2);

			painter->setRenderHint(QPainter::Antialiasing, true);
			QRadialGradient radiaGradient(QPointF(0, 0), nRotateCoverWidth / 2 + 6);
			radiaGradient.setColorAt(0.95, QColor(224, 231, 250, 75));
			radiaGradient.setColorAt(1.0, QColor(224, 231, 250, 0));
			painter->setPen(QColor(224, 231, 250, 0));
			painter->setBrush(QBrush(radiaGradient));
			painter->drawEllipse(paintRect.adjusted(-6, -6, 6, 6));

			painter->setClipPath(path);
			painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		}
	}
}

void CResourceItem::setPixMirrored()
{
  m_bMirrored = !m_bMirrored;

  QImage img = m_pix.toImage().mirrored(true, false);
  m_pix = QPixmap::fromImage(img);

  update();
}

bool CResourceItem::isMirroredOrRotated()
{
  if (m_bRotated || m_bMirrored)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void CResourceItem::resetValues()
{
  m_bRotated = false;
  m_bMirrored = false;
  m_nRotatedAngle = 0;
}

bool CResourceItem::saveTransFormedImg()
{
  bool bResult = false;
  if (m_bRotated)
  {
    QTransform transForm;
    m_pix = m_pix.transformed(transForm.rotate(m_nRotatedAngle));
  }
  if (m_pix.save(m_path))
  {
    bResult = true;
  }
  return bResult;
}

FileMode CResourceItem::getFileMode()
{
  return cur_mode;
}

qreal CResourceItem::getAnimationRotatedAngle()
{
	return m_AnimationRotated;
}

QSize CResourceItem::getPixOriginalSize()
{
    return m_pix.size();
}

void CResourceItem::Stop()
{
    if (movie)
    {
        delete movie;
        movie = NULL;
    }
}

float CResourceItem::LoadItem( QPixmap* pixmap, const QSize sz, QString local_path,float scale /*= 1*/ )
{
	float _scale_Value = 1.0;
	if (pixmap)
	{
		m_pix = *pixmap;
	}

	m_path = local_path;

	m_sz = sz;

	/*if (abs(scale - 1) < 0.0000001 || abs(scale - 0.1) < 0.0000001)
	{
		float _scale = calcScale(sz);
		setScale(_scale);
		_scale_Value = _scale;
	}
	else
	{
		m_scaleValue = scale;
		setScale(m_scaleValue);
		_scale_Value = m_scaleValue;
	}*/
	this->update();
	return _scale_Value;
}

void CResourceItem::ResetRotation()
{
	setRotation(0);

	m_AnimationRotated = 0;

    m_bRotated = false;
}

void CResourceItem::animationRotate(qreal realAngle)
{
	m_AnimationRotated += realAngle;
	setRotation(m_AnimationRotated);
}

float CResourceItem::reloadItem(QPixmap* pixmap, const QSize sz, QString local_path, float scale /* = 1 */)
{
	float _scale_Value = 1.0;
	if (pixmap)
	{
		m_pix = *pixmap;
	}

	m_path = local_path;

	m_sz = sz;

	if (qAbs(scale - 1) < 0.0000001 || qAbs(scale - 0.1) < 0.0000001)
	{
		float _scale = calcScale(sz);
		setScale(_scale);
		_scale_Value = _scale;
	}
	else
	{
		m_scaleValue = scale;
		setScale(m_scaleValue);
		_scale_Value = m_scaleValue;
	}
	this->update();
	return _scale_Value;
}

void CResourceItem::ScaleItem(float scale)
{
	m_scaleValue = scale;
	setScale(m_scaleValue);
}

void CResourceItem::RotateItem()
{
  m_nRotatedAngle = -90 * (m_Rotation % 4);
	//setRotation(-90 * (m_Rotation % 4));
  setRotation(m_nRotatedAngle);
	m_Rotation++;

  if (0 == abs(m_nRotatedAngle) % 360)
  {
    m_bRotated = false;
  }
  else
  {
    m_bRotated = true;
  }
}

void CResourceItem::rotateItemByAngle(int nAngle)
{
	m_nRotatedAngle += nAngle;
	setRotation(m_nRotatedAngle);
	if (0 == abs(m_nRotatedAngle) % 360)
	{
		m_bRotated = false;
	}
	else
	{
		m_bRotated = true;
	}
}

float CResourceItem::LoadItemReset()
{
	float _scale = calcScale(m_sz);
	setScale(_scale);

	return _scale;
}

QRectF CResourceItem::boundingRect() const
{
	return QRectF(-m_pix.width() / 2, -m_pix.height() / 2, m_pix.width(), m_pix.height());
}

void CResourceItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	
	switch (cur_mode)
	{
	case GifMode:
		//gif模式

		if (movie)
		{
			QPixmap m_pix = movie->currentPixmap();
			painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
			
			//gif需要加速刷新页面
			this->update();
		}

		break;
	case PPTXMode:
		//普通模式-用pix
		painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		break;
	case PSDMode:
		//普通模式-用pix
		painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		break;
	case CustomMode:
		//普通模式-用pix
		//painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		
		painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		
		break;
	case AudioMode:
		//painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
		drawCirclePixMap(painter);
		break;
	case VideoMode:
	{
		/*if (nullptr != m_pGraphicsProxyWidget)
		{
			m_pVideoPlayerWidget->update();
		}*/
	}
		break;
	default:
		break;
	}
}

void CResourceItem::wheelEvent(QGraphicsSceneWheelEvent* event)
{
	qreal qrealOriginScale = m_scaleValue;
	if (event->delta() > 0)//鼠标滚轮向前滚动
	{
		m_scaleValue *= 1.1;//每次放大10%
	}
	else
	{
		m_scaleValue *= 0.9;//每次缩小10%
	}
	setScale(m_scaleValue);
	
	if (event->delta() > 0)
	{
		moveBy(-event->pos().x()*qrealOriginScale*0.1, -event->pos().y()*qrealOriginScale*0.1);//使图片缩放的效果看起来像是以鼠标所在点为中心进行缩放的
	}
	else
	{
		moveBy(event->pos().x()*qrealOriginScale*0.1, event->pos().y()*qrealOriginScale*0.1);//使图片缩放的效果看起来像是以鼠标所在点为中心进行缩放的
	}
}
