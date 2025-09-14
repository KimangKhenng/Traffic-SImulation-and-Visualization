#ifndef VEHICLE_H
#define VEHICLE_H
#define GAPACCAPANCE 10


#include "Entities/TrafficLight/trafficlight.h"
#include "vehiclesight.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <qmath.h>

static const float ACCER = 0.01;

class SimulationScene;
class Vehicle: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Vehicle(QGraphicsItem *parent = nullptr);
    ////////
    /// \brief Vehicle
    /// Prevent Copying
    Vehicle(const Vehicle&) = delete;
    ///////
    /// \brief operator =
    /// \return Address of Vehicle
    /// Prevent using operator =
    Vehicle& operator = (const Vehicle&) = delete;
    ~Vehicle();
    //// Overloading Function
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    // Overloading Funcion
    //////////////////////
    /// \brief rotate_to_point
    /// \param point = point for vehicle to rotate to
    /// use to rotate to a specfic point
    /// //////////////////
    void rotate_to_point(QPointF point);
    /////////////////////
    /// \brief extract_coordinate
    /// \param path = QPainterPath as path to follow
    /// Give vehile a path to follow
    /// path = QPainterPath
    /// Draw By Yourself
    void extract_coordinate(QPainterPath path);
    /////////////////////
    /// \brief setDirection
    /// \param dir = region for vehicle to appear
    /// set turning direction for vehicle
    void setDirection(Direction dir);
    /////////////////////
    /// \brief setTrafficLight
    /// \param light
    /// set Traffic to be obeyed for vehicle
    /// ////////////
    void initialize();
    /////////////////
    /// \brief setRegion
    /// \param r
    /// set Which region vehicle belong to
    void setRegion(region r);
    /// ////////////


    bool is_in_stop_point();
    QList<QPointF> get_path() const;
    bool Isinthejunction();
    QPointF get_position() const;
    int get_current_index() const;
    QPointF get_initial_path() const;
    region getRegion() const;
    Direction getDir() const;
    void setDir(const Direction &dir);
    void turnOnSightSeeing();
    void turnOffSightSeeing();
    void turnOnEngine();
    void turnOffEngine();
    bool isContainedSignal() const;
    void setMode(const VEHICLEMETHOD &mode);
    bool isDeletable() const;
     qreal getSpeed() const;
     void turnOffInteraction();
     void turnOnInteraction();
    //Reimplement Event

//    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public slots:
    void advance(int phase) Q_DECL_OVERRIDE;
    void update(const VEHICLEMETHOD& mode = VEHICLEMETHOD::SIGHTSEEING);
    //void forward();
private:
    QPixmap generateImage() const;
    Vehicle *getCollding();
    Vehicle *nextVehicle();
    SimulationScene *myScene() const;

    double distanceToOtherVehicle(QGraphicsItem *v) const;

    void adjustSpeedIntersection();
    void adjustSpeedIntersection(Vehicle *leader);
    bool ifAllowed() const;
    bool hasInfront();
    bool is_enter_the_junction() const;
    bool isAboutToCrash() const;
    void reset_speed();
    void decelerate(QPointF rhs);
    void accelerate();
    void accelerate(Vehicle *leader);
    void stop_advance();
    bool isInsideIntersection();

    qreal m_angle;
    qreal m_speed;
    qreal m_acceleration;
//    QColor m_color;
    QList<QPointF> m_path_to_follow;
    QPointF m_destination;
    int m_point_index;
    int m_step_count;
    bool m_driving_state;
    VehicleSight *m_sightseeing;
    VehicleSight *m_sightseeing_small;
    Direction m_dir;
    region m_region;
    //QTimer *m_internal_timer;
    VEHICLEMETHOD m_mode;
    bool m_Is_deletable;
    Vehicle* m_leader;
};

#endif // VEHICLE_H
