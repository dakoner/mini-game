#ifndef MOTIONFILTER_H
#define MOTIONFILTER_H
#include <iostream>

#include <QtWidgets/QGraphicsPolygonItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QScrollBar>
#include <set>
#include "box2dengine.h"
#include "PlayerShip.h"

// Would prefer to not require this class at all, but it seems
// required for handling scene-level mouse and touch events properly.

class SceneMotionFilter : public QObject
{
  Q_OBJECT

  public:
  SceneMotionFilter(PlayerShip *ship):
  _ship(ship) { }

protected:
  bool eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::GraphicsSceneMouseMove) {
      QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
      QPointF pos = mouseEvent->scenePos();
      b2Vec2 sp = _ship->GetBody()->GetPosition();
      b2Vec2 mp(pos.x(), pos.y());
      mp -= sp;
      mp *= 0.02;
      _ship->GetBody()->ApplyForceToCenter(mp, true);
      return true;
    }
    return QObject::eventFilter(obj, event);
  }

private:
  PlayerShip* _ship;
};

#endif // MOTIONFILTER_H
