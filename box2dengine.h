#ifndef BOX2DENGINE_H
#define BOX2DENGINE_H

#include <QtCore/QObject>
#include <Box2D/Box2D.h>

class b2Fixture;

class QtBox2DQueryCallback : public QObject, public b2QueryCallback
{
    Q_OBJECT

public:
    explicit QtBox2DQueryCallback(QObject *parent = 0);
    explicit QtBox2DQueryCallback(b2BodyType type, QObject *parent = 0);
    bool ReportFixture(b2Fixture *fixture);
    inline void setTerminate(bool terminate) { m_repeat = !terminate; }

signals:
    void bodyFound(b2Body *body);

private:
    b2BodyType m_type;
    bool       m_repeat;
    bool       m_filter;
};

class QPointF;
class b2World;
class b2BodyDef;
class b2JointDef;

typedef void (b2Fixture::*FixtureMember)(float32);

class QtBox2DEngine : public QObject
{
    Q_OBJECT

public:
    explicit QtBox2DEngine(QObject *parent = 0);
    virtual ~QtBox2DEngine();

    b2Body *createBody(const b2BodyDef *definition) const;
    b2Body *createBody(b2BodyType type, qreal x = 0, qreal y = 0, qreal angle = 0, bool bullet = false) const;
    void destroyBody(b2Body *body);

    b2Body *bodies() const;
    QList<b2Body *> bodyList() const;

    inline bool worldLocked() const { return m_world->IsLocked(); }

    b2Fixture *createFixture(b2Body *body, const b2Shape *shape, qreal density = 1, qreal friction = 0.5) const;
    b2Fixture *createSensor(b2Body *body, const b2Shape *shape) const;

    b2Joint *createJoint(const b2JointDef *definition) const;
    void destroyJoint(b2Joint *joint);

    void query(QtBox2DQueryCallback *callback, const QPointF &p1, const QPointF &p2);

    void setFriction(b2Body *body, qreal friction) const;
    void setDensity(b2Body *body, qreal density) const;
    void setRestitution(b2Body *body, qreal restitution) const;

    inline void setContactListener(b2ContactListener *listener) { m_world->SetContactListener(listener); }

public slots:
    void start();
    void stop();

    void setInterval(double hertz);
    void setTimestepRatio(double ratio);
    void setGravity(float32 x, float32 y);
    void setGravity(float32 g);

    inline void setVelocityIterations(int i) { m_velocityIter = i; }
    inline void setPositionIterations(int i) { m_positionIter = i; }

signals:
    void step();

protected:
    void timerEvent(QTimerEvent *event);

private:
    void assignFixtureProperty(b2Body *body, const FixtureMember &member, qreal arg) const;

    int      m_timer;
    bool     m_running;
    qreal    m_hertz;
    int      m_velocityIter;
    int      m_positionIter;
    qreal    m_step;
    b2World *const m_world;
};

#endif // BOX2DENGINE_H

