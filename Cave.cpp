#include <QPolygonF>
#include <QGraphicsItemGroup>
#include <iostream>
#include "Cave.h"

std::vector<int> stalagtites{0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1,0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1};
std::vector<int> stalagmites{0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1,0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1};

Cave::Cave(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Item(scene, engine, view) {
  _body = _engine->createBody(b2_staticBody, 0, 0, 0, false);
  QList<QGraphicsItem*> items;
  QPolygonF points;

  for (unsigned int i = 0; i < stalagtites.size(); ++i)
    points.push_back(QPointF(i,stalagtites[i]));
  // Add stalagmites in reverse order to maintain polygon winding.
  for (unsigned int i = stalagmites.size(); i > 0; --i)
    points.push_back(QPointF(i-1,10-stalagmites[i-1]));
  // Add the first point, so we create a loop
  points.push_back(QPointF(0,stalagtites[0]));
  QPen p(Qt::white);
  p.setWidth(0);
  _it.reset(_scene->addPolygon(points, p));

  std::vector<b2Vec2> vertices;
  for (auto item : points) {
    vertices.push_back(b2Vec2(item.x(), item.y()));
  }

  b2ChainShape *chain = new b2ChainShape;
  chain->CreateChain(vertices.data(), vertices.size());
  b2Fixture* fixture = _engine->createFixture(_body, chain);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x8;
  b.maskBits = 0xffff;
  fixture->SetFilterData(b);

}
