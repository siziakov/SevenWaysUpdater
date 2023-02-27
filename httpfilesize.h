#ifndef HTTPFILESIZE_H
#define HTTPFILESIZE_H

#include <QObject>
#include <QNetworkReply>

#include "mapdescriptor.h"

class HTTPFileSize: public QObject
{
    Q_OBJECT
public:
    HTTPFileSize(MapDescriptor *mapDescriptor, void (*func)(MapDescriptor *md), QObject *parent);
    void RequestSize();
public slots:
    void fileSize();
    void httpError(QNetworkReply::NetworkError code);
private:
    void requestFileSize(const QString &url);

    MapDescriptor *md;
    QNetworkAccessManager *m_netmanager;
    QNetworkReply *m_reply;

    void (*callBackFunction)(MapDescriptor *md);
};

#endif // HTTPFILESIZE_H
