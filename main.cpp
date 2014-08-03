#include <QApplication>
#include <QGraphicsScene>
#include "box2dengine.h"
#include "World.h"
#include "Diamond.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "MyContactListener.h"
#include "MotionFilter.h"

const float view_scale = 108.;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);

  QGraphicsScene* scene = new QGraphicsScene;

  QGraphicsView* view = new QGraphicsView(scene);
  view->setMouseTracking(true);
  view->resize(1920,1080);
  view->scale(view_scale, view_scale);
  view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->show();
    

  QtBox2DEngine* engine = new QtBox2DEngine;

  World* world = new World(scene, engine, view);
  PlayerShip* player_ship = new PlayerShip(scene, engine, view);
  for (int i = 0; i < 3; ++i) {
    new EnemyShip(scene, engine, view);
  }
  for (int i = 0; i < 30; ++i) {
    new Diamond(scene, engine, view);
  }

  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(player_ship);
  // scene event filter required to get mouse events
  scene->installEventFilter(scene_motion_filter);
  view->installEventFilter(player_ship);

  MyContactListener* myContactListenerInstance = new MyContactListener(engine, view);
  engine->setContactListener(myContactListenerInstance);

  engine->setGravity(0);
  engine->setInterval(60);
  engine->start();

  return a.exec();
}
