#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "PolygonItem.h"
#include "QtSensors/QTiltSensor"

class PlayerShip: public PolygonItem
{
  Q_OBJECT

public:
  PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine);
  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void updateDrag();
  void updateTilt();

private:
  QTiltSensor ts;
};

#endif
