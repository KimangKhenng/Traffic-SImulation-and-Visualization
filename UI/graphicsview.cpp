#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent):QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setOptimizationFlag(GraphicsView::DontSavePainterState);
    setCacheMode(QGraphicsView::CacheBackground);

    //setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    //this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
//    GraphicsView::wheelEvent(event);
    double scaleFactor = 1.15;
    //int level_of_zoom = 5;
    if( /*m_max <120*level_of_zoom&&*/event->delta()>0){
        //m_min -= 120;
        //m_max += event->delta();
        //setSceneRect(0,0,size().height()*scaleFactor,size().width()*scaleFactor);
        this->scale(scaleFactor, scaleFactor);
    }
    if(/* m_min < 120*level_of_zoom&&*/event->delta()<0){
        //m_max -= 120;
        //m_min -= event->delta();
        //setSceneRect(0,0,size().height()/scaleFactor,size().width()/scaleFactor);
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

//void GraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//    QGraphicsView::mouseMoveEvent(event);
//    //qDebug()<<"Actual Position "<<event->pos()<<"Scene Pos "<<event->screenPos();
//    if(event->buttons() == Qt::RightButton){
//        this->setCursor(Qt::SizeAllCursor);

//    }
//    if(event->buttons() == Qt::LeftButton){
//        if(dynamic_cast<Vehicle*>(this->scene()->itemAt(this->mapToScene(event->pos()),this->transform()))){
//            this->setCursor(Qt::OpenHandCursor);
//            //qDebug()<<event->pos();
//        }
//    }
//}

//void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
//{
//    QGraphicsView::mouseReleaseEvent(event);
//    this->setCursor(Qt::ArrowCursor);

//}
/*void GraphicsView::resizeEvent(QResizeEvent *event)
{
    setSceneRect(event->size().width()/2,event->size().height()/2,event->size().width(),event->size().height());
    qDebug()<<sceneRect();
    qDebug()<<event->size();
}*/

void GraphicsView::Initializer()
{
    fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
}

//void GraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    QGraphicsView::mousePressEvent(event);
//    qDebug()<<"Hello";
//}

