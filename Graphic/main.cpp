#include <QApplication>
#include <Q3DSurface>
#include <QtWidgets>

#include "window.h"

using namespace QtDataVisualization;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window *window = new Window;
    window->createWindow();


    return app.exec();
}
