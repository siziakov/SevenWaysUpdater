#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QNetworkAccessManager>

class QNetworkReply;
class QFile;

class Downloader : public QObject
{
    Q_OBJECT
    using BaseClass = QObject;

public:
    explicit Downloader(QObject* parent = nullptr, bool cachedUpdate = false);

    // Метод для запуска скачиввания
    bool get(const QString& targetFolder, const QUrl& url);

    static QString CacheFolder;

    void unzipFile(const QString& targetFolder, QString fileName, bool removeFileAfterUnzipping = false);

public slots:
    // Метод отмены загрузки
    void cancelDownload();

signals:
    // Сигнал передающий информацию о прогрессе загрузки
    void updateDownloadProgressPart(qint64 bytesReceived, qint64 bytesTotal);
    void updateFileWasUnzipped(bool result);

private slots:
    // Слот для постепенного считывания загружаемых данных
    void onReadyRead();
    // Слот для обработки завершения запроса
    void onReply(QNetworkReply* reply);

private:
    QNetworkReply* m_currentReply {nullptr};    // Текущий обрабатываемый запрос
    QFile* m_file                 {nullptr};    // Текущий файл в который идёт запись
    QNetworkAccessManager m_manager;            // Сетевой менеджер для загрузки файлов
    QString targetFolder;

    qint64 bytesPart;

    bool cachedUpdate = false;

    static int on_extract(const char *filename, void *arg);
    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
};

#endif // DOWNLOADER_H
