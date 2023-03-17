#ifndef MAPDESCRIPTOR_H
#define MAPDESCRIPTOR_H

#include <QString>
#include <QDate>

class MapDescriptor
{
public:
    MapDescriptor();
    MapDescriptor(QString server, QString serverPath, QString filename, QString name, QString mapsFolder);
    MapDescriptor(QString server, QString serverPath, QString filename, QString name, QString mapsFolder, int fileSize, QString fileSizeS, QDateTime date, QString dateS);
    MapDescriptor(const MapDescriptor *md);
    ~MapDescriptor();

    QString GetFullURL();

    QString Protocol = "http://";
    QString Server;
    QString ServerPath;
    QString Filename;
    QString Name;
    int FileSize = 0;
    QString FileSizeS = "";
    QDateTime Date = QDateTime::currentDateTime();
    QString DateS = "";

    QString MAPSFolder = "";

    QString GetFileLength(int size);

    bool Equals(MapDescriptor md);

    bool FileIsOlder();
    bool FileExists();
    void UpdateFileInfo(MapDescriptor md);

    static MapDescriptor Empty;
};

#endif // MAPDESCRIPTOR_H
