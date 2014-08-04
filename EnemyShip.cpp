#include "EnemyShip.h"
#include "qglobal.h"

// todo(dek): keep moving code into Ship constructor


EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): 
  PolygonItem(
       QPolygonF({ { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} }), 
       QPen(Qt::white),
       QBrush(Qt::red, Qt::SolidPattern),
       QPointF((float)qrand()/RAND_MAX*40., (float)qrand()/RAND_MAX*10.),
       0x2, 0xffff,
       scene, engine, view) {

  b2Vec2 force((float)qrand()/RAND_MAX, (float)qrand()/RAND_MAX);
  _body->ApplyForceToCenter(force, true);
}
