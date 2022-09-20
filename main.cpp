#include "mainwindow.h"

#include <QApplication>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/res/cat.ico"));
    MainWindow w;
    w.show();
    return app.exec();
}
