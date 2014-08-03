#include <iostream>
#include "QtGui/QtGui"
#include <Box2D/Box2D.h>
#include "box2dengine.h"
#include "qworldview.h"

class MyContactListener: public QObject, public b2ContactListener {
  Q_OBJECT
public:
  MyContactListener(QtBox2DEngine* engine, QWorldView* view): _engine(engine), _view(view) {
    connect(_engine, &QtBox2DEngine::step, this, &MyContactListener::update);
  }
  void BeginContact(b2Contact* contact) {
    uint16 cbA = contact->GetFixtureA()->GetFilterData().categoryBits;
    uint16 cbB = contact->GetFixtureB()->GetFilterData().categoryBits;
    std::cout << cbA << " " << cbB << std::endl;
    if (cbA == 0x1 && cbB == 0x4) {
      if (_view->_diamonds.find((Diamond*)contact->GetFixtureB()->GetUserData()) == _view->_diamonds.end()) {
	std::cout << "diamond not found" << std::endl;
      } else {
	_fixtures_to_destroy.insert(contact->GetFixtureB());
      }
    }
  }
private slots:
  void update() {
    for(auto& item : _fixtures_to_destroy) {
      Diamond*  d = (Diamond*)item->GetUserData();
      _view->_diamonds.erase(d);
      delete d;
      item->GetBody()->DestroyFixture(item);
    }
    _fixtures_to_destroy.clear();
  }
private:
  QtBox2DEngine* _engine;
  QWorldView* _view;
  std::set<b2Fixture*> _fixtures_to_destroy;
};

