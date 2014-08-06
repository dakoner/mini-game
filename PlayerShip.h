#ifndef _PLAYER_SHIP_H_
#define _PLAYER_SHIP_H_

#include "PolygonItem.h"

class PlayerShip: public PolygonItem
{
  Q_OBJECT

public:
  PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine);
};

#endif
