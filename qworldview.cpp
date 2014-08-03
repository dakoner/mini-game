#include <math.h>

#include <iostream>
#include <vector>

#include "qworldview.h"
#include "QtGui/QtGui"
#include "MotionFilter.h"
#include "MyContactListener.h"

const float view_scale = 108.;

class QWorldView;
QWorldView::QWorldView(QWidget *parent) :
  QGraphicsView(parent) {

  QGraphicsScene* _scene= new QGraphicsScene;
  QtBox2DEngine* engine= new QtBox2DEngine;

  setMouseTracking(true);
  resize(1920,1080);
  scale(view_scale, view_scale);
  setScene(_scene);
  setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  _world = new World(_scene, engine, this);
  _items.insert(_world);
  PlayerShip* player_ship = new PlayerShip(_scene, engine, this);
  _items.insert(player_ship);
  for (int i = 0; i < 3; ++i) {
    _items.insert(new EnemyShip(_scene, engine, this));
  }
  for (int i = 0; i < 30; ++i) {
    _items.insert(new Diamond(_scene, engine, this));
  }

  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(player_ship);
  // scene event filter required to get mouse events
  _scene->installEventFilter(scene_motion_filter);
  installEventFilter(player_ship);

  MyContactListener* myContactListenerInstance = new MyContactListener(engine, this);
  engine->setContactListener(myContactListenerInstance);

  engine->setGravity(0);
  engine->setInterval(60);
  engine->start();
}

