#include <iostream>
#include <set>
#include <Box2D/Box2D.h>
#include "box2dengine.h"
#include <QGraphicsView>
#include "Item.h"


class MyContactListener: public QObject, public b2ContactListener {
  Q_OBJECT
public:
  MyContactListener(QtBox2DEngine* engine, QGraphicsView* view): _engine(engine), _view(view) {
    connect(_engine, &QtBox2DEngine::step, this, &MyContactListener::update);
  }
  void BeginContact(b2Contact* contact) {
    uint16 cbA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 cbB = contact->GetFixtureB()->GetFilterData().categoryBits;
    // PlayerShip<->diamond collision
    if (cbA == 0x1 && cbB == 0x4) {
      _fixtures_to_destroy.insert(contact->GetFixtureB());
    }
    if (cbA == 0x4 && cbB == 0x1) {
      _fixtures_to_destroy.insert(contact->GetFixtureA());
    }
    // EnemyShip<->diamond collision
    if (cbA == 0x2 && cbB == 0x4) {
      _fixtures_to_destroy.insert(contact->GetFixtureA());
    }
    if (cbA == 0x4 && cbB == 0x2) {
      _fixtures_to_destroy.insert(contact->GetFixtureB());
    }
  }
private slots:
  void update() {
    for(auto& fixture : _fixtures_to_destroy) {
      Item* i = (Item*)fixture->GetUserData();
      delete i;
      _engine->destroyBody(fixture->GetBody());
    }
    _fixtures_to_destroy.clear();
  }
private:
  QtBox2DEngine* _engine;
  QGraphicsView* _view;
  std::set<b2Fixture*> _fixtures_to_destroy;
};

