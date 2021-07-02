#include "gifHandler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gifHandler w;
    w.show();
    return a.exec();
}
