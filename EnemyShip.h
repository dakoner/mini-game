#ifndef _ENEMY_SHIP_H_
#define _ENEMY_SHIP_H_

#include "Ship.h"

class EnemyShip: public Ship
{
  Q_OBJECT

public:
  EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
};

#endif
