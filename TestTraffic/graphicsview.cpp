#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent):QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    //setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    int level_of_zoom = 3;
    if( m_max <120*level_of_zoom&&event->delta()>0){
        m_min -= 120;
        m_max += event->delta();
        //setSceneRect(0,0,size().height()*scaleFactor,size().width()*scaleFactor);
        this->scale(scaleFactor, scaleFactor);
    }
    if( m_min < 120*level_of_zoom&&event->delta()<0){
        m_max -= 120;
        m_min -= event->delta();
        //setSceneRect(0,0,size().height()/scaleFactor,size().width()/scaleFactor);
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
void GraphicsView::resizeEvent(QResizeEvent *event)
{
    setSceneRect(event->size().width()/2,event->size().height()/2,event->size().width(),event->size().height());
//    qDebug()<<sceneRect();
//    qDebug()<<event->size();
}

void GraphicsView::Initializer()
{
    fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
}

/*void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->pos();
}*/

