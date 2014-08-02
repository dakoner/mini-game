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

class Ship: public QObject
{
  Q_OBJECT

public:
  Ship(QGraphicsView* view, QGraphicsScene* scene, QtBox2DEngine* engine);
  b2Body* Body();

  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void update();

private:
  QGraphicsView* _view;
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  b2PolygonShape *_polyshape;
  b2Body* _body;
  QGraphicsPolygonItem* _pi;
};

#endif
