#include "customsysteminfo.h"
#include <QStringLiteral>
#include <QtCore5Compat/QTextCodec>


CustomSystemInfo::CustomSystemInfo()
{
     codec = QTextCodec::codecForName("IBM 866"); //IBM 866 to decode windows symbols
}


int CustomSystemInfo::executeConsoleExpr(QProcess& process, const QString& expr){
    process.startCommand(expr);
    process.waitForFinished();
    return process.exitCode();
}


void deleteFirstWordFromString(QString& string){
    QString::const_iterator erase_it = string.cbegin();
        for (auto it = string.cbegin(); it != string.cend(); ++it) {
            if (*it == ' ') {
                erase_it = it + 1;
                break;
            }
        }
    string.erase(string.cbegin(), erase_it);
}


QString CustomSystemInfo::getDataFromConsole(const QString& expr, bool deleteFirstWord=true){
    // QProcess process in .h;
    if (executeConsoleExpr(process, expr)){ // if exit code from process != 0
        return "error";
    }
    // decode russian symbols from console output
    QString output = codec->toUnicode(process.readAllStandardOutput().simplified());
    if (deleteFirstWord)
        deleteFirstWordFromString(output);
    return output;
}

// add one space before first char of string to
// split it by the separator. E.g:
// " Name=name"  - can split      "Name=name"   - can't split
// " Name=name"    by " Name=".   " Name=name"   by "Name=" or " Name=".
QVector<QString> CustomSystemInfo::splitWMIoutput(const QString& query, const QString& sep){
    return (" " + getDataFromConsole(query, false)).split(sep);
}


QVector<QString> CustomSystemInfo::getInfoAboutLogicalDisks(){
    QVector<QString> result;
    // if computer has 2 (or more) disks, then wmic output will have
    // nonseparate string with information about both disks. E.g.:
    // > wmic logicaldisk get caption
    // Caption
    // C:
    // D:
    // hence we need to split this string and get info about each disk
    // separartely in for loop
    auto diskNamesSplitted = splitWMIoutput("wmic logicaldisk get caption /format:list", " Caption=");
    // d.begin() + 1 -> because first object is " "
    diskNamesSplitted = QStringList(diskNamesSplitted.begin() + 1, diskNamesSplitted.end());
    result.reserve(5 * diskNamesSplitted.size());
    numberOfLogicalDrives = diskNamesSplitted.size();

    for (auto it = diskNamesSplitted.begin(); it != diskNamesSplitted.end(); ++it){

        QString name        = QString("wmic logicaldisk where caption='%1' get Name").arg(*it); // C:
        QString description = QString("wmic logicaldisk where caption='%1' get Description").arg(*it); // ????????? ????
        QString fileSystem  = QString("wmic logicaldisk where caption='%1' get FileSystem").arg(*it); // NTFS
        QString freeSpace   = QString("wmic logicaldisk where caption='%1' get FreeSpace").arg(*it); // 60 GB
        QString size        = QString("wmic logicaldisk where caption='%1' get Size").arg(*it); // 250 GB

        result << getDataFromConsole(name);
        result << getDataFromConsole(description);
        result << getDataFromConsole(fileSystem);
        result << QString::number(getDataFromConsole(size).toLongLong() >> 30).append(" GB");
        result << QString::number(getDataFromConsole(freeSpace).toLongLong() >> 30).append(" GB");

        // add empty string to result to use it like spacing, that divides outputs
        if (it != diskNamesSplitted.end() - 1)
            result << " ";
    }
    return result;
}

size_t CustomSystemInfo::getNumberOfLogicalDisks(){
    return numberOfLogicalDrives;
}

QVector<QString> CustomSystemInfo::getInfoAboutHardDrive(){
    QVector<QString> result;
    auto driveNamesSplitted = splitWMIoutput("wmic diskdrive get caption /format:list", " Caption=");
    driveNamesSplitted = QStringList(driveNamesSplitted.begin() + 1, driveNamesSplitted.end());
    result.reserve(2 * driveNamesSplitted.size());
    numberOfHardDrives = driveNamesSplitted.size() ;
    for (auto it = driveNamesSplitted.begin(); it != driveNamesSplitted.end(); ++it){

        QString model = QString("wmic diskdrive where caption='%1' get model").arg(*it); // SSD ....
        QString size  = QString("wmic diskdrive where caption='%1' get size").arg(*it); // 250 GB

        result << getDataFromConsole(model);
        result << QString::number(getDataFromConsole(size).toLongLong() >> 30).append(" GB");

        if (it != driveNamesSplitted.end() - 1)
            result << " ";
    }
    return result;
}


size_t CustomSystemInfo::getNumberOfHardDrives(){
    return numberOfHardDrives;
}


QVector<QString> CustomSystemInfo::getInfoAboutRam(){
    QVector<QString> result;

    auto RAMcardNamesSplitted = splitWMIoutput("wmic memorychip get banklabel /format:list", " BankLabel=");
    RAMcardNamesSplitted = QStringList(RAMcardNamesSplitted.begin() + 1, RAMcardNamesSplitted.end());
    result.reserve(4 * RAMcardNamesSplitted.size());
    numberOfRam = RAMcardNamesSplitted.size();

    for (auto it = RAMcardNamesSplitted.begin(); it != RAMcardNamesSplitted.end(); ++it){

         QString tag          = QString("wmic memorychip where banklabel='%1' get tag").arg(*it); // ?????????? ??????
         QString manufacturer = QString("wmic memorychip where banklabel='%1' get manufacturer").arg(*it); // kingston
         QString capacity     = QString("wmic memorychip where banklabel='%1' get capacity").arg(*it); // 8 GB
         QString speed        = QString("wmic memorychip where banklabel='%1' get speed").arg(*it); // 2200

         result << getDataFromConsole(tag);
         result << getDataFromConsole(manufacturer);
         result << QString::number(getDataFromConsole(capacity).toLongLong() >> 30).append(" GB");
         result << getDataFromConsole(speed).append(" MHz");
         if (it != RAMcardNamesSplitted.end() - 1)
             result << " ";
     }
    return result;
}


size_t CustomSystemInfo::getNumberOfRam(){
    return numberOfRam;
}


QVector<QString> CustomSystemInfo::getInfoAboutGpu(){
    QVector<QString> result;

    auto videocardNamesSplitted = splitWMIoutput("wmic PATH Win32_videocontroller get name /format:list", " Name=");
    videocardNamesSplitted = QStringList(videocardNamesSplitted.begin() + 1, videocardNamesSplitted.end());
    result.reserve(3 * videocardNamesSplitted.size());
    numberOfVideoCards = videocardNamesSplitted.size();

    for (auto it = videocardNamesSplitted.begin(); it != videocardNamesSplitted.end(); ++it){

        QString vName = QString("wmic PATH Win32_videocontroller where name='%1' get name").arg(*it); // nvidia gtx 1060
        QString resX  = QString("wmic PATH Win32_videocontroller where name='%1' get CurrentHorizontalResolution").arg(*it); // 1920x1080
        QString resY  = QString("wmic PATH Win32_videocontroller where name='%1' get CurrentVerticalResolution").arg(*it);
        QString rate  = QString("wmic PATH Win32_videocontroller where name='%1' get CurrentRefreshRate").arg(*it); //144

        result << getDataFromConsole(vName);
        result << getDataFromConsole(resX).append("x").append(getDataFromConsole(resY));
        result << getDataFromConsole(rate).append(" Hz");
        if (it != videocardNamesSplitted.end() - 1)
            result << " ";
    }

    return result;
}

size_t CustomSystemInfo::getNumberOfVideoCards(){
    return numberOfVideoCards;
}


QVector<QString> CustomSystemInfo::getInfoAboutWindows(){
    QVector<QString> result;
    result.reserve(7);

    result << getDataFromConsole("wmic os get Caption"); // windows 10 pro
    result << getDataFromConsole("wmic os get BuildNumber");  //1943
    result << getDataFromConsole("wmic os get OSArchitecture"); // 64
    result << getDataFromConsole("wmic os get CSName"); //DESKTOP-I192P3O
    result << getDataFromConsole("wmic os get Manufacturer"); // Microsoft
    result << getDataFromConsole("wmic os get MUILanguages"); // ru
    result << getDataFromConsole("wmic os get SystemDirectory"); // C:system

    return result;
}


QVector<QString> CustomSystemInfo::getInfoAboutCpu(){
   QVector<QString> result;
   result.reserve(7);

   result << getDataFromConsole("wmic cpu get name"); // Intel Core i5 8750H
   result << getDataFromConsole("wmic cpu get NumberOfCores"); //6
   result << getDataFromConsole("wmic cpu get ThreadCount"); //12
   result << getDataFromConsole("wmic cpu get NumberOfLogicalProcessors"); //12
   result << getDataFromConsole("wmic cpu get CurrentClockSpeed").append(" MHz"); //2200
   result << getDataFromConsole("wmic cpu get L3CacheSize").append(" KB"); //3000
   result << getDataFromConsole("wmic cpu get L2CacheSize").append(" KB"); //9000

   return result;
}
