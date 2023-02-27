#include "httpfilesize.h"

HTTPFileSize::HTTPFileSize(MapDescriptor *mapDescriptor, void (*func)(MapDescriptor *md), QObject *parent)
    : QObject{parent}
{
    md = mapDescriptor;
    callBackFunction = func;
}

void HTTPFileSize::RequestSize()
{
    requestFileSize(md->GetFullURL());
}

void HTTPFileSize::fileSize()
{
    md->FileSize = m_reply->header(QNetworkRequest::ContentLengthHeader).toInt();
    md->FileSizeS = md->GetFileLength(md->FileSize);
    m_reply->deleteLater();
    m_netmanager->deleteLater();
    callBackFunction(md);
}

void HTTPFileSize::httpError(QNetworkReply::NetworkError code)
{

}

void HTTPFileSize::requestFileSize(const QString &url)
{
    QNetworkRequest req;
    m_netmanager = new QNetworkAccessManager(NULL);
    req.setUrl(QUrl(url));
    m_reply = m_netmanager->get(req);
    connect(m_reply, SIGNAL(metaDataChanged()), this, SLOT(fileSize()));
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
}
