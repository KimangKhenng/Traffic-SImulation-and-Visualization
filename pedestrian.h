#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

#define SIZE 15

class Pedestrian :public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Pedestrian(QGraphicsEllipseItem *parent = nullptr);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    virtual ~Pedestrian() override;
public slots:
    void advance(int phase) Q_DECL_OVERRIDE;
private:
    QGraphicsRectItem *m_sightseeing;
};

#endif // PEDESTRIAN_H
