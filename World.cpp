#include "World.h"
#include "MotionFilter.h"

World::World(QGraphicsScene* scene, QGraphicsView* view):
  _scene(scene),
  _view(view),
  _engine(new QtBox2DEngine),
  _myContactListener(new MyContactListener(_engine, _view)),
  _cave(new Cave(_scene, _engine)),
  _player_ship(new PlayerShip(_scene, _engine)) {


  // Detect user/scene input
  SceneMotionFilter* scene_motion_filter = new SceneMotionFilter(_player_ship);
  // scene event filter required to get mouse events
  _scene->installEventFilter(scene_motion_filter);
  _view->installEventFilter(this);


  for (int i = 0; i < 10; ++i) {
    new EnemyShip(_scene, _engine, _cave);
  }
  for (int i = 0; i < 30; ++i) {
    new Diamond(_scene, _engine, _cave);
  }

  _engine->setContactListener(_myContactListener);
  _engine->setGravity(0);
  _engine->setInterval(60);

  connect(_engine, &QtBox2DEngine::step, this, &World::centerViewOnPlayer);
  connect(_engine, &QtBox2DEngine::step, this, &World::updateDrag);
#ifdef __ANDROID_API__
  ts.start();
  connect(_engine, &QtBox2DEngine::step, this, &World::updateTitle);
#endif
}

void World::Start() {
  _engine->start();
}

void World::centerViewOnPlayer() {
  _view->centerOn(_player_ship->GetBody()->GetPosition().x, _view->height()/2);
}

// TODO(dek): move event filter to World
bool World::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    switch (keyEvent->key()) {
    case Qt::Key_Left:
      _player_ship->GetBody()->ApplyForceToCenter(b2Vec2(-1., 0), true);
      break;
    case Qt::Key_Right:
      _player_ship->GetBody()->ApplyForceToCenter(b2Vec2(1., 0), true);
      break;
    case Qt::Key_Up:
      _player_ship->GetBody()->ApplyForceToCenter(b2Vec2(0, -1.), true);
      break;
    case Qt::Key_Down:
      _player_ship->GetBody()->ApplyForceToCenter(b2Vec2(0, 1.), true);
      break;
    }
  } else {
    // standard event processing
    return QObject::eventFilter(obj, event);
  }
  return true;
}


void World::updateDrag() {

  // Apply drag
  // drag coefficient
  float Cd = 0.05f;
  b2Vec2 lv = _player_ship->GetBody()->GetLinearVelocity();
  float v = lv.x * lv.x;
  float dragForce = 0.5f * v * Cd;
  float dragAngle = atan2f(lv.y, lv.x) + M_PI/2.f;
  b2Vec2 appliedDrag(-sinf(dragAngle)*dragForce, 0.);
  _player_ship->GetBody()->ApplyForceToCenter(appliedDrag, true);
}

void World::updateTilt() {
   b2Vec2 tilt(ts.reading()->xRotation()/360. * 10., -ts.reading()->yRotation()/360.);
  _player_ship->GetBody()->ApplyForceToCenter(tilt, true);
}
