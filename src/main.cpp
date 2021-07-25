#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "darkpalette.h"
#include <chrono>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    darkPalette palette;
    auto darkPollete = palette.setDarkPalette();
    a.setPalette(darkPollete);
    MainWindow w;
    w.show();
    return a.exec();
}
