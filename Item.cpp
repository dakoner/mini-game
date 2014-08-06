#include <iostream>
#include "Item.h"

Item::Item(QGraphicsScene* scene, QtBox2DEngine* engine): _scene(scene),
							  _engine(engine) {
  connect(_engine, &QtBox2DEngine::step, this, &Item::updatePosition);
}

b2Body* Item::GetBody() { return _body; }
QGraphicsItem* Item::GetGraphicsItem() { return _it.get(); }

bool Item::eventFilter(QObject *obj, QEvent *event) {
  // standard event processing
  return QObject::eventFilter(obj, event);
}

void Item::updatePosition() {
  if (!_it.get()) {
    std::cerr << "updatePosition called on invalid item." << std::endl;
  } else 
    _it->setPos(_body->GetPosition().x, _body->GetPosition().y);
}
