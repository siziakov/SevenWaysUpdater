#ifndef MAPDESCRIPTOR_H
#define MAPDESCRIPTOR_H

#include <QString>
#include <QDate>

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
    QDate Date;
    QString DateS;

    QString GetFileLength(int size);
};

#endif // MAPDESCRIPTOR_H
