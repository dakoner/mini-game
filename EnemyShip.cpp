#include "EnemyShip.h"
#include "qglobal.h"

EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Ship(scene, engine, view) {
  std::vector<b2Vec2> ship_crds = { { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} };
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

  QVector<QPointF> polygon_crds;
  for(auto& item : ship_crds) {
    polygon_crds.push_back(QPointF(item.x, item.y));
  }
  QPolygonF polygon(polygon_crds);
  QPen p(Qt::white);
  p.setWidth(0);
  _it = _scene->addPolygon(polygon, p);
  _it->setData(0, QVariant::fromValue((void *)_body));
  _it->setPos(_body->GetPosition().x, _body->GetPosition().y);
  ((QGraphicsPolygonItem *)_it)->setBrush(QBrush(Qt::red, Qt::SolidPattern));

  b2Vec2 force((float)qrand()/RAND_MAX, (float)qrand()/RAND_MAX);
  _body->ApplyForceToCenter(force, true);
}
