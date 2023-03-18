#include "downloader.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include "zip.h"

QString Downloader::CacheFolder;

Downloader::Downloader(QObject* parent) :
    BaseClass(parent)
{
    // Подключаемся к сигналу finished
    connect(&m_manager, &QNetworkAccessManager::finished, this, &Downloader::onReply);
    CacheFolder = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QDir::separator();
}

bool Downloader::get(const QString& targetFolder, const QUrl& url)
{
    this->targetFolder = targetFolder;
    if (targetFolder.isEmpty() || url.isEmpty())
    {
        return false;
    }

    // Cоздаём объект класса файла для скачивания
    // здесь имеется целевая директория и имя файла, которое выделяется из URL
    m_file = new QFile(CacheFolder + url.fileName());
    // Пробуем открыть файл
    if (!m_file->open(QIODevice::WriteOnly))
    {
        delete m_file;
        m_file = nullptr;
        return false;
    }

    bytesPart = 0;
    // Создаём запрос
    QNetworkRequest request(url);
    // Обязательно разрешаем переходить по редиректам
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    // Запускаем скачивание
    m_currentReply = m_manager.get(request);

    // После чего сразу подключаемся к сигналам о готовности данных к чтению и обновлению прогресса скачивания
    connect(m_currentReply, &QNetworkReply::readyRead, this, &Downloader::onReadyRead);
    connect(m_currentReply, &QNetworkReply::downloadProgress, this, &Downloader::updateDownloadProgress);
    return true;
}

void Downloader::onReadyRead()
{
    // Если есть данные и файл открыт
    if (m_file)
    {
        // записываем их в файл
        m_file->write(m_currentReply->readAll());
        m_file->flush();
    }
}

void Downloader::cancelDownload()
{
    // Отмена запроса
    if (m_currentReply)
    {
        m_currentReply->abort();
        bytesPart = 0;
    }
}

void Downloader::onReply(QNetworkReply* reply)
{
    QNetworkReply::NetworkError error = reply->error();
    // По завершению запроса
    if (error == QNetworkReply::NoError)
    {
        QString fileName = m_file->fileName();
        // сохраням файл
        m_file->flush();
        m_file->close();

        int res = zip_extract(fileName.toStdString().c_str(), targetFolder.toStdString().c_str(), Downloader::on_extract, nullptr);
        emit updateFileWasUnzipped(res == 0);
    }
    else
    {
        // Или удаляем его в случае ошибки
        m_file->remove();
        bytesPart = 0;
    }

    delete m_file;
    m_file = nullptr;
    reply->deleteLater();
}

int Downloader::on_extract(const char *filename, void *arg)
{
    return 0;
}

void Downloader::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qint64 part = bytesReceived - bytesPart;
    bytesPart = bytesReceived;
    emit updateDownloadProgressPart(part, bytesTotal);
}
