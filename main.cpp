#include "mainwindow.h"
#include <windows.h>
#include <QApplication>
#include <QTextCodec>
#include "darkpalette.h"
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
