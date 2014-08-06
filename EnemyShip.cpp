#include "EnemyShip.h"
#include "qglobal.h"

// todo(dek): keep moving code into Ship constructor


EnemyShip::EnemyShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view, Cave* cave): 
  PolygonItem(
       QPolygonF({ { 1./10., 0. }, {3./10., 0.}, {4./10.,1./10.}, {3./10.,2./10.}, {1./10.,2./10.}, {0.,1./10.} }), 
       QPen(Qt::white),
       QBrush(Qt::red, Qt::SolidPattern),
       QPointF(0, 0),
       0x2, 0xffff,
       scene, engine, view) {

  while (true) {
    float x = (float)qrand()/RAND_MAX*40.;
    float y = (float)qrand()/RAND_MAX*10.;
    if (cave->isBelowStalagtite(x, y) && cave->isAboveStalagmite(x, y)) {
      GetBody()->SetTransform(b2Vec2(x, y), GetBody()->GetAngle());
      break;
    }
  }

  b2Vec2 force((float)qrand()/RAND_MAX, (float)qrand()/RAND_MAX);
  _body->ApplyForceToCenter(force, true);
}
