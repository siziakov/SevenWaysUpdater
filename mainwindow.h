#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTreeWidgetItem>

#include "maps.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateParentItem(QTreeWidgetItem *item);

private slots:
    void on_btnSelectFolder_clicked();

    void on_btnFullUpdate_clicked();

    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    void updateFileWasUnzipped(bool result);

    void on_btnCachedUpdate_clicked();

public slots:
    void treeItemChanged(QTreeWidgetItem *item, int column); // slot function

private:
    Ui::MainWindow *ui;
    QString lastOpenedFile;
    QString EXEFolder;
    QString MAPSFolder;
    QString CacheFolder;

    qint64 totalSizeOfSelectedMaps;
    qint64 totalDownloadedBytes;
    int unzippedFiles;

    QBrush mapIsOnDeviceBrush;

    static Maps MapSet;

    static QTreeWidget *mapsTree;
    QList<MapDescriptor> *offlineMapsCached = nullptr;

    bool isMapInCacheExist(MapDescriptor md);
    bool isMapInCacheOlder(MapDescriptor md);

    void writeSettings();
    void readSettings();
    void writeLastMaps(QList<MapDescriptor> *maps);
    QList<MapDescriptor> *readLastMaps();

    void fillFolders();
    void fillListOfMaps();
    void checkCache();

    void requestFileSize(MapDescriptor *md);

    void prepareAndUpdateMaps();

    void initMaps();

    void doUpdate(QList<MapDescriptor> *mapsToUpdate, QString folderToSave);

    void mapInfoUpdated(MapDescriptor *md);

};

#endif // MAINWINDOW_H
