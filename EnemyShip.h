#ifndef _ENEMY_SHIP_H_
#define _ENEMY_SHIP_H_

#include "PolygonItem.h"
#include "Cave.h"

class EnemyShip: public PolygonItem
{
  Q_OBJECT

public:
  EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, Cave* cave);
};

#endif
