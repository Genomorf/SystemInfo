#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <customsysteminfo.h>
#include <QtCore5Compat/QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textFont.setPixelSize(20);

    createOsInfoBlock();
    createCpuInfoBlock();
    createGpuInfoBlock();
    createRamInfoBlock();
    createHardDriveInfoBlock();
    createLogicalDisksInfoBlock();

    // connect left scroll bar to right scroll bar to
    // use them as one: if we scroll one, second is
    // scrolling too and other way round
    connect( ui->textBrowserLeft4->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserRight4->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserRight4->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserLeft4->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserLeft6->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserRight6->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserRight6->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserLeft6->verticalScrollBar(), &QScrollBar::setValue);
}


void MainWindow::createOsInfoBlock(){
    QVector<QString> parameters {
           {"ОС: "},
           {"Сборка:"},
           {"Тип системы:"},
           {"Имя устройства:"},
           {"Производитель:"},
           {"Язык системы:"},
           {"Системная директория:"}
    };
    fillBlock(ui->labelOsTitle,"Характеристики ОС", ui->textBrowserLeft1, ui->textBrowserRight1,
              0, parameters, customSystemInfo.getInfoAboutWindows());
}


void MainWindow::createCpuInfoBlock(){
    QVector<QString> parameters{
        {"Процессор: "},
        {"Ядер: "},
        {"Потоков: "},
        {"Логических процессоров: "},
        {"Тактовая частота: "},
        {"Размер L3 кэша: "},
        {"Размер L2 кэша: "}
    };
    fillBlock(ui->labelCPUTitle,"Характеристики CPU", ui->textBrowserLeft2, ui->textBrowserRight2,
              0, parameters, customSystemInfo.getInfoAboutCpu());
}


void MainWindow::createGpuInfoBlock(){
    QVector<QString> parameters{
        {"Видеокарта 0:"},
        {"Разрешение: "},
        {"Частота обновления: "}
    };
    fillBlock(ui->labelGPUTitle, "Характеристики GPU", ui->textBrowserLeft3,
              ui->textBrowserRight3, customSystemInfo.getNumberOfVideoCards(),
              parameters, customSystemInfo.getInfoAboutGpu());
}


void MainWindow::createRamInfoBlock(){
    QVector<QString> parameters{
        {"RAM 0:"},
        {"Производитель: "},
        {"Объем: "},
        {"Скорость: "}
    };
    fillBlock(ui->labelRAMTitle, "Характеристики RAM", ui->textBrowserLeft4,
              ui->textBrowserRight4, customSystemInfo.getNumberOfRam(),
              parameters, customSystemInfo.getInfoAboutRam());
}


void MainWindow::createHardDriveInfoBlock(){
    QVector<QString> parameters{
        {"Жесткий диск 0:"},
        {"Размер: "}
    };
    fillBlock(ui->labelDrive, "Характеристики жестких дисков", ui->textBrowserLeft5,
              ui->textBrowserRight5, customSystemInfo.getNumberOfHardDrives(),
              parameters, customSystemInfo.getInfoAboutHardDrive());

}


void MainWindow::createLogicalDisksInfoBlock(){
    QVector<QString> parameters{
        {"Локальный диск 0:"},
        {"Описание: "},
        {"Файловая система: "},
        {"Размер: "},
        {"Свободного места: "}
    };
    fillBlock(ui->labelLogical, "Характеристики локальных дисков", ui->textBrowserLeft6,
              ui->textBrowserRight6, customSystemInfo.getNumberOfLogicalDisks(),
              parameters, customSystemInfo.getInfoAboutLogicalDisks());
}


void MainWindow::fillTextBrowserWithInfo(QTextBrowser* tb, QVector<QString> info){
    tb->setFont(textFont);
    for (auto& i : info){
        tb->insertPlainText(i.append('\n'));
    }
}


void MainWindow::fillBlock(
        QLabel* label, const QString& labelText, QTextBrowser* browserLeft,
        QTextBrowser* browserRight, size_t numberOfObjects, QVector<QString>& parameters,
        QVector<QString>&& info
        ){
    label->setFont(textFont);
    label->setText(labelText);
    browserLeft->setTextColor(QColor(Qt::white));
    browserRight->setTextColor(QColor(153,153,153));
    for (size_t i = 0; i < numberOfObjects; ++i){
        // This 2 lines of code replace two last symbols of the first
        // string in QVector<QString> parameters with int count and
        // char(':'). E.g. parameters[0] = "Видеокарта 0:".
        // In for loop this code transformates it to:
        // "Видеокарта 1:" and "Видеокарта 2:"
        parameters[0] = parameters[0].left(parameters[0].size() - 2);
        parameters[0].append(QString::number(i + 1).append(":"));

        fillTextBrowserWithInfo(browserLeft, parameters);

        // devide parameters by \n in for loop
        if (i != numberOfObjects - 1)
            browserLeft->insertPlainText("\n");

    }
    // if computer doesn't have 2 (or more) objects and
    // for loop wasn't created. Need this for:
    // getInfoAboutCpu() and getInfoAboutWindows()
    if (numberOfObjects == 0)
         fillTextBrowserWithInfo(browserLeft, parameters);


    fillTextBrowserWithInfo(browserRight, info);
}


MainWindow::~MainWindow()
{
    delete ui;
}

