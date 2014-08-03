#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "Item.h"

class Diamond: public Item
{
  Q_OBJECT

public:
  Diamond(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view);
};

#endif
