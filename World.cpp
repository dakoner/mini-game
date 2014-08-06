#include "World.h"

World::World(QGraphicsScene* scene, QGraphicsView* view):
  _scene(scene),
  _view(view),
  _engine(new QtBox2DEngine),
  _myContactListener(new MyContactListener(_engine, _view)),
  _cave(new Cave(_scene, _engine)),
  _player_ship(new PlayerShip(_scene, _engine)) {
  _view->installEventFilter(_player_ship);

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
}

void World::Start() {
  _engine->start();
}

void World::centerViewOnPlayer() {
  _view->centerOn(_player_ship->GetBody()->GetPosition().x, _view->height()/2);
}
