#ifndef VEHICLE_H
#define VEHICLE_H
#define GAPACCAPANCE 10

#include <QtWidgets>
#include "commonenum.h"
#include "road.h"
class Vehicle: public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Vehicle(QGraphicsItem *parent = 0);
    // @Overloading Function
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    // Overloading Funcion
    //////////////////////
    /// \brief rotate_to_point
    /// \param point
    /// use to rotate to a specfic point
    /// //////////////////
    void rotate_to_point(QPointF point);
    /////////////////////
    /// \brief extract_coordinate
    /// \param path
    /// Give vehile a path to follow
    /// path = QPainterPath
    /// Draw By Yourself
    void extract_coordinate(QPainterPath path);
    /////////////////////
    /// \brief setDirection
    /// \param dir
    /// set turning direction for vehicle
    void setDirection(Direction dir);
    /////////////////////
    /// \brief setTrafficLight
    /// \param light
    /// set Traffic to be obeyed for vehicle
    /// ////////////
    void initialize();
    void setRegion(region r);
    double distance_to_other_vehicle(Vehicle *car);
    bool is_on_action();
    bool is_in_stop_point();
    void set_on_action(bool state);
    void reset_speed();
    void decelerate();
    void accerlerate();
    QList<QPointF> get_path();
    bool Isinthejunction();
    QPointF get_position() const;
    int get_current_index() const;
    QPointF get_initial_path() const;
    QTimer *get_timer();
    bool is_enter_the_junction();
    void stop_advance();
    region getRegion() const;
    bool ifAllowed() const;
    Direction getDir() const;
    void setDir(const Direction &dir);

public slots:
    void advance();
private:
    Vehicle *getCollding();
    bool hasInfront();
    qreal m_angle;
    qreal m_speed;
    QColor m_color;
    QList<QPointF> m_path_to_follow;
    QPointF m_destination;
    int m_point_index;
    QTimer *m_internal_timer;
    bool m_on_action_state;
    int m_step_count;
    bool m_driving_state;
    QGraphicsRectItem *m_sightseeing;
    Direction m_dir;
    region m_region;
};

#endif // VEHICLE_H
