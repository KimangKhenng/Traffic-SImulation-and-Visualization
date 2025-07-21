#include <QPoint>
#include <QList>
#include <QHash>
#include <QSizeF>
#include "Entities/Vehicle/vehicle.h"

class SpatialGrid
{
public:
    SpatialGrid(double cellSize);

    void clear();
    void insert(Vehicle *vehicle);
    QList<Vehicle *> getNearby(Vehicle *vehicle, double radius) const;

private:
    QPoint computeCellKey(const QPointF &pos) const;

    double m_cellSize;
    QHash<QPoint, QList<Vehicle *>> m_grid; // 2D grid mapping
};
