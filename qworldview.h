#ifndef QWORLDVIEW_H
#define QWORLDVIEW_H
#include <set>
#include <QMainWindow>
#include "QGraphicsView"
#include "QGraphicsScene"
#include "box2dengine.h"
#include "Box2D/Box2D.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Diamond.h"
#include "World.h"

class QWorldView : public QGraphicsView, public b2ContactListener
{
    Q_OBJECT

public:
  explicit QWorldView(QtBox2DEngine* engine, QWidget *parent = 0);
  std::set<Item* > _items;

private:
  QtBox2DEngine *_engine;
  QGraphicsScene *_scene;
  PlayerShip* _player_ship;
  World* _world;
};

#endif // QWORLDVIEW_H
