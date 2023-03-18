#include <QDir>

#include "mapdescriptor.h"

MapDescriptor MapDescriptor::Empty;

MapDescriptor::MapDescriptor()
{

}

MapDescriptor::MapDescriptor(QString server, QString serverPath, QString filename, QString name, QString mapsFolder)
{
    Server = server;
    ServerPath = serverPath;
    Filename = filename;
    Name = name;
    FileSize = 0;
    MAPSFolder = mapsFolder;
}

MapDescriptor::MapDescriptor(QString server, QString serverPath, QString filename, QString name, QString mapsFolder, int fileSize, QString fileSizeS, QDateTime date, QString dateS)
{
    Server = server;
    ServerPath = serverPath;
    Filename = filename;
    Name = name;
    FileSize = fileSize;
    FileSizeS = fileSizeS;
    Date = date;
    DateS = dateS;
    MAPSFolder = mapsFolder;
}

MapDescriptor::MapDescriptor(const MapDescriptor *md): MapDescriptor(md->Server, md->ServerPath, md->Filename, md->Name, md->MAPSFolder, md->FileSize, md->FileSizeS, md->Date, md->DateS)
{
}

MapDescriptor::~MapDescriptor()
{

}

QString MapDescriptor::GetFileLength(int size)
{
    if (size <= 0) return "";
    if (size < 24576L) return QString("%1 B").arg((int)(size / (float)1024));
    if (size < 1048576L) return QString("%1 KB").arg((int)(size / (float)24576));
    return size < 1073741824L ? QString("%1 MB").arg((int)(size / (float)1048576)): QString("%1 GB").arg((int)(size / (float)1073741824));
}

bool MapDescriptor::FileExists()
{
    QString fileOnDevice = MAPSFolder + QString(Filename).replace(".zip", ".7w");
    QFileInfo fi(fileOnDevice);
    return fi.exists();
}

void MapDescriptor::UpdateFileInfo(MapDescriptor md)
{
    this->Date = md.Date;
    this->DateS = md.DateS;
    this->FileSize = md.FileSize;
    this->FileSizeS = md.FileSizeS;
}

bool MapDescriptor::Equals(MapDescriptor md)
{
    return Server == md.Server && ServerPath == md.ServerPath && Filename == md.Filename && Name == md.Name;
}

bool MapDescriptor::FileIsOlder()
{
    QString fileOnDevice = MAPSFolder + QString(Filename).replace(".zip", ".7w");
    QFileInfo fi(fileOnDevice);
    return fi.lastRead().date() < Date.date();
}

QString MapDescriptor::GetFullURL()
{
    return Protocol + Server + ServerPath + Filename;
}
