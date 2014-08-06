#include <iostream>
#include <math.h>
#include <cstdlib>
#include "Diamond.h"
#include <qglobal.h>
#include "Box2D/Box2D.h"


Diamond::Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, Cave* cave):
  PolygonItem::PolygonItem(
			   QPolygonF({ {0, 0},{.1,-.1},{.2,0,},{.1,.1} }),
			   QPen(Qt::white),
			   QBrush(Qt::yellow, Qt::SolidPattern),
			   QPointF(0,0),
			   0x4, 0xffff,
			   scene, engine) {
 while (true) {
   float x = (float)qrand()/RAND_MAX*40.;
   float y = (float)qrand()/RAND_MAX*10.;
   if (cave->isBelowStalagtite(x, y) && cave->isAboveStalagmite(x, y)) {
     GetBody()->SetTransform(b2Vec2(x, y), GetBody()->GetAngle());
     break;
   }
 }
}
