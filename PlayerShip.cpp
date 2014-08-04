#include "PlayerShip.h"
#include "MotionFilter.h"

// TODO(dek): can the declarative code be put in initializer list, then handled automagically by base class code?
PlayerShip::PlayerShip(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): 
  PolygonItem(
	      QPolygonF({ {0, 0}, {.1, .1}, {0.2,0.025}, {.3333,.1}, {.3333,.2}, {.2,.275}, {.1,.2}, {0,.3333} }), 
	      QPen(Qt::white),
	      QBrush(Qt::white, Qt::SolidPattern),
	      QPointF(2.,5.),
	      0x1, 0xffff,
	      scene, engine, view) {

  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(this);
  // scene event filter required to get mouse events
  _scene->installEventFilter(scene_motion_filter);
  _view->installEventFilter(this);

  connect(engine, &QtBox2DEngine::step, this, &PlayerShip::centerView);
  connect(engine, &QtBox2DEngine::step, this, &PlayerShip::updateDrag);
#ifdef __ANDROID_API__
  ts.start();
  connect(engine, &QtBox2DEngine::step, this, &PlayerShip::updateTitle);
#endif
}

bool PlayerShip::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    switch (keyEvent->key()) {
    case Qt::Key_Left:
      _body->ApplyForceToCenter(b2Vec2(-1., 0), true);
      break;
    case Qt::Key_Right:
      _body->ApplyForceToCenter(b2Vec2(1., 0), true);
      break;
    case Qt::Key_Up:
      _body->ApplyForceToCenter(b2Vec2(0, -1.), true);
      break;
    case Qt::Key_Down:
      _body->ApplyForceToCenter(b2Vec2(0, 1.), true);
      break;
    }
  } else {
    // standard event processing
    return QObject::eventFilter(obj, event);
  }
  return true;
}

void PlayerShip::centerView() {
  _view->centerOn(_it->x(), _view->height()/2);
}

void PlayerShip::updateDrag() {

  // Apply drag
  // drag coefficient
  float Cd = 0.05f;
  b2Vec2 lv = _body->GetLinearVelocity();
  float v = lv.x * lv.x;
  float dragForce = 0.5f * v * Cd;
  float dragAngle = atan2f(lv.y, lv.x) + M_PI/2.f;
  b2Vec2 appliedDrag(-sinf(dragAngle)*dragForce, 0.);
  _body->ApplyForceToCenter(appliedDrag, true);
}

void PlayerShip::updateTilt() {
   b2Vec2 tilt(ts.reading()->xRotation()/360. * 10., -ts.reading()->yRotation()/360.);
  _body->ApplyForceToCenter(tilt, true);
}
