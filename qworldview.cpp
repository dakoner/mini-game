#include <math.h>

#include <iostream>
#include <vector>

#include "qworldview.h"
#include "QtGui/QtGui"
#include "MotionFilter.h"
#include "PlayerShip.h"

const float view_scale = 72.;

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

  _ship = new PlayerShip(_scene, engine, this);

  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(_ship);
  // scene event filter required to get mouse events
  _scene->installEventFilter(scene_motion_filter);
  installEventFilter(_ship);
}

