#include <QRubberBand>
#include <QMouseEvent>
#include <QMutex>
#include <QDebug>
#include "NcFramelessHelper.h"

#include <QWidget>
#include <QStyle>
#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QtGui>

#ifdef Q_OS_MAC
#import <Cocoa/Cocoa.h>
#import <AppKit/NSView.h>
#include <QMacNativeWidget>
#endif

class NcCursorPosCalculator
{

public:
    NcCursorPosCalculator();
    void reset();
    void recalculate( const QPoint& globalMousePos, const QRect& frameRect, const int borderWidth);

public:
    bool onEdges;
    bool onLeftEdge;
    bool onRightEdge;
    bool onTopEdge;
    bool onBottomEdge;
    bool onTopLeftEdge;
    bool onBottomLeftEdge;
    bool onTopRightEdge;
    bool onBottomRightEdge;
};
//TODO: Should not be static.

class NcWidgetData
{
public:
    NcWidgetData( NcFramelessHelperImpl* _d, QWidget* topLevelWidget );
    ~NcWidgetData();

    //void setWidget( QWidget* topLevelWidget );
    QWidget* widget();
    void handleWidgetEvent( QEvent* event );
    void setMovable(bool movable );
    bool isMovable(){return mMovable;}

    void setResizable(bool resizable ){mResizable = resizable;}
    bool isResizable(){return mResizable;}

    void setBorderWidth(int newBorderWidth ){mBorderWidth = newBorderWidth;}
    int borderWidth(){return mBorderWidth;}

private:
    void updateCursorShape( const QPoint& globalMousePos );
    void resizeWidget( const QPoint& globalMousePos );
    void moveWidget( const QPoint& globalMousePos );

    void handleMousePressEvent( QMouseEvent* event );
    void handleMouseReleaseEvent( QMouseEvent* event );
    void handleMouseMoveEvent( QMouseEvent* event );
    void handleLeaveEvent( QEvent* event );
    void handleHoverMoveEvent( QHoverEvent* event );

private:
    NcFramelessHelperImpl* d;
    bool mLeftButtonPressed;
    QWidget* mWidget;
    QPoint mDragPos;
    NcCursorPosCalculator mPressedMousePos;
    NcCursorPosCalculator mMoveMousePos;
    bool mCursorShapeChanged;
    Qt::WindowFlags mWindowFlags;
    bool mMovable;
    bool mResizable;
    int mBorderWidth;
};


class NcFramelessHelperImpl
{
public:
    QHash< QWidget*, NcWidgetData* > mHashWidgetData;
};

NcCursorPosCalculator::NcCursorPosCalculator()
{
    reset();
}

void NcCursorPosCalculator::reset()
{
    onEdges = false;
    onLeftEdge = false;
    onRightEdge = false;
    onTopEdge = false;
    onBottomEdge = false;
    onTopLeftEdge = false;
    onBottomLeftEdge = false;
    onTopRightEdge = false;
    onBottomRightEdge = false;
}

void NcCursorPosCalculator::recalculate( const QPoint& globalMousePos, const QRect& frameRect, const int borderWidth)
{
    int globalMouseX = globalMousePos.x();
    int globalMouseY = globalMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    onLeftEdge = globalMouseX >= frameX &&
            globalMouseX <= frameX + borderWidth;


    onRightEdge = globalMouseX >= frameX + frameWidth - borderWidth &&
            globalMouseX <= frameX + frameWidth;

    onTopEdge = globalMouseY >= frameY &&
            globalMouseY <= frameY + borderWidth;


    onBottomEdge = globalMouseY >= frameY + frameHeight - borderWidth &&
            globalMouseY <= frameY + frameHeight;

    onTopLeftEdge = onTopEdge && onLeftEdge;
    onBottomLeftEdge = onBottomEdge && onLeftEdge;
    onTopRightEdge = onTopEdge && onRightEdge;
    onBottomRightEdge = onBottomEdge && onRightEdge;

    //only these checks would be enough
    onEdges = onLeftEdge || onRightEdge ||
            onTopEdge || onBottomEdge;

}


NcWidgetData::NcWidgetData( NcFramelessHelperImpl* _d, QWidget* topLevelWidget )
{
    d = _d;
    mWidget = topLevelWidget;
    mLeftButtonPressed = false;
    mCursorShapeChanged = false;
    mMovable = true;
    mResizable = true;
    mBorderWidth = 5;

    mWindowFlags = mWidget->windowFlags();

    //---from Qt docs of setWindowFlags()----
    //Note: This function calls setParent() when
    //changing the flags for a window, causing the
    //widget to be hidden. You must call show()
    //to make the widget visible again..

    bool visible = mWidget->isVisible();

    mWidget->setMouseTracking( true );
    mWidget->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //Bug fix, mouse move events does not propagate from child widgets.
    //so need the hover events.
    mWidget->setAttribute( Qt::WA_Hover );
    mWidget->setWindowOpacity(1.0);
    mWidget->setAttribute(Qt::WA_NoSystemBackground);
    mWidget->setAttribute(Qt::WA_OpaquePaintEvent);
    mWidget->setAttribute(Qt::WA_TranslucentBackground);

#ifdef Q_OS_MAC
    // showMinimized() not working, see QTBUG-32184
    //window->hide();
    NSView *view = (NSView *)mWidget->winId();
    NSWindow *wnd = [view window];
    [wnd setOpaque:NO];
#endif

    mWidget->setVisible( visible );
}

NcWidgetData::~NcWidgetData()
{
    //---from Qt docs of setWindowFlags()----
    //Note: This function calls setParent() when
    //changing the flags for a window, causing the
    //widget to be hidden. You must call show()
    //to make the widget visible again..

    bool visible = mWidget->isVisible();

    mWidget->setMouseTracking( false );
    mWidget->setWindowFlags( mWindowFlags );//^  Qt::CustomizeWindowHint ^ Qt::FramelessWindowHint );
    mWidget->setAttribute( Qt::WA_Hover, false );

    mWidget->setVisible( visible );
}

void NcWidgetData::setMovable(bool movable )
{
    mMovable = movable;
}


QWidget* NcWidgetData::widget()
{
    return mWidget;
}

void NcWidgetData::handleWidgetEvent( QEvent* event )
{
    switch ( event->type() )
    {
    default: //qDebug() << "Event = " << event;
        break;
    case QEvent::MouseButtonPress:
        handleMousePressEvent( static_cast<QMouseEvent*>( event ) );
        break;

    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent( static_cast<QMouseEvent*>( event ) );
        break;

    case QEvent::MouseMove:
        handleMouseMoveEvent( static_cast<QMouseEvent*>( event ) );
        break;

    case QEvent::Leave:
        handleLeaveEvent( event );
        break;

        //Bug fix, hover event is necessary coz child widget does not
        //propagate mousemove events. so the cursor remains in edge shape
        //even in middle of widget.
    case QEvent::HoverMove:
        handleHoverMoveEvent( static_cast<QHoverEvent*>( event ) );
        break;
        //case QEvent::Enter:
        //qDebug() << "Enter event";//d->handleEnterEvent( event );
        //break;
    }
}

void NcWidgetData::updateCursorShape( const QPoint& globalMousePos )
{
    if ( mWidget->isFullScreen() || mWidget->isMaximized() )
    {
        if ( mCursorShapeChanged )
            mWidget->unsetCursor();

        return;
    }

    mMoveMousePos.recalculate( globalMousePos, mWidget->frameGeometry(), mBorderWidth);

    if( mMoveMousePos.onTopLeftEdge || mMoveMousePos.onBottomRightEdge )
    {
        mWidget->setCursor( Qt::SizeFDiagCursor );
        mCursorShapeChanged = true;
    }
    else if( mMoveMousePos.onTopRightEdge || mMoveMousePos.onBottomLeftEdge )
    {
        mWidget->setCursor( Qt::SizeBDiagCursor );
        mCursorShapeChanged = true;
    }
    else if( mMoveMousePos.onLeftEdge || mMoveMousePos.onRightEdge )
    {
        mWidget->setCursor( Qt::SizeHorCursor );
        mCursorShapeChanged = true;
    }
    else if( mMoveMousePos.onTopEdge || mMoveMousePos.onBottomEdge )
    {
        mWidget->setCursor( Qt::SizeVerCursor );
        mCursorShapeChanged = true;
    }
    else
    {
        if ( mCursorShapeChanged )
        {
            mWidget->unsetCursor();
            mCursorShapeChanged = false;
        }
    }
}

void NcWidgetData::resizeWidget( const QPoint& globalMousePos )
{
    QRect origRect;

    origRect = mWidget->frameGeometry();


    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords( &left, &top, &right, &bottom );

    int minWidth = mWidget->minimumWidth();
    int minHeight = mWidget->minimumHeight();

    if ( mPressedMousePos.onTopLeftEdge )
    {
        left = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if ( mPressedMousePos.onBottomLeftEdge )
    {
        left = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if ( mPressedMousePos.onTopRightEdge )
    {
        right = globalMousePos.x();
        top = globalMousePos.y();
    }
    else if ( mPressedMousePos.onBottomRightEdge )
    {
        right = globalMousePos.x();
        bottom = globalMousePos.y();
    }
    else if ( mPressedMousePos.onLeftEdge )
    {
        left = globalMousePos.x();
    }
    else if ( mPressedMousePos.onRightEdge )
    {
        right = globalMousePos.x();
    }
    else if ( mPressedMousePos.onTopEdge )
    {
        top = globalMousePos.y();
    }
    else if ( mPressedMousePos.onBottomEdge )
    {
        bottom = globalMousePos.y();
    }

    QRect newRect( QPoint(left, top), QPoint(right, bottom) );

    if ( newRect.isValid() )
    {
        if ( minWidth > newRect.width() )
        {
            //determine what has caused the width change.
            if( left != origRect.left() )
                newRect.setLeft( origRect.left() );
            else
                newRect.setRight( origRect.right() );
        }
        if ( minHeight > newRect.height() )
        {
            //determine what has caused the height change.
            if ( top != origRect.top() )
                newRect.setTop( origRect.top() );
            else
                newRect.setBottom( origRect.bottom() );
        }
        mWidget->move(newRect.topLeft());
        mWidget->resize(newRect.size());
    }
    else
    {
        //qDebug() << "Calculated Rect is not valid" << newRect;
    }

}

void NcWidgetData::moveWidget( const QPoint& globalMousePos )
{
    mWidget->move( globalMousePos - mDragPos );
    mWidget->update();
}

void NcWidgetData::handleMousePressEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWidget->setAttribute( Qt::WA_Hover, false);
        mLeftButtonPressed = true;

        QRect frameRect = mWidget->frameGeometry();
        mPressedMousePos.recalculate( event->globalPos(), frameRect, mBorderWidth);

        mDragPos = event->globalPos() - frameRect.topLeft();

    }
}

void NcWidgetData::handleMouseReleaseEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWidget->setAttribute( Qt::WA_Hover, true);
        mLeftButtonPressed = false;
        mPressedMousePos.reset();
    }
}

void NcWidgetData::handleMouseMoveEvent( QMouseEvent* event )
{
    if ( mLeftButtonPressed )
    {
        if(event->buttons() & Qt::LeftButton)
        {
            //qDebug() << mWidget->objectName();
            if ( mResizable && mPressedMousePos.onEdges )
            {
                resizeWidget( event->globalPos() );
            }
            else if ( mMovable )
            {
                moveWidget( event->globalPos() );
            }
        }

    }
    else if ( mResizable)
    {
        updateCursorShape( event->globalPos() );
    }

}

void NcWidgetData::handleLeaveEvent( QEvent* /*event*/ )
{
    if ( !mLeftButtonPressed )
        mWidget->unsetCursor();
}

void NcWidgetData::handleHoverMoveEvent( QHoverEvent* event )
{
    if ( mResizable)
        updateCursorShape( mWidget->mapToGlobal( event->pos() ) );
}

NcFramelessHelper::NcFramelessHelper( QObject* parent )
    : QObject( parent ),
      d( new NcFramelessHelperImpl )
{

}

NcFramelessHelper::~NcFramelessHelper()
{
    QList<QWidget*> keys = d->mHashWidgetData.keys();
    int size = keys.size();
    for ( int i = 0; i < size; ++i )
    {
        delete d->mHashWidgetData.take( keys[i] );
    }

    delete d;
}

bool NcFramelessHelper::eventFilter( QObject *obj, QEvent *event )
{
    QEvent::Type type = event->type();

    if ( type == QEvent::MouseMove ||
         type == QEvent::HoverMove ||
         type == QEvent::MouseButtonPress ||
         type == QEvent::MouseButtonRelease ||
         type == QEvent::Leave
         )
    {
        NcWidgetData* data = d->mHashWidgetData.value( static_cast<QWidget*>(obj) );
        if ( data )
        {
            data->handleWidgetEvent( event );
        }

    }

    return false;
}

void NcFramelessHelper::activateOn( QWidget* topLevelWidget )
{
    if ( d->mHashWidgetData.contains( topLevelWidget ) )
        return;

    NcWidgetData* data = new NcWidgetData( d, topLevelWidget );
    d->mHashWidgetData.insert( topLevelWidget, data );

    topLevelWidget->installEventFilter( this );

}

void NcFramelessHelper::removeFrom( QWidget* topLevelWidget )
{
    NcWidgetData* data = d->mHashWidgetData.take( topLevelWidget );
    if ( data )
    {
        topLevelWidget->removeEventFilter( this );
        delete data;
    }
}

void NcFramelessHelper::setWidgetMovable(QWidget *widget, bool movable )
{
    d->mHashWidgetData[widget]->setMovable(movable);
}

bool NcFramelessHelper::isWidgetMovable(QWidget *widget)
{
    return d->mHashWidgetData[widget]->isMovable();
}

void NcFramelessHelper::setWidgetResizable(QWidget *widget, bool resizable)
{
    d->mHashWidgetData[widget]->setResizable(resizable);
}

bool NcFramelessHelper::isWidgetResizable(QWidget *widget)
{
    return d->mHashWidgetData[widget]->isResizable();
}

void NcFramelessHelper::setBorderWidth(QWidget *widget, int newBorderWidth )
{
    //TODO: Make it non-static.
    if ( newBorderWidth >= 0 )
        d->mHashWidgetData[widget]->setBorderWidth(newBorderWidth);
}

int NcFramelessHelper::borderWidth(QWidget *widget)
{
    return d->mHashWidgetData[widget]->borderWidth();
}
