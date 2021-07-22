#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "customsysteminfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fillTextBrowserWithInfo(QTextBrowser *tb, QVector<QString> info);
    void createOsInfoBlock();
    void createCpuInfoBlock();
    void createGpuInfoBlock();
    void createRamInfoBlock();
    void createHardDriveInfoBlock();
    void createLogicalDisksInfoBlock();
    void fillBlock(QLabel *label, const QString &labelText, QTextBrowser *browserLeft,
                   QTextBrowser *browserRight, size_t numberOfObjects, QVector<QString>& parameters,
                   QVector<QString>& info);
private:
    Ui::MainWindow *ui;
    QFont textFont;
    CustomSystemInfo customSystemInfo;
};
#endif // MAINWINDOW_H
