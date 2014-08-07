#include "EnemyShip.h"
#include "qglobal.h"

EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, Cave* cave): 
  PolygonItem(
       QPolygonF({ { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} }), 
       QPen(Qt::white),
       QBrush(Qt::red, Qt::SolidPattern),
       QPointF(0, 0),
       0x2, 0xffff,
       scene, engine) {

  GetBody()->SetTransform(cave->GeneratePointInside(), GetBody()->GetAngle());

  b2Vec2 force((float)qrand()/RAND_MAX, (float)qrand()/RAND_MAX);
  _body->ApplyForceToCenter(force, true);
}
