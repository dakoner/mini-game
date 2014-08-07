#include <QPolygonF>
#include <QGraphicsItemGroup>
#include <iostream>
#include "Cave.h"


Cave::Cave(QGraphicsScene* scene, QtBox2DEngine* engine): 
  Item(scene, engine),
  _stalagtites{0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1,0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1}, 
  _stalagmites{0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1,0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1} {
    _body = _engine->createBody(b2_staticBody, 0, 0, 0, false);
    QList<QGraphicsItem*> items;
    QPolygonF points;

    for (unsigned int i = 0; i < _stalagtites.size(); ++i)
      points.push_back(QPointF(i,_stalagtites[i]));
    // Add stalagmites in reverse order to maintain polygon winding.
    for (unsigned int i = _stalagmites.size(); i > 0; --i)
      points.push_back(QPointF(i-1,10-_stalagmites[i-1]));
    // Add the first point, so we create a loop
    points.push_back(QPointF(0,_stalagtites[0]));
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

b2Vec2 Cave::GeneratePointInside() {
  // make this code a method of Cave?
  while (true) {
    float x = (float)qrand()/RAND_MAX*40.;
    float y = (float)qrand()/RAND_MAX*10.;
    if (isBelowStalagtite(x, y) && isAboveStalagmite(x, y)) {
      return b2Vec2(x, y);
    }
  }
}

bool Cave::isBelowStalagtite(float x, float y) {
  
  int x_index = floor(x);
  if (x < _stalagtites.size()-1) {
    int y0 = _stalagtites[x_index];
    int y1 = _stalagtites[x_index+1];
    b2Vec2 A = b2Vec2(x_index, y0+1);
    b2Vec2 B = b2Vec2(x_index+1, y1+1);
    b2Vec2 pos = b2Vec2(x,y);
    bool b = ( (B.x-A.x)*(pos.y-A.y) - (B.y-A.y)*(pos.x-A.x) ) > 0;
    return  b;
  }
  return false;
};

bool Cave::isAboveStalagmite(float x, float y) {
  
  int x_index = floor(x);
  if (x < _stalagmites.size()-1) {
    int y0 = _stalagmites[x_index];
    int y1 = _stalagmites[x_index+1];
    b2Vec2 A = b2Vec2(x_index, 10-y0-1);
    b2Vec2 B = b2Vec2(x_index+1, 10-y1-1);
    b2Vec2 pos = b2Vec2(x,y);
    bool b = ( (B.x-A.x)*(pos.y-A.y) - (B.y-A.y)*(pos.x-A.x) ) < 0;
    return  b;
  }
  return false;
};
