#include <QApplication>
#include <QGraphicsScene>
#include "box2dengine.h"
#include "Cave.h"
#include "Diamond.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "MyContactListener.h"

const float view_scale = 108.;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);

  QGraphicsScene* scene = new QGraphicsScene;

  QGraphicsView* view = new QGraphicsView(scene);
  view->setMouseTracking(true);
  // view->resize(1920,1080);
  view->scale(view_scale, view_scale);
  view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view->setFrameStyle(0);
  view->showFullScreen();
    

  QtBox2DEngine* engine = new QtBox2DEngine;

  Cave* cave = new Cave(scene, engine, view);
  PlayerShip* player_ship = new PlayerShip(scene, engine, view);
  for (int i = 0; i < 10; ++i) {
    new EnemyShip(scene, engine, view, cave);
  }
  for (int i = 0; i < 30; ++i) {
    new Diamond(scene, engine, view, cave);
  }


  MyContactListener* myContactListenerInstance = new MyContactListener(engine, view);
  engine->setContactListener(myContactListenerInstance);

  engine->setGravity(0);
  engine->setInterval(60);
  engine->start();

  return a.exec();
}
