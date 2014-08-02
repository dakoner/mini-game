#include "qworldview.h"
#include <QApplication>
#include "box2dengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);

  QtBox2DEngine engine;
  engine.setGravity(0);
  engine.setInterval(60);

  QWorldView w(&engine);
    w.show();

  engine.start();

    return a.exec();
}
