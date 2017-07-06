#ifndef VEHICLE_H
#define VEHICLE_H
#include <QtWidgets>
#include "road.h"
#include "traffic_light_widget.h"
class Vehicle: public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Vehicle();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void rotate_to_point(QPointF point);
    void extract_coordinate(QPainterPath path);
    void initialize(Traffic_Light_widget *m_traffic);
    double distance_to_other_vehicle(Vehicle *car);
    bool is_on_action();
    bool is_in_stop_point();
    void set_on_action(bool state);
    bool is_no_car_infront();
    void reset_speed();
    void decelerate();
    void accerlerate();
    bool is_on_the_same_path(Vehicle *vehicle);
    QList<QPointF> get_path();
    Vehicle *get_next_vehicle();
    Vehicle *get_back_vehicle();
    bool Isinthejunction();
    QPointF get_position();
    int get_current_index();
    QPointF get_initial_path();
    QTimer *get_timer();
    void get_list_of_all(QList<Vehicle *> *car_list);
    QList<Vehicle *> *get_list();
    void set_order_in_list(int x);
    bool is_enter_the_junction();
    void stop_advance();
    void remove_next();
    int get_index_in_list();

public slots:
    void advance();
private:
    qreal m_angle;
    qreal m_speed;
    QColor m_color;
    QList<QPointF> m_path_to_follow;
    QPointF m_destination;
    int m_point_index;
    QTimer *m_internal_timer;
    bool m_on_action_state;
    QList<Vehicle *> *m_list;
    int m_step_count;
    int m_order_in_list;
    Vehicle *m_next;
    Vehicle *m_back;
    bool m_driving_state;
    Traffic_Light_widget *m_traffic_widget;
};

#endif // VEHICLE_H
