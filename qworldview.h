#ifndef QWORLDVIEW_H
#define QWORLDVIEW_H

#include <QMainWindow>
#include "QGraphicsView"
#include "QGraphicsScene"
#include "box2dengine.h"
#include "Box2D/Box2D.h"
#include "Ship.h"

class QWorldView : public QGraphicsView
{
    Q_OBJECT

public:
  explicit QWorldView(QtBox2DEngine* engine, QWidget *parent = 0);

private:
  QtBox2DEngine *_engine;
  QGraphicsScene *_scene;
  Ship* _ship;
};

#endif // QWORLDVIEW_H
