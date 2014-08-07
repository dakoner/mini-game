#ifndef _CAVE_H_
#define _CAVE_H_

#include <vector>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "Item.h"

#include "Box2D/Box2D.h"
#include "box2dengine.h"


class Cave: public Item
{
  Q_OBJECT

public:
  Cave(QGraphicsScene* scene, QtBox2DEngine* engine);

  bool isBelowStalagtite(float x, float y);
  bool isAboveStalagmite(float x, float y);
  b2Vec2 GeneratePointInside();

  std::vector<int> _stalagtites{0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1,0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1};
  std::vector<int> _stalagmites{0,0,0,0,2,2,2,2,2,3,3,4,4,3,0,0,0,0,0,1,0,0,0,0,1,1,2,2,1,1,1,3,1,0,0,1,4,0,0,1};
};

#endif
