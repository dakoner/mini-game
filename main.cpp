#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "World.h"

const float view_scale = 108.;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);

  QGraphicsScene* scene = new QGraphicsScene;

  QGraphicsView* view = new QGraphicsView(scene);
  view->setMouseTracking(true);
  // view->resize(1920,1080);
  view->scale(view_scale, view_scale);
  view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view->setFrameStyle(0);
  view->showFullScreen();
    
  World w(scene, view);
  w.Start();
  return a.exec();
}
