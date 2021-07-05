#include "gifHandler.h"
#include "userListView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // gifHandler w;
	userListView w;
    w.show();
    return a.exec();
}
