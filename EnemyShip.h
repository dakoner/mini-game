#ifndef _ENEMY_SHIP_H_
#define _ENEMY_SHIP_H_

#include "Ship.h"

class EnemyShip: public Ship
{
  Q_OBJECT

public:
  EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  b2Body* Body();

private slots:
  void update();

private:
  b2PolygonShape *_polyshape;
  QGraphicsPolygonItem* _pi;
};

#endif
