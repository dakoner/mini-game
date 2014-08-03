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
  Ship(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  b2Body* Body();

  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  // Currently pure virtual, but if we kept a pointer to the
  // QGraphicsItem created by subclasses, we could put the position
  // update in the base class
  virtual void updatePosition() = 0;

protected:
  b2Body* _body;
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  QGraphicsView* _view;
};

#endif
