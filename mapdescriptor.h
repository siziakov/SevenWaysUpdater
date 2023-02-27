#ifndef MAPDESCRIPTOR_H
#define MAPDESCRIPTOR_H

//#include <QNetworkAccessManager>
//#include <QNetworkReply>
#include <QString>
//#include <QObject>

class MapDescriptor
{
public:
    MapDescriptor();
    MapDescriptor(QString server, QString serverPath, QString filename, QString name);
    ~MapDescriptor();

    QString GetFullURL();

    QString Protocol = "http://";
    QString Server;
    QString ServerPath;
    QString Filename;
    QString Name;
    int FileSize;
    QString FileSizeS;

    QString GetFileLength(int size);
};

#endif // MAPDESCRIPTOR_H
