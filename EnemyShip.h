#ifndef _ENEMY_SHIP_H_
#define _ENEMY_SHIP_H_

#include "Ship.h"

class EnemyShip: public Ship
{
  Q_OBJECT

public:
  EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  ~EnemyShip() {
    _scene->removeItem(_pi);
    delete _pi;
  }
  b2Body* Body();

private slots:
  void update();

private:
  QGraphicsPolygonItem* _pi;
};

#endif
