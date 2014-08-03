#ifndef _ITEM_H_
#define _ITEM_H_

#include <vector>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include "Box2D/Box2D.h"
#include "box2dengine.h"

class Item: public QObject
{
  Q_OBJECT

public:
  Item(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
  ~Item() {
    _scene->removeItem(_it);
    delete _it;
  }
  QGraphicsView* GetView();
  b2Body* GetBody();
  QGraphicsItem* GetGraphicsItem();

  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  virtual void updatePosition();

protected:
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  QGraphicsView* _view;
  b2Body* _body;
  QGraphicsItem* _it;
};

#endif
