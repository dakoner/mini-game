#include "World.h"

World::World(QGraphicsScene* scene, QGraphicsView* view):
  _scene(scene),
  _view(view),
  _engine(new QtBox2DEngine),
  _myContactListener(new MyContactListener(_engine, _view)),
  _cave(new Cave(_scene, _engine, _view)),
  _player_ship(new PlayerShip(_scene, _engine, _view)) {

  for (int i = 0; i < 10; ++i) {
    new EnemyShip(_scene, _engine, _view, _cave);
  }
  for (int i = 0; i < 30; ++i) {
    new Diamond(_scene, _engine, _view, _cave);
  }

  _engine->setContactListener(_myContactListener);
  _engine->setGravity(0);
  _engine->setInterval(60);
}

void World::Start() {
  _engine->start();
}
