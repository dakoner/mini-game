#include <cstdlib>
#include "Diamond.h"
#include <qglobal.h>

Diamond::Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): 
  PolygonItem(
	      QPolygonF({ {0, 0},{.1,-.1},{.2,0,},{.1,.1} }),
	      QPen(Qt::white),
	      QBrush(Qt::yellow, Qt::SolidPattern),
	      QPointF((float)qrand()/RAND_MAX*40.,
		      (float)qrand()/RAND_MAX*10.),
	      0x4, 0xffff,
	      scene, engine, view) {
}
