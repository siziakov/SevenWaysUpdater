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

public slots:
    void treeItemChanged(QTreeWidgetItem *item, int column); // slot function

private:
    Ui::MainWindow *ui;
    QString lastOpenedFile;
    QString EXEFolder;
    QString MAPSFolder;

    static QTreeWidget *mapsTree;

    static void fileSizeChanged(MapDescriptor *md);

    void writeSettings();
    void readSettings();
    void fillFolders();
    void fillListOfMaps();

    static void updateFileSizeOfMap(MapDescriptor *md);

    void requestFileSize(MapDescriptor *md);

    Maps *maps;

    void initMaps();

};

#endif // MAINWINDOW_H
