#ifndef _POLYGON_ITEM_H_
#define _POLYGON_ITEM_H_

#include <vector>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "Box2D/Box2D.h"
#include "box2dengine.h"
#include "Item.h"

class PolygonItem: public Item
{
  Q_OBJECT

public:
  PolygonItem(QPolygonF polygon, QPen p, QBrush br, QPointF point, uint16 categoryBits, uint16 maskBits, QGraphicsScene* scene, QtBox2DEngine* engine);
protected:
  b2PolygonShape* _polyshape;
  b2Fixture* _fixture;
};

#endif
