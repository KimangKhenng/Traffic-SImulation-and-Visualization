#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QWidget>

#include "mainwindow.h"

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);
    void Initializer();

protected:
    // Control Mouse wheel to zoom
    void wheelEvent(QWheelEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
    //virtual void resizeEvent(QResizeEvent *event);


private:
    qreal m_min;
    qreal m_max;
};

#endif // GRAPHICSVIEW_H
