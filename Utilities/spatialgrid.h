#ifndef SPATIALGRID_H
#define SPATIALGRID_H

#include <QHash>
#include <QList>
#include <QPointF>
#include <QRectF>
#include <QSet>

class Vehicle;

/**
 * @brief The SpatialGrid class provides an efficient spatial partitioning system for collision detection
 * 
 * This class divides the simulation area into a grid of cells. Each vehicle is assigned to one or more
 * cells based on its position and bounding rectangle. When checking for collisions, vehicles only need
 * to check against other vehicles in the same or neighboring cells, dramatically reducing the number
 * of collision checks from O(n²) to approximately O(n).
 */
class SpatialGrid
{
public:
    /**
     * @brief Construct a new Spatial Grid object
     * @param bounds The total area covered by the grid
     * @param cellSize The size of each grid cell (both width and height)
     */
    SpatialGrid(const QRectF& bounds, qreal cellSize = 100.0);
    
    /**
     * @brief Insert a vehicle into the spatial grid
     * @param vehicle The vehicle to insert
     * @param position The current position of the vehicle
     * @param boundingRect The bounding rectangle of the vehicle (for multi-cell occupancy)
     */
    void insert(Vehicle* vehicle, const QPointF& position, const QRectF& boundingRect);
    
    /**
     * @brief Remove a vehicle from the spatial grid
     * @param vehicle The vehicle to remove
     */
    void remove(Vehicle* vehicle);
    
    /**
     * @brief Update a vehicle's position in the spatial grid
     * @param vehicle The vehicle to update
     * @param newPosition The new position of the vehicle
     * @param boundingRect The bounding rectangle of the vehicle
     */
    void update(Vehicle* vehicle, const QPointF& newPosition, const QRectF& boundingRect);
    
    /**
     * @brief Get all vehicles that could potentially collide with the given area
     * @param position Center position to query around
     * @param queryRect The area to search for potential collisions
     * @return List of vehicles in the query area and neighboring cells
     */
    QList<Vehicle*> getNearbyVehicles(const QPointF& position, const QRectF& queryRect) const;
    
    /**
     * @brief Get all vehicles in the same cell as the given position
     * @param position The position to query
     * @return List of vehicles in the same cell
     */
    QList<Vehicle*> getVehiclesInCell(const QPointF& position) const;
    
    /**
     * @brief Clear all vehicles from the grid
     */
    void clear();
    
    /**
     * @brief Get the total number of vehicles currently in the grid
     * @return Number of vehicles
     */
    int getVehicleCount() const;
    
    /**
     * @brief Get debug information about grid usage
     * @return String containing grid statistics
     */
    QString getDebugInfo() const;

private:
    struct GridCell {
        QList<Vehicle*> vehicles;
    };
    
    /**
     * @brief Convert world coordinates to grid coordinates
     * @param position World position
     * @return Grid coordinates as QPair<int, int>
     */
    QPair<int, int> worldToGrid(const QPointF& position) const;
    
    /**
     * @brief Get all grid cells that overlap with the given rectangle
     * @param rect Rectangle in world coordinates
     * @return List of grid coordinates that overlap with the rectangle
     */
    QList<QPair<int, int>> getCellsForRect(const QRectF& rect) const;
    
    /**
     * @brief Get neighboring cells around the given cell (including the cell itself)
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return List of neighboring grid coordinates
     */
    QList<QPair<int, int>> getNeighboringCells(int gridX, int gridY) const;
    
    /**
     * @brief Check if grid coordinates are within bounds
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return True if coordinates are valid
     */
    bool isValidCell(int gridX, int gridY) const;
    
    /**
     * @brief Get the hash key for grid coordinates
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return Hash key for the cell
     */
    uint getCellKey(int gridX, int gridY) const;

private:
    QRectF m_bounds;                                    // Total area covered by the grid
    qreal m_cellSize;                                   // Size of each cell
    int m_gridWidth;                                    // Number of cells horizontally
    int m_gridHeight;                                   // Number of cells vertically
    
    QHash<uint, GridCell> m_cells;                      // Hash map of all cells
    QHash<Vehicle*, QSet<uint>> m_vehicleCells;         // Track which cells each vehicle occupies
    
    mutable QList<Vehicle*> m_tempVehicleList;          // Temporary list to avoid allocations
};

#endif // SPATIALGRID_H