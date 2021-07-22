#ifndef CUSTOMSYSTEMINFO_H
#define CUSTOMSYSTEMINFO_H

#include <QtWidgets>
#include <QTextCodec>
class CustomSystemInfo
{
public:
    CustomSystemInfo();
    QVector<QString> getInfoAboutWindows();
    QVector<QString> getInfoAboutCpu();
    QVector<QString> getInfoAboutGpu();
    QVector<QString> getInfoAboutRam();
    QVector<QString> getInfoAboutHardDrive();
    QVector<QString> getInfoAboutLogicalDisks();
    size_t getNumberOfVideoCards();
    size_t getNumberOfRam();
    size_t getNumberOfHardDrives();
    size_t getNumberOfLogicalDisks();
private:
    int executeConsoleExpr(QProcess &process, const QString &expr);
    QString getDataFromConsole(const QString& expr, bool);
    QVector<QString> splitWMIoutput(const QString &query, const QString &sep);
    QTextCodec *codec;
    QProcess process;
    size_t numberOfVideoCards;
    size_t numberOfRam;
    size_t numberOfHardDrives;
    size_t numberOfLogicalDrives;
};

#endif // CUSTOMSYSTEMINFO_H
