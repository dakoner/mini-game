#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "Item.h"

#include "Box2D/Box2D.h"
#include "box2dengine.h"

class World: public Item
{
  Q_OBJECT

public:
  World(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  void addLine(double x1, double y1, double x2, double y2, QList<QGraphicsItem*>* items);
  void addChain(const QList<QPointF>& points, QList<QGraphicsItem*>* items);
};

#endif
