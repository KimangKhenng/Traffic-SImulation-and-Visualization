#include "spatialgrid.h"
#include "Entities/Vehicle/vehicle.h"
#include <QDebug>
#include <QtMath>

SpatialGrid::SpatialGrid(const QRectF& bounds, qreal cellSize)
    : m_bounds(bounds)
    , m_cellSize(cellSize)
    , m_gridWidth(qCeil(bounds.width() / cellSize))
    , m_gridHeight(qCeil(bounds.height() / cellSize))
{
    // Pre-reserve some space for better performance
    m_cells.reserve(m_gridWidth * m_gridHeight / 4); // Assume 25% occupancy initially
    m_vehicleCells.reserve(1000); // Reserve space for up to 1000 vehicles initially
    
    qDebug() << "SpatialGrid created with bounds:" << bounds 
             << "cellSize:" << cellSize 
             << "grid dimensions:" << m_gridWidth << "x" << m_gridHeight;
}

void SpatialGrid::insert(Vehicle* vehicle, const QPointF& position, const QRectF& boundingRect)
{
    if (!vehicle) return;
    
    // Remove the vehicle if it's already in the grid (to handle duplicates)
    remove(vehicle);
    
    // Get all cells that this vehicle overlaps
    QRectF vehicleRect = boundingRect;
    vehicleRect.moveCenter(position);
    QList<QPair<int, int>> cellCoords = getCellsForRect(vehicleRect);
    
    QSet<uint> cellKeys;
    for (const auto& coord : cellCoords) {
        if (isValidCell(coord.first, coord.second)) {
            uint key = getCellKey(coord.first, coord.second);
            cellKeys.insert(key);
            m_cells[key].vehicles.append(vehicle);
        }
    }
    
    // Store which cells this vehicle occupies
    m_vehicleCells[vehicle] = cellKeys;
}

void SpatialGrid::remove(Vehicle* vehicle)
{
    if (!vehicle) return;
    
    auto it = m_vehicleCells.find(vehicle);
    if (it == m_vehicleCells.end()) return;
    
    // Remove the vehicle from all cells it occupied
    const QSet<uint>& cellKeys = it.value();
    for (uint key : cellKeys) {
        auto cellIt = m_cells.find(key);
        if (cellIt != m_cells.end()) {
            cellIt.value().vehicles.removeOne(vehicle);
            // Clean up empty cells to save memory
            if (cellIt.value().vehicles.isEmpty()) {
                m_cells.erase(cellIt);
            }
        }
    }
    
    // Remove the vehicle from our tracking
    m_vehicleCells.erase(it);
}

void SpatialGrid::update(Vehicle* vehicle, const QPointF& newPosition, const QRectF& boundingRect)
{
    if (!vehicle) return;
    
    // For efficiency, we could check if the vehicle has actually moved to a different cell
    // before doing a full remove/insert, but for simplicity we'll always remove and re-insert
    insert(vehicle, newPosition, boundingRect);
}

QList<Vehicle*> SpatialGrid::getNearbyVehicles(const QPointF& position, const QRectF& queryRect) const
{
    m_tempVehicleList.clear();
    QSet<Vehicle*> uniqueVehicles; // Use QSet to avoid duplicates
    
    // Get the query area in world coordinates
    QRectF searchRect = queryRect;
    searchRect.moveCenter(position);
    
    // Get all cells that overlap with the search area
    QList<QPair<int, int>> cellCoords = getCellsForRect(searchRect);
    
    // Also include neighboring cells to handle edge cases where vehicles might be
    // partially in adjacent cells
    QSet<QPair<int, int>> expandedCells;
    for (const auto& coord : cellCoords) {
        QList<QPair<int, int>> neighbors = getNeighboringCells(coord.first, coord.second);
        for (const auto& neighbor : neighbors) {
            if (isValidCell(neighbor.first, neighbor.second)) {
                expandedCells.insert(neighbor);
            }
        }
    }
    
    // Collect vehicles from all relevant cells
    for (const auto& coord : expandedCells) {
        uint key = getCellKey(coord.first, coord.second);
        auto it = m_cells.find(key);
        if (it != m_cells.end()) {
            for (Vehicle* vehicle : it.value().vehicles) {
                uniqueVehicles.insert(vehicle);
            }
        }
    }
    
    // Convert set back to list
    for (Vehicle* vehicle : uniqueVehicles) {
        m_tempVehicleList.append(vehicle);
    }
    
    return m_tempVehicleList;
}

QList<Vehicle*> SpatialGrid::getVehiclesInCell(const QPointF& position) const
{
    QPair<int, int> coord = worldToGrid(position);
    
    if (!isValidCell(coord.first, coord.second)) {
        return QList<Vehicle*>();
    }
    
    uint key = getCellKey(coord.first, coord.second);
    auto it = m_cells.find(key);
    
    if (it != m_cells.end()) {
        return it.value().vehicles;
    }
    
    return QList<Vehicle*>();
}

void SpatialGrid::clear()
{
    m_cells.clear();
    m_vehicleCells.clear();
}

int SpatialGrid::getVehicleCount() const
{
    return m_vehicleCells.size();
}

QString SpatialGrid::getDebugInfo() const
{
    int occupiedCells = m_cells.size();
    int totalCells = m_gridWidth * m_gridHeight;
    int vehicleCount = getVehicleCount();
    
    double occupancyPercentage = occupiedCells * 100.0 / totalCells;
    double avgVehiclesPerCell = occupiedCells > 0 ? vehicleCount * 1.0 / occupiedCells : 0.0;
    
    QString info = QString("SpatialGrid Debug Info:\n"
                          "  Grid Size: %1x%2 (%3 total cells)\n"
                          "  Occupied Cells: %4 (%5%)\n"
                          "  Vehicle Count: %6\n"
                          "  Avg Vehicles per Occupied Cell: %7")
                   .arg(m_gridWidth)
                   .arg(m_gridHeight)
                   .arg(totalCells)
                   .arg(occupiedCells)
                   .arg(occupancyPercentage, 0, 'f', 1)
                   .arg(vehicleCount)
                   .arg(avgVehiclesPerCell, 0, 'f', 1);
    
    return info;
}

QPair<int, int> SpatialGrid::worldToGrid(const QPointF& position) const
{
    int gridX = qFloor((position.x() - m_bounds.left()) / m_cellSize);
    int gridY = qFloor((position.y() - m_bounds.top()) / m_cellSize);
    return QPair<int, int>(gridX, gridY);
}

QList<QPair<int, int>> SpatialGrid::getCellsForRect(const QRectF& rect) const
{
    QList<QPair<int, int>> cells;
    
    // Get the grid coordinates for the rectangle corners
    QPair<int, int> topLeft = worldToGrid(rect.topLeft());
    QPair<int, int> bottomRight = worldToGrid(rect.bottomRight());
    
    // Iterate through all cells that the rectangle overlaps
    for (int x = topLeft.first; x <= bottomRight.first; ++x) {
        for (int y = topLeft.second; y <= bottomRight.second; ++y) {
            cells.append(QPair<int, int>(x, y));
        }
    }
    
    return cells;
}

QList<QPair<int, int>> SpatialGrid::getNeighboringCells(int gridX, int gridY) const
{
    QList<QPair<int, int>> neighbors;
    
    // Include the cell itself and all 8 surrounding cells
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int x = gridX + dx;
            int y = gridY + dy;
            neighbors.append(QPair<int, int>(x, y));
        }
    }
    
    return neighbors;
}

bool SpatialGrid::isValidCell(int gridX, int gridY) const
{
    return gridX >= 0 && gridX < m_gridWidth && gridY >= 0 && gridY < m_gridHeight;
}

uint SpatialGrid::getCellKey(int gridX, int gridY) const
{
    // Simple hash function for grid coordinates
    // This assumes grid dimensions won't exceed 65536x65536
    return static_cast<uint>(gridX) | (static_cast<uint>(gridY) << 16);
}