#include "World.h"

std::vector<int> stalagtites{0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1,0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1};
std::vector<int> stalagmites{0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1,0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1};

void addLine(b2Body* body, QGraphicsScene *scene, QtBox2DEngine* engine, double x1, double y1, double x2, double y2) {
    QPen p(Qt::white);
    p.setWidth(0);
    scene->addLine(QLineF(x1, y1, x2, y2), p);
    b2EdgeShape *edge = new b2EdgeShape;
    edge->Set(b2Vec2(x1,-y1), b2Vec2(x2,-y2));
    b2Fixture* fixture = engine->createFixture(body, edge);
    fixture->SetRestitution(1);
    fixture->SetFriction(0);
}

void addChain(b2Body* body, QGraphicsScene *scene, QtBox2DEngine* engine, const QList<QPointF>& points) {
  QPen p(Qt::white);
  p.setWidth(0);

  b2Vec2* vertices = new b2Vec2[points.size()-1];
  for (int i=0; i < points.size()-1; ++i) {

    scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(), p);

    vertices[i] = b2Vec2(points[i].x(), -points[i].y());
  }
  b2ChainShape *chain = new b2ChainShape;
  chain->CreateChain(vertices, points.size()-1);
  b2Fixture* fixture = engine->createFixture(body, chain);\
  fixture->SetRestitution(1);
  fixture->SetFriction(0);
}

World::World(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): _scene(scene), _engine(engine), _view(view) {
  b2Body* stalagtites_body = engine->createBody(b2_staticBody, 0, 0, 0, false);
  {
    QList<QPointF> points;
    for (unsigned int i = 0; i < stalagtites.size(); ++i)
      points.push_back(QPointF(i,stalagtites[i]));
    addChain(stalagtites_body, scene, engine,  points);
  }

  b2Body* stalagmites_body = engine->createBody(b2_staticBody, 0, 0, 0, false);
  {
    QList<QPointF> points;
    for (unsigned int i = 0; i < stalagmites.size(); ++i)
      points.push_back(QPointF(i,10.-stalagmites[i]));
    addChain(stalagmites_body, scene, engine,  points);
  }
  addLine(stalagtites_body, scene, engine,0,0,0,10);
  addLine(stalagtites_body, scene, engine,stalagtites.size()-1,0,stalagtites.size()-1,10);

}
