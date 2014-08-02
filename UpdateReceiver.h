#ifndef UPDATERECEIVER_H
#define UPDATERECEIVER_H
#include <iostream>
#include <QtCore/QObject>
#include <QtWidgets/QGraphicsPolygonItem>
#include "box2dengine.h"
#include <QtWidgets/QGraphicsView>
#include <math.h>

class UpdateReceiver : public QObject {
  Q_OBJECT
  public:
  UpdateReceiver(QGraphicsView* view, QGraphicsPolygonItem* pi, b2Body* ship_body): _view(view), _pi(pi), _ship_body(ship_body) {
  }


public slots:
  void update() {
    _pi->setPos(_ship_body->GetPosition().x, -_ship_body->GetPosition().y);
    _view->centerOn(_pi->x(), _view->height()/2);

    // a very sleek object
    float Cd = 0.05f;
    b2Vec2 lv = _ship_body->GetLinearVelocity();
    float v = lv.x * lv.x;
    float dragForce = 0.5f * v * Cd;
    float dragAngle = atan2f(lv.y, lv.x) + M_PI/2.f;
    b2Vec2 appliedDrag(-sinf(dragAngle)*dragForce, 0.);
    _ship_body->ApplyForceToCenter(appliedDrag, true);
  }

private:
  QGraphicsView* _view;
  QGraphicsPolygonItem* _pi;
  b2Body* _ship_body;
};

#endif // UPDATERECEIVER_H
