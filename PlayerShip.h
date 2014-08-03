#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Ship.h"
#include "QtSensors/QTiltSensor"

class PlayerShip: public Ship
{
  Q_OBJECT

public:
  PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void centerView();
  void updateDrag();
  void updateTilt();

private:
  QTiltSensor ts;
};

#endif
