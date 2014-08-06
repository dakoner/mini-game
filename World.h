#include <QGraphicsScene>
#include <QGraphicsView>
#include "box2dengine.h"
#include "Cave.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Diamond.h"
#include "MyContactListener.h"

class World {
public:
  World(QGraphicsScene* _scene,
	QGraphicsView* _view);
  void Start();
private:
  QGraphicsScene* _scene;
  QGraphicsView* _view;
  QtBox2DEngine* _engine;
  MyContactListener* _myContactListener;
  Cave* _cave;
  PlayerShip* _player_ship;
};
