#include <iostream>
#include <QtCore/QTimerEvent>
#include <QtCore/QPointF>
#include <Box2D/Box2D.h>
#include "box2dengine.h"

/*!
    \class QtBox2DQueryCallback

    \brief Box2D query callback. Emits the bodyFound() signal when
    a body is detected by the query.
 */

/*!
    Constructs a query callback object.
 */
QtBox2DQueryCallback::QtBox2DQueryCallback(QObject *parent)
    : QObject(parent),
      m_type(b2_staticBody),
      m_repeat(true),
      m_filter(false)
{
}

/*!
    Constructs a query callback object that only reports bodies of the type
    specified by \a type.
 */
QtBox2DQueryCallback::QtBox2DQueryCallback(b2BodyType type, QObject *parent)
    : QObject(parent),
      m_type(type),
      m_repeat(true),
      m_filter(true)
{
}

/*!
    \reimp
 */
bool QtBox2DQueryCallback::ReportFixture(b2Fixture *fixture)
{
    b2Body *body = fixture->GetBody();
    if (!m_filter || (m_filter && m_type == body->GetType())) {
        emit bodyFound(body);
        return m_repeat;
    }
    return true;
}

/*!
    \fn void QtBox2DQueryCallback::setTerminate(bool terminate)

    This property holds whether the query terminates when a body is found.
 */

/*!
    \class QtBox2DEngine

    \brief Main class for Box2D simulations. Essentially a QObject-based wrapper
    for the b2World class with a more Qt-friendly interface

    This class also has some added signals and slots and can be used together
    with QtBox2DWidget to visualize Box2D simulations.
 */

/*!
    Constructs a QtBox2DEngine.
 */
QtBox2DEngine::QtBox2DEngine(QObject *parent)
    : QObject(parent),
      m_timer(0),
      m_running(false),
      m_hertz(58),
      m_velocityIter(8),
      m_positionIter(3),
      m_step(5),
      m_world(new b2World(b2Vec2(0, -10)))
{
}

/*!
    Destroys the QtBox2DEngine object.
 */
QtBox2DEngine::~QtBox2DEngine()
{
    stop();
    delete m_world;
}

/*!
    Creates a world body using \a definition.
 */
b2Body *QtBox2DEngine::createBody(const b2BodyDef *definition) const
{
    return m_world->CreateBody(definition);
}

/*!
    Creates a body of b2BodyType \a type at position \a x, \a y.

    \overload
 */
b2Body *QtBox2DEngine::createBody(b2BodyType type, qreal x, qreal y, qreal angle, bool bullet) const
{
    b2BodyDef body;
    body.type = type;
    body.position.Set(x, y);
    body.angle = angle;
    body.bullet = bullet;
    return createBody(&body);
}

/*!
    Remove and destroy \a body.
 */
void QtBox2DEngine::destroyBody(b2Body *body)
{
    m_world->DestroyBody(body);
}

/*!
    Returns a pointer to the head of the world body list. Use b2Body::GetNext
    to get the next body in the list. See Box2D's documentation for more info.

    \sa QtBox2DEngine::bodylist()
 */
b2Body *QtBox2DEngine::bodies() const
{
    return m_world->GetBodyList();
}

/*!
    Returns a list of pointers to all bodies in the world.

    \sa QtBox2DEngine::bodies()
 */
QList<b2Body *> QtBox2DEngine::bodyList() const
{
    QList<b2Body *> list;
    b2Body *b = m_world->GetBodyList();
    while (b) {
        list.push_back(b);
        b = b->GetNext();
    }
    return list;
}

/*!
    \fn bool QtBox2DEngine::worldLocked() const

    Returns true if the world is locked, i.e., a time step is in progress.
 */

/*!
    Creates a fixture with \a shape and attaches it to \a body.
 */
b2Fixture *QtBox2DEngine::createFixture(b2Body *body, const b2Shape *shape, qreal density, qreal friction) const
{
    b2FixtureDef fixture;
    fixture.shape = shape;
    fixture.density = density;
    fixture.friction = friction;
    return body->CreateFixture(&fixture);
}

/*!
    Creates a sensor and attaches it to \a body. A sensor is a fixture that
    detects collision but does not produce a response.
 */
b2Fixture *QtBox2DEngine::createSensor(b2Body *body, const b2Shape *shape) const
{
    b2FixtureDef fixture;
    fixture.shape = shape;
    fixture.isSensor = true;
    return body->CreateFixture(&fixture);
}

/*!
    Creates a joint defined by \a definition. See Box2D's documentation for
    more info about joints.
 */
b2Joint *QtBox2DEngine::createJoint(const b2JointDef *definition) const
{
    return m_world->CreateJoint(definition);
}

/*!
    Destroys \a joint.
 */
void QtBox2DEngine::destroyJoint(b2Joint *joint)
{
    m_world->DestroyJoint(joint);
}

/*!
    Performs a log(N) time complexity region query to determine all the shapes
    between points \a p1 and \a p2, using \a callback to report when a body is
    found.

    \sa QtBox2DQueryCallback
 */
void QtBox2DEngine::query(QtBox2DQueryCallback *callback, const QPointF &p1, const QPointF &p2)
{
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(p1.x(), p1.y());
    aabb.upperBound = b2Vec2(p2.x(), p2.y());
    m_world->QueryAABB(callback, aabb);
}

/*!
    Set friction of all fixtures on \a body to \a friction.
 */
void QtBox2DEngine::setFriction(b2Body *body, qreal friction) const
{
    assignFixtureProperty(body, &b2Fixture::SetFriction, friction);
}

/*!
    Set density of all fixtures on \a body to \a density.
 */
void QtBox2DEngine::setDensity(b2Body *body, qreal density) const
{
    assignFixtureProperty(body, &b2Fixture::SetDensity, density);
}

/*!
    Set restitution of all fixtures on \a body to \a restitution.
 */
void QtBox2DEngine::setRestitution(b2Body *body, qreal restitution) const
{
    assignFixtureProperty(body, &b2Fixture::SetRestitution, restitution);
}

/*!
    \fn void QtBox2DEngine::setContactListener(b2ContactListener *listener)

    Assign a contact listener for this engine.

    \sa QtBox2DContactListener
 */

/*!
    Starts simulation.
 */
void QtBox2DEngine::start()
{
    if (!m_running) {
        m_running = true;
        setInterval(m_hertz);
    }
}

/*!
    Stops simulation.
 */
void QtBox2DEngine::stop()
{
    if (m_running) {
        m_running = false;
        if (m_timer)
            killTimer(m_timer);
        m_timer = 0;
    }
}

/*!
    Set the simulation update interval in hertz.
 */
void QtBox2DEngine::setInterval(double hertz)
{
    if (m_timer)
        killTimer(m_timer);
    m_hertz = hertz;
    m_timer = startTimer(m_hertz/m_step);
}

/*!
    Set timestep ratio. The step is performed interval/ratio times per second.
 */
void QtBox2DEngine::setTimestepRatio(double ratio)
{
    m_step = ratio;
    setInterval(m_hertz);
}

/*!
    Specifies the world gravity using a vector with coordinates \a x and \a y.
 */
void QtBox2DEngine::setGravity(float32 x, float32 y)
{
    m_world->SetGravity(b2Vec2(x, y));
}

/*!
    Assign a gravity vector pointing downward with length g, i.e., (0, -g).

    \overload
 */
void QtBox2DEngine::setGravity(float32 g)
{
    m_world->SetGravity(b2Vec2(0, -g));
}

/*!
    \fn void QtBox2DEngine::setVelocityIterations(int i)

    Set iteration count for the velocity phase in the constraint solver. The
    default setting is 8. More iterations decreases performance but improves
    the quality of simulation. See Box2D's documentation.
 */

/*!
    \fn void QtBox2DEngine::setPositionIterations(int i)

    Set position iteration count. Default setting is 3. More iterations
    decreases performance but improves the quality of simulation. See Box2D's
    documentation.
 */

/*!
    \reimp
 */
void QtBox2DEngine::timerEvent(QTimerEvent *event)
{
    if (m_running && event->timerId() == m_timer) {
        m_world->Step(1.0/m_hertz, m_velocityIter, m_positionIter);
        emit step();
    }
}

void QtBox2DEngine::assignFixtureProperty(b2Body *body, const FixtureMember &member, qreal arg) const
{
    b2Fixture* fixture = body->GetFixtureList();
    while (fixture) {
        (fixture->*member)(arg);
        fixture = fixture->GetNext();
    }
}

