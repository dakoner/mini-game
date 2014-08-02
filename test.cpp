#include "QtWidgets/QApplication"
#include "QtGui/QtGui"
#include "Box2D/Box2D.h"
#include <iostream>
#include <vector>
#include "box2dengine.h"
#include "QtWidgets/QGraphicsScene"
#include "QtWidgets/QGraphicsView"
#include "UpdateReceiver.h"
#include "MotionFilter.h"

float scale = 72.;

int main(int argc, char *argv[]) {
  int& argc_ref(argc);
  QApplication app(argc_ref, argv);
  app.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);
  QGraphicsScene scene;

  QGraphicsView view;
  view.setMouseTracking(true);
  view.resize(1280,720);
  view.scale(scale, scale);
  view.setScene(&scene);
  view.setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  QtBox2DEngine engine;
  engine.setGravity(0);

  std::vector<b2Vec2> ship_crds = { {0, 0}, {.1, .1}, {0.2,0.025}, {.3333,.15}, {.2,.275}, {.1,.2}, {0,.3333} };
  b2PolygonShape *polyshape = new b2PolygonShape;
  polyshape->Set(ship_crds.data(), ship_crds.size());

  b2Body* body = engine.createBody(b2_dynamicBody, 2, -5, 0, false);
  b2Fixture* fixture = engine.createFixture(body, polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);

  QVector<QPointF> polygon_crds = { {0, 0}, {.1, .1}, {0.2,0.025}, {.3333,.15}, {.2,.275}, {.1,.2}, {0,.3333} };
  QPolygonF polygon(polygon_crds);
  QPen p(Qt::white);
  p.setWidth(0);
  QGraphicsPolygonItem* pi = scene.addPolygon(polygon, p);

  UpdateReceiver update_receiver(&view,  pi, body);
  QObject::connect(&engine, SIGNAL(step()), &update_receiver, SLOT(update()));

  MotionFilter* motion_filter = new MotionFilter(body);
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(body);
  // scene event filter required to get mouse events
  scene.installEventFilter(scene_motion_filter);
  view.installEventFilter(motion_filter);

  pi->setPos(body->GetPosition().x, -body->GetPosition().y);
  view.centerOn(1280/2,720/2);

  engine.start();

  view.show();
  return app.exec();

}
