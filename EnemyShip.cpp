#include "EnemyShip.h"
#include "qglobal.h"

EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Ship(scene, engine, view) {
  QPolygonF polygon({ { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} });
  QPen p(Qt::white);
  QBrush br(Qt::red, Qt::SolidPattern);
  p.setWidth(0);
  _it = _scene->addPolygon(polygon, p, br);

  std::vector<b2Vec2> ship_crds;
  for (auto item : polygon) {
    ship_crds.push_back(b2Vec2(item.x(), item.y()));
  }

  b2PolygonShape* polyshape = new b2PolygonShape;
  polyshape->Set(ship_crds.data(), ship_crds.size());

  _body = engine->createBody(b2_dynamicBody, (float)qrand()/RAND_MAX*40, (float)qrand()/RAND_MAX*10, 0, false);
  _body->SetFixedRotation(true);

  b2Fixture* fixture = engine->createFixture(_body, polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x2;
  b.maskBits = 0xffff;
  fixture->SetFilterData(b);
  fixture->SetUserData(this);


  b2Vec2 force((float)qrand()/RAND_MAX, (float)qrand()/RAND_MAX);
  _body->ApplyForceToCenter(force, true);
}
