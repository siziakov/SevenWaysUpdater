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

//class MapDescriptor: public QObject
//{
//    Q_OBJECT

//public:
//    MapDescriptor();
//    MapDescriptor(const MapDescriptor &mapDescriptor);
//    MapDescriptor(QString server, QString filename, QString name);
//    ~MapDescriptor();

//    const MapDescriptor operator = (const MapDescriptor &mapDescriptor);

//    QString Server;
//    QString Filename;
//    QString Name;
//    QString FileSize;

//public slots:
//    void fileSize();
//    void httpError(QNetworkReply::NetworkError code);

//private:
//    void requestFileSize(const QString &url);
//    QNetworkAccessManager *m_netmanager;
//    QNetworkReply *m_reply;
//};

#endif // MAPDESCRIPTOR_H
