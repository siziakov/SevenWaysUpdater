#ifndef HTTPFILESIZE_H
#define HTTPFILESIZE_H

#include <QObject>
#include <QNetworkReply>

#include "mapdescriptor.h"

class HTTPFileSize: public QObject
{
    Q_OBJECT
public:
    HTTPFileSize(MapDescriptor *mapDescriptor, QObject *parent);
    void RequestSize();
public slots:
    void fileSize();
    void httpError(QNetworkReply::NetworkError code);

signals:
    void mapInfoUpdated(MapDescriptor *md);

private:
    void requestFileSize(const QString &url);

    MapDescriptor *md;
    QNetworkAccessManager *m_netmanager;
    QNetworkReply *m_reply;
};

#endif // HTTPFILESIZE_H
