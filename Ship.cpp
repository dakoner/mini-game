#include "Ship.h"
Ship::Ship(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): _scene(scene), _engine(engine), _view(view) {
  connect(_engine, SIGNAL(step()), this, SLOT(update()));
}

b2Body* Ship::Body() { return _body; }

bool Ship::eventFilter(QObject *obj, QEvent *event) {
  // standard event processing
  return QObject::eventFilter(obj, event);
}

