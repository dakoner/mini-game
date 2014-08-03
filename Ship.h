#ifndef _SHIP_H_
#define _SHIP_H_

#include <vector>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>

#include "Box2D/Box2D.h"
#include "box2dengine.h"
#include "Item.h"

class Ship: public Item
{
  Q_OBJECT

public:
  Ship(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);

};

#endif
