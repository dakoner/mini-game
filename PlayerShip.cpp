#include "PlayerShip.h"
#include "MotionFilter.h"


PlayerShip::PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine): 
  PolygonItem(
	      QPolygonF({ {0, 0}, {.1, .1}, {0.2,0.025}, {.3333,.1}, {.3333,.2}, {.2,.275}, {.1,.2}, {0,.3333} }), 
	      QPen(Qt::white),
	      QBrush(Qt::white, Qt::SolidPattern),
	      QPointF(2.,5.),
	      0x1, 0xffff,
	      scene, engine) { }


