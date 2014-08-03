#include <math.h>

#include <iostream>
#include <vector>

#include "qworldview.h"
#include "QtGui/QtGui"
#include "MotionFilter.h"
#include "MyContactListener.h"

const float view_scale = 72.;

class QWorldView;
QWorldView::QWorldView(QtBox2DEngine* engine, QWidget *parent) :
  QGraphicsView(parent),
  _engine(engine),
  _scene(new QGraphicsScene)
{

  setMouseTracking(true);
  resize(1280,720);
  scale(view_scale, view_scale);
  setScene(_scene);
  setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  QGraphicsTextItem* ti = _scene->addText("Test");
  ti->setDefaultTextColor(Qt::red);
  ti->setX(0);
  ti->setY(0);
  ti->setScale(0.005);
  
  _player_ship = new PlayerShip(_scene, engine, this);
  for (int i = 0; i < 3; ++i) {
    _enemy_ships.insert(new EnemyShip(_scene, engine, this));
  }
  _world = new World(_scene, engine, this);
  for (int i = 0; i < 30; ++i) {
    _diamonds.insert(new Diamond(_scene, engine, this));
  }

  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(_player_ship);
  // scene event filter required to get mouse events
  _scene->installEventFilter(scene_motion_filter);
  installEventFilter(_player_ship);

  MyContactListener* myContactListenerInstance = new MyContactListener(_engine, this);
  engine->setContactListener(myContactListenerInstance);

}

