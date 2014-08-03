#include "qworldview.h"
#include <QApplication>
#include <QGraphicsScene>
#include "box2dengine.h"
#include "World.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, true);

    QWorldView w;
    w.show();
    

    return a.exec();
}
