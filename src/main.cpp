#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "darkpalette.h"
#include <chrono>
#include <iostream>
#include <QElapsedTimer>
int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();
    QApplication a(argc, argv);
    darkPalette palette;
    auto darkPollete = palette.setDarkPalette();
    a.setPalette(darkPollete);
    MainWindow w;
    w.show();

    qDebug() << timer.elapsed();
    return a.exec();
}
