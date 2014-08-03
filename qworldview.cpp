#include <math.h>

#include <iostream>
#include <vector>

g#include "qworldview.h"
#include "QtGui/QtGui"
#include "MotionFilter.h"
#include "MyContactListener.h"


class QWorldView;
QWorldView::QWorldView(QWidget *parent) :
  QGraphicsView(parent) {

  QGraphicsScene* scene= new QGraphicsScene;
  QtBox2DEngine* engine= new QtBox2DEngine;

  setMouseTracking(true);
  resize(1920,1080);
  scale(view_scale, view_scale);
  setScene(scene);
  setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  x}qw

