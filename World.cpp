#include <QList>
#include <QGraphicsItemGroup>
#include <iostream>
#include "World.h"

std::vector<int> stalagtites{0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1,0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1};
std::vector<int> stalagmites{0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1,0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1};

World::World(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): Item(scene, engine, view) {
  _body = _engine->createBody(b2_staticBody, 0, 0, 0, false);
  QList<QGraphicsItem*> items;
  {
    QList<QPointF> points;
    for (unsigned int i = 0; i < stalagtites.size(); ++i)
      points.push_back(QPointF(i,stalagtites[i]));
    addChain(points, &items);
  }

  {
    QList<QPointF> points;
    for (unsigned int i = 0; i < stalagmites.size(); ++i)
      points.push_back(QPointF(i,10-stalagmites[i]));
    addChain(points, &items);
  }
  addLine(0,0,0,10, &items);
  addLine(stalagtites.size()-1,0,stalagtites.size()-1,10, &items);
  _it = _scene->createItemGroup(items);
}

void World::addLine(double x1, double y1, double x2, double y2, QList<QGraphicsItem*>* items) {
  QPen p(Qt::white);
  p.setWidth(0);
  items->append(_scene->addLine(QLineF(x1, y1, x2, y2), p));
  b2EdgeShape *edge = new b2EdgeShape;
  edge->Set(b2Vec2(x1,y1), b2Vec2(x2,y2));
  b2Fixture* fixture = _engine->createFixture(_body, edge);
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x8;
  b.maskBits = 0xffff;
  fixture->SetFilterData(b);
}

void World::addChain(const QList<QPointF>& points, QList<QGraphicsItem*>* items) {
  QPen p(Qt::white);
  p.setWidth(0);

  b2Vec2* vertices = new b2Vec2[points.size()];
  for (int i=0; i < points.size()-1; ++i) {

    items->append(_scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(), p));
    vertices[i] = b2Vec2(points[i].x(), points[i].y());
  }
  vertices[points.size()-1] = b2Vec2(points[points.size()-1].x(), points[points.size()-1].y());

  b2ChainShape *chain = new b2ChainShape;
  chain->CreateChain(vertices, points.size());
  b2Fixture* fixture = _engine->createFixture(_body, chain);\
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
  b2Filter b;
  b.categoryBits = 0x8;
  b.maskBits = 0xffff;
  fixture->SetFilterData(b);
}
