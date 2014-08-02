#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "Ship.h"

class Diamond: public QObject
{
  Q_OBJECT

public:
  Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
private:
  QGraphicsScene* _scene;
  QtBox2DEngine* _engine;
  QGraphicsView* _view;
  b2Body* _body;
  QGraphicsPolygonItem* _pi;
};

#endif
