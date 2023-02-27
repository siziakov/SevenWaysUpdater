//#include <QNetworkAccessManager>

#include "mapdescriptor.h"

//MapDescriptor::MapDescriptor(): QObject()
//{
//    this->Server = "";
//    this->Filename = "";
//    this->Name = "";
//}

//MapDescriptor::MapDescriptor(const MapDescriptor &mapDescriptor): QObject()
//{
//    this->Server = mapDescriptor.Server;
//    this->Filename = mapDescriptor.Filename;
//    this->Name = mapDescriptor.Name;
//    this->FileSize = mapDescriptor.FileSize;
//}

//MapDescriptor::MapDescriptor(QString server, QString filename, QString name)
//{
//    this->Server = "http://" + server;
//    this->Filename = filename;
//    this->Name = name;

//    requestFileSize(Server + Filename);
//}

//MapDescriptor::~MapDescriptor()
//{
//    if (m_reply != NULL)
//    {
//        //m_reply->abort();
//        //delete  m_reply;
//        //m_reply = NULL;
//    }
//    if (m_netmanager != NULL)
//    {
//        //m_netmanager->disconnect();
//        //delete m_netmanager;
//        //m_netmanager = NULL;
//    }
//}

//const MapDescriptor MapDescriptor::operator =(const MapDescriptor &mapDescriptor)
//{
//    return mapDescriptor;
//}

//void MapDescriptor::fileSize()
//{
//    FileSize = m_reply->header(QNetworkRequest::ContentLengthHeader).toString();
//    m_reply->deleteLater();
//    m_netmanager->deleteLater();
//}

//void MapDescriptor::httpError(QNetworkReply::NetworkError code)
//{

//}

//void MapDescriptor::requestFileSize(const QString &url)
//{
//    QNetworkRequest req;
//    m_netmanager = new QNetworkAccessManager(NULL);
//    req.setUrl(QUrl(url));
//    m_reply = m_netmanager->get(req);
//    connect(m_reply, SIGNAL(metaDataChanged()), this, SLOT(fileSize()));
//    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
//}


MapDescriptor::MapDescriptor()
{

}

MapDescriptor::MapDescriptor(QString server, QString serverPath, QString filename, QString name)
{
    Server = server;
    ServerPath = serverPath;
    Filename = filename;
    Name = name;
    FileSize = 0;
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

QString MapDescriptor::GetFullURL()
{
    return Protocol + Server + ServerPath + Filename;
}
