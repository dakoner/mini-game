#include "EnemyShip.h"

EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Ship(scene, engine, view) {
  std::vector<b2Vec2> ship_crds = { { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} };
  b2PolygonShape* _polyshape = new b2PolygonShape;
  _polyshape->Set(ship_crds.data(), ship_crds.size());

  _body = engine->createBody(b2_dynamicBody, 1, -4, 0, false);
  _body->SetFixedRotation(true);
  b2Fixture* fixture = engine->createFixture(_body, _polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);

  QVector<QPointF> polygon_crds = { { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} };
  QPolygonF polygon(polygon_crds);
  QPen p(Qt::white);
  p.setWidth(0);
  _pi = _scene->addPolygon(polygon, p);
  _pi->setData(0, QVariant::fromValue((void *)_body));
  _pi->setPos(_body->GetPosition().x, -_body->GetPosition().y);

  b2Vec2 force(1,0);
  _body->ApplyForceToCenter(force, true);

  connect(_engine, SIGNAL(step()), this, SLOT(update()));

}

void EnemyShip::update() {
  _pi->setPos(_body->GetPosition().x, -_body->GetPosition().y);
}
