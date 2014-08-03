#include "Item.h"
Item::Item(QGraphicsScene* scene, QtBox2DEngine* engine, QGraphicsView* view): _scene(scene), _engine(engine), _view(view) {
  connect(_engine, &QtBox2DEngine::step, this, &Item::updatePosition);
}

b2Body* Item::Body() { return _body; }
QGraphicsItem* Item::GraphicsItem() { return _it; }

bool Item::eventFilter(QObject *obj, QEvent *event) {
  // standard event processing
  return QObject::eventFilter(obj, event);
}

void Item::updatePosition() {
  _it->setPos(_body->GetPosition().x, _body->GetPosition().y);
}
