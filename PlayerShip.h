#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Ship.h"
#include "QtSensors/QTiltSensor"

class PlayerShip: public Ship
{
  Q_OBJECT

public:
  PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  ~PlayerShip() {
    _scene->removeItem(_pi);
    delete _pi;
  }
  b2Body* Body();

  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void update();

private:
  QGraphicsPolygonItem* _pi;
  QTiltSensor ts;
};

#endif
