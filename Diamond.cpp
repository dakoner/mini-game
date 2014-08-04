#include <cstdlib>
#include "Diamond.h"
#include <qglobal.h>

Diamond::Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Item(scene, engine, view) {
  QPolygonF polygon({ {0, 0},{.1,-.1},{.2,0,},{.1,.1} });
  QPen p(Qt::white);
  QBrush br(Qt::yellow, Qt::SolidPattern);
  p.setWidth(0);
  _it = _scene->addPolygon(polygon, p, br);

  std::vector<b2Vec2> ship_crds;
  for(auto& item : polygon) {
    ship_crds.push_back(b2Vec2(item.x(), item.y()));
  }

  b2PolygonShape* polyshape = new b2PolygonShape;
  polyshape->Set(ship_crds.data(), ship_crds.size());

  qreal x = (float)qrand()/RAND_MAX*40;
  qreal y = (float)qrand()/RAND_MAX*10;
  _body = engine->createBody(b2_dynamicBody, x, y, 0, false);
  _body->SetFixedRotation(true);

  b2Fixture* fixture = engine->createFixture(_body, polyshape);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x4;
  b.maskBits = 0xffff;
  fixture->SetFilterData(b);
  fixture->SetUserData(this);
}
