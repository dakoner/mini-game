#ifndef MOTIONFILTER_H
#define MOTIONFILTER_H
#include <iostream>

#include <QtWidgets/QGraphicsPolygonItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QScrollBar>
#include <set>
#include "box2dengine.h"

class SceneMotionFilter : public QObject
{
    Q_OBJECT

public:
    SceneMotionFilter(b2Body *ship_body):
        _ship_body(ship_body) { }

protected:
    bool eventFilter(QObject *obj, QEvent *event) {
        if (event->type() == QEvent::GraphicsSceneMouseMove) {
            QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            QPointF pos = mouseEvent->scenePos();
            b2Vec2 sp = _ship_body->GetPosition();
            b2Vec2 mp(pos.x(), -pos.y());
            mp -= sp;
            mp *= 0.02;
            _ship_body->ApplyForceToCenter(mp, true);
            return true;
        }
        return QObject::eventFilter(obj, event);
    }

private:
    b2Body* _ship_body;
};


class MotionFilter : public QObject
{
    Q_OBJECT

public:
    MotionFilter(b2Body *ship_body):
        _ship_body(ship_body) { }

protected:
    bool eventFilter(QObject *obj, QEvent *event) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            switch (keyEvent->key()) {
            case Qt::Key_Left:
                _ship_body->ApplyForceToCenter(b2Vec2(-1., 0), true);
                break;
            case Qt::Key_Right:
                _ship_body->ApplyForceToCenter(b2Vec2(1., 0), true);
                break;
            case Qt::Key_Up:
                _ship_body->ApplyForceToCenter(b2Vec2(0, 1.), true);
                break;
            case Qt::Key_Down:
                _ship_body->ApplyForceToCenter(b2Vec2(0, -1.), true);
                break;
            }
        } else {
            // standard event processing
            return QObject::eventFilter(obj, event);
        }
        return true;
    }

private:
    b2Body* _ship_body;
};

#endif // MOTIONFILTER_H
