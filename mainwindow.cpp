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
    connect( ui->textBrowserLeft4->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserRight4->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserRight4->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserLeft4->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserLeft6->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserRight6->verticalScrollBar(), &QScrollBar::setValue);
    connect( ui->textBrowserRight6->verticalScrollBar(), &QScrollBar::valueChanged, ui->textBrowserLeft6->verticalScrollBar(), &QScrollBar::setValue);

}



void MainWindow::fillTextBrowserWithInfo(QTextBrowser* tb, QVector<QString> info){


    tb->setFont(textFont);
    for (auto& i : info){
        tb->insertPlainText(i.append('\n'));
    }
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

    ui->labelOsTitle->setFont(textFont);
    ui->labelOsTitle->setText("Характеристики ОС");
    ui->textBrowserLeft1->setTextColor(QColor(Qt::white));
    ui->textBrowserRight1->setTextColor(QColor(153,153,153));

    fillTextBrowserWithInfo(ui->textBrowserLeft1, parameters);
    fillTextBrowserWithInfo(ui->textBrowserRight1, customSystemInfo.getInfoAboutWindows());
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
    ui->labelCPUTitle->setFont(textFont);
    ui->labelCPUTitle->setText("Характеристики CPU");
    ui->textBrowserLeft2->setTextColor(QColor(Qt::white));
    ui->textBrowserRight2->setTextColor(QColor(153,153,153));

    fillTextBrowserWithInfo(ui->textBrowserLeft2, parameters);
    fillTextBrowserWithInfo(ui->textBrowserRight2, customSystemInfo.getInfoAboutCpu());
}

void MainWindow::createGpuInfoBlock(){
    QVector<QString> parameters{
        {"Видеокарта 0:"},
        {"Разрешение: "},
        {"Частота обновления: "}
    };
//    ui->labelGPUTitle->setFont(textFont);
//    ui->labelGPUTitle->setText("Характеристики GPU");
//    ui->textBrowserLeft3->setTextColor(QColor(Qt::white));
//    ui->textBrowserRight3->setTextColor(QColor(153,153,153));

//    auto info = customSystemInfo.getInfoAboutGpu();
//    size_t numberOfVideoCards = customSystemInfo.getNumberOfVideoCards();
//    for (size_t i = 0; i < numberOfVideoCards; ++i){

//        parameters[0] = parameters[0].left(parameters[0].size() - 2);
//        parameters[0].append(QString::number(i + 1).append(":"));

//        fillTextBrowserWithInfo(ui->textBrowserLeft3, parameters);

//        if (i != numberOfVideoCards - 1)
//            ui->textBrowserLeft3->insertPlainText("\n");
//    }
//    fillTextBrowserWithInfo(ui->textBrowserRight3, info);
    auto info = customSystemInfo.getInfoAboutGpu();
    fillBlock(ui->labelGPUTitle, "Характеристики GPU", ui->textBrowserLeft3,
              ui->textBrowserRight3, customSystemInfo.getNumberOfVideoCards(),
              parameters, info);
}

void MainWindow::createRamInfoBlock(){
    QVector<QString> parameters{
        {"RAM 0:"},
        {"Производитель: "},
        {"Объем: "},
        {"Скорость: "}
    };

    ui->labelRAMTitle->setFont(textFont);
    ui->labelRAMTitle->setText("Характеристики RAM");
    ui->textBrowserLeft4->setTextColor(QColor(Qt::white));
    ui->textBrowserRight4->setTextColor(QColor(153,153,153));

    auto info = customSystemInfo.getInfoAboutRam();
    size_t numberOfRam = customSystemInfo.getNumberOfRam();
    for (size_t i = 0; i < numberOfRam; ++i){
        parameters[0] = parameters[0].left(parameters[0].size() - 2);
        parameters[0].append(QString::number(i + 1).append(":"));

        fillTextBrowserWithInfo(ui->textBrowserLeft4, parameters);

        if (i != numberOfRam - 1)
            ui->textBrowserLeft4->insertPlainText("\n");
    }

    fillTextBrowserWithInfo(ui->textBrowserRight4, info);
}

void MainWindow::createHardDriveInfoBlock(){
    QVector<QString> parameters{
        {"Жесткий диск 0:"},
        {"Размер: "}
    };
    ui->labelDrive->setFont(textFont);
    ui->labelDrive->setText("Характеристики жестких дисков");

    ui->textBrowserLeft5->setTextColor(QColor(Qt::white));
    ui->textBrowserRight5->setTextColor(QColor(153,153,153));
    auto info = customSystemInfo.getInfoAboutHardDrive();
    size_t numberOfHardDrives = customSystemInfo.getNumberOfRam();
    for (size_t i = 0; i < numberOfHardDrives; ++i){
        parameters[0] = parameters[0].left(parameters[0].size() - 2);
        parameters[0].append(QString::number(i + 1).append(":"));

        fillTextBrowserWithInfo(ui->textBrowserLeft5, parameters);

        if (i != numberOfHardDrives - 1)
            ui->textBrowserLeft5->insertPlainText("\n");
    }
    fillTextBrowserWithInfo(ui->textBrowserRight5, info);
}

void MainWindow::createLogicalDisksInfoBlock(){
    QVector<QString> parameters{
        {"Локальный диск 0:"},
        {"Описание: "},
        {"Файловая система: "},
        {"Размер: "},
        {"Свободного места: "}
    };
    ui->labelLogical->setFont(textFont);
    ui->labelLogical->setText("Характеристики локальных дисков");

    ui->textBrowserLeft6->setTextColor(QColor(Qt::white));
    ui->textBrowserRight6->setTextColor(QColor(153,153,153));

    auto info = customSystemInfo.getInfoAboutLogicalDisks();
    size_t numberOfLogicalDisks = customSystemInfo.getNumberOfLogicalDisks();
    for (size_t i = 0; i < numberOfLogicalDisks; ++i){
        parameters[0] = parameters[0].left(parameters[0].size() - 2);
        parameters[0].append(QString::number(i + 1).append(":"));

        fillTextBrowserWithInfo(ui->textBrowserLeft6, parameters);

        if (i != numberOfLogicalDisks - 1)
            ui->textBrowserLeft6->insertPlainText("\n");

    }
    fillTextBrowserWithInfo(ui->textBrowserRight6, info);

}

void MainWindow::fillBlock(
        QLabel* label, const QString& labelText, QTextBrowser* browserLeft,
        QTextBrowser* browserRight, size_t numberOfObjects, QVector<QString>& parameters,
        QVector<QString>& info
        )
{
    label->setFont(textFont);
    label->setText(labelText);
    browserLeft->setTextColor(QColor(Qt::white));
    browserRight->setTextColor(QColor(153,153,153));
    for (size_t i = 0; i < numberOfObjects; ++i){
        parameters[0] = parameters[0].left(parameters[0].size() - 2);
        parameters[0].append(QString::number(i + 1).append(":"));

        fillTextBrowserWithInfo(browserLeft, parameters);

        if (i != numberOfObjects - 1)
            browserLeft->insertPlainText("\n");

    }
    fillTextBrowserWithInfo(browserRight, info);
}
MainWindow::~MainWindow()
{
    delete ui;
}

