#include <cstdlib>
#include "Diamond.h"
#include <qglobal.h>

Diamond::Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): _scene(scene), _engine(engine), _view(view) {
  std::vector<b2Vec2> ship_crds = { {.1,.2},{.2,.1},{.3,.2,},{.2,.3} };
  b2PolygonShape* polyshape = new b2PolygonShape;
  polyshape->Set(ship_crds.data(), ship_crds.size());

  _body = engine->createBody(b2_dynamicBody, (float)qrand()/RAND_MAX*40., (float)-qrand()/RAND_MAX*10., 0, false);
  _body->SetFixedRotation(true);
  b2Fixture* fixture = engine->createFixture(_body, polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);

  QVector<QPointF> polygon_crds = { {.1,-.2},{.2,-.1},{.3,-.2,},{.2,-.3} };
  QPolygonF polygon(polygon_crds);
  QPen p(Qt::white);
  p.setWidth(0);
  _pi = _scene->addPolygon(polygon, p);
  _pi->setData(0, QVariant::fromValue((void *)_body));
  _pi->setPos(_body->GetPosition().x, -_body->GetPosition().y);
}
