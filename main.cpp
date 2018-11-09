#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow window;
    window.show();
    return application.exec();
}
