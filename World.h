#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsView>
#include "box2dengine.h"
#include "Cave.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Diamond.h"
#include "MyContactListener.h"
#include <QObject>
#include "QtSensors/QTiltSensor"

class World: public QObject {
  Q_OBJECT
public:
  World(QGraphicsScene* _scene,
	QGraphicsView* _view);
  void Start();
  void centerViewOnPlayer();
  bool eventFilter(QObject *obj, QEvent *event);
private slots:
  void updateDrag();
  void updateTilt();
private:
  QGraphicsScene* _scene;
  QGraphicsView* _view;
  QtBox2DEngine* _engine;
  MyContactListener* _myContactListener;
  Cave* _cave;
  PlayerShip* _player_ship;
private:
  QTiltSensor ts;
};
