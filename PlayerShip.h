#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "Ship.h"

class PlayerShip: public Ship
{
  Q_OBJECT

public:
  PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  b2Body* Body();

  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void update();

private:
  b2ChainShape *_chainshape;
  QGraphicsPolygonItem* _pi;
};

#endif
