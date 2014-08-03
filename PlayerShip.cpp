#include "PlayerShip.h"

PlayerShip::PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Ship(scene, engine, view) {
  std::vector<b2Vec2> ship_crds = { {0, 0}, {.1, .1}, {0.2,0.025}, {.3333,.1}, {.3333,.2}, {.2,.275}, {.1,.2}, {0,.3333} };
  b2PolygonShape* polyshape = new b2PolygonShape;
  polyshape->Set(ship_crds.data(), ship_crds.size());

  _body = engine->createBody(b2_dynamicBody, 2, 5, 0, false);
  _body->SetFixedRotation(true);
  b2Fixture* fixture = engine->createFixture(_body, polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x1;
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
  _pi = _scene->addPolygon(polygon, p);
  _pi->setData(0, QVariant::fromValue((void *)_body));
  _pi->setPos(_body->GetPosition().x, _body->GetPosition().y);
}

bool PlayerShip::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    switch (keyEvent->key()) {
    case Qt::Key_Left:
      _body->ApplyForceToCenter(b2Vec2(-1., 0), true);
      break;
    case Qt::Key_Right:
      _body->ApplyForceToCenter(b2Vec2(1., 0), true);
      break;
    case Qt::Key_Up:
      _body->ApplyForceToCenter(b2Vec2(0, -1.), true);
      break;
    case Qt::Key_Down:
      _body->ApplyForceToCenter(b2Vec2(0, 1.), true);
      break;
    }
  } else {
    // standard event processing
    return QObject::eventFilter(obj, event);
  }
  return true;
}

void PlayerShip::update() {
  // Apply drag
  // drag coefficient
  float Cd = 0.05f;
  b2Vec2 lv = _body->GetLinearVelocity();
  float v = lv.x * lv.x;
  float dragForce = 0.5f * v * Cd;
  float dragAngle = atan2f(lv.y, lv.x) + M_PI/2.f;
  b2Vec2 appliedDrag(-sinf(dragAngle)*dragForce, 0.);
  _body->ApplyForceToCenter(appliedDrag, true);

  _pi->setPos(_body->GetPosition().x, _body->GetPosition().y);
  // Would prefer to implement centering logic in QWorldView
  _view->centerOn(_pi->x(), _view->height()/2);
}
