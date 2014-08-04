#include "PolygonItem.h"

PolygonItem::PolygonItem(QPolygonF polygon, QPen p, QBrush br, QPointF point, uint16 categoryBits, uint16 maskBits, QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Item(scene, engine, view) {
  p.setWidth(0);
  _it.reset(scene->addPolygon(polygon, p, br));
  std::vector<b2Vec2> ship_crds;
  for (auto item : polygon) {
    ship_crds.push_back(b2Vec2(item.x(), item.y()));
  }
  _polyshape = new b2PolygonShape;
  _polyshape->Set(ship_crds.data(), ship_crds.size());
  _body = engine->createBody(b2_dynamicBody, point.x(), point.y(), 0, false);
  _body->SetFixedRotation(true);

  b2Filter filter;
  filter.categoryBits = categoryBits;
  filter.maskBits = maskBits;
  _fixture = engine->createFixture(_body, _polyshape);
  _fixture->SetRestitution(1);
  _fixture->SetFriction(0);
  _fixture->SetFilterData(filter);
  _fixture->SetUserData(this);
}
