#include "SpatialGrid.h"
#include <QtMath>

SpatialGrid::SpatialGrid(double cellSize)
    : m_cellSize(cellSize)
{
}

void SpatialGrid::clear()
{
    m_grid.clear();
}

void SpatialGrid::insert(Vehicle *vehicle)
{
    QPoint key = computeCellKey(vehicle->pos());
    m_grid[key].append(vehicle);
}

QPoint SpatialGrid::computeCellKey(const QPointF &pos) const
{
    return QPoint(static_cast<int>(pos.x() / m_cellSize),
                  static_cast<int>(pos.y() / m_cellSize));
}

QList<Vehicle *> SpatialGrid::getNearby(Vehicle *vehicle, double radius) const
{
    QList<Vehicle *> result;
    QPoint centerKey = computeCellKey(vehicle->pos());

    int range = static_cast<int>(qCeil(radius / m_cellSize));

    for (int dx = -range; dx <= range; ++dx)
    {
        for (int dy = -range; dy <= range; ++dy)
        {
            QPoint neighborKey = centerKey + QPoint(dx, dy);
            if (m_grid.contains(neighborKey))
            {
                for (Vehicle *other : m_grid[neighborKey])
                {
                    if (other != vehicle && QLineF(vehicle->pos(), other->pos()).length() <= radius)
                    {
                        result.append(other);
                    }
                }
            }
        }
    }

    return result;
}
