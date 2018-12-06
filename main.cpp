
#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <QListWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Notepad");
    w.show();
    return a.exec();
}
