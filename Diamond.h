#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "PolygonItem.h"

class Diamond: public PolygonItem
{
  Q_OBJECT

public:
  Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
};

#endif
