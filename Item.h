#ifndef _ITEM_H_
#define _ITEM_H_

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

class Item: public QObject
{
  Q_OBJECT

public:
  Item(QGraphicsScene* scene, QtBox2DEngine* engine);
  ~Item() {
    if (_it.get() != nullptr)
      _scene->removeItem(_it.get());
  }
  b2Body* GetBody();
  QGraphicsItem* GetGraphicsItem();

  virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
  virtual void updatePosition();

protected:
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  b2Body* _body;
  std::unique_ptr<QGraphicsItem> _it;
};

#endif
