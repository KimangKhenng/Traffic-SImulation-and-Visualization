#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QWidget>
#include <QtWidgets>
#include "mainwindow.h"
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = 0);
    void Initializer();

protected:
    // Control Mouse wheel to zoom
    virtual void wheelEvent(QWheelEvent *event);
    //virtual void resizeEvent(QResizeEvent *event);
//    virtual void mousePressEvent(QMouseEvent *event);

private:
    qreal m_min;
    qreal m_max;
};

#endif // GRAPHICSVIEW_H
