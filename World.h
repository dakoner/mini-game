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
#include <QGraphicsPolygonItem>

#include "Box2D/Box2D.h"
#include "box2dengine.h"

class World: public QObject
{
  Q_OBJECT

public:
  World(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);


protected:
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  QGraphicsView* _view;
};

#endif
