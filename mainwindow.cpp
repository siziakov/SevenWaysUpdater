#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QStandardPaths>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httpfilesize.h"
#include "downloader.h"

QTreeWidget *MainWindow::mapsTree;
Maps MainWindow::MapSet;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mapIsOnDeviceBrush.setStyle(Qt::SolidPattern);
    mapIsOnDeviceBrush.setColor(QColor(150, 150, 150));
    ui->setupUi(this);
    mapsTree = ui->treeWidget;
    ui->progressBar->setValue(0);

    readSettings();
    if (lastOpenedFile.isEmpty())
        on_btnSelectFolder_clicked();

    initMaps();
    fillListOfMaps();
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));
}

MainWindow::~MainWindow()
{
    writeSettings();

    delete ui;
}

void MainWindow::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem* parent = item->parent();
    if(parent==NULL) // There is no parent node, it is root node
    {
        return;
    }
    // Select the number of child nodes
    int selectCount=0;
    int childCount= parent->childCount();
    for(int i=0;i<childCount;i++)
    {
        QTreeWidgetItem *childItem = parent->child(i);
        if(childItem->checkState(0)== Qt::Checked)
        {
            selectCount++;
        }
    }
    if(selectCount<=0)
    {
        // Select the state / semi-selected state -> change to unchecked state
        parent->setCheckState(0, Qt::Unchecked);
    }
    else if(selectCount>0 && selectCount<childCount)
    {
        // Unchecked Status / Select Status -> Change to some of the status
        parent->setCheckState(0,Qt::PartiallyChecked); // Partial selection
    }
    else if(selectCount==childCount)
    {
        // Unchecked state / semi-selected state -> Change to select the status
        parent->setCheckState(0,Qt::Checked);
    }
}

void MainWindow::on_btnSelectFolder_clicked()
{
    lastOpenedFile = QFileDialog::getOpenFileName(this, tr("Select folder with 7Ways"), "", tr("7Ways executable (7Ways.exe)"));
    fillFolders();
}

void MainWindow::treeItemChanged(QTreeWidgetItem *item, int column)
{
    QString itemText = item->text(0); // Return the text in the specified column

    if(Qt::Checked == item -> checkState(0)) // CheckState (Column) Returns the check status of the label in the given column (select status)
    {
        QTreeWidgetItem* parent = item->parent();  // The last level of the project?
        int count = item->childCount(); // Return to the number of child nodes of the current node
        if(count > 0) // is a tree node
        {
            for (int i = 0; i<count ; i++)
            {
                // Select the child node and set it to select the status
                item->child(i)->setCheckState(0,Qt::Checked); // CHILD (i) Returns the item to which the item is given in the subkey
            }
        }
        else // No child node, leaves
        {
            // is a child node
            updateParentItem(item);
        }
    }
    else if (Qt::Unchecked == item->checkState(0))
    {
        int count = item->childCount();
        if(count > 0)
        {
            for(int i = 0 ;i<count;i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
        else
        {
            // is a child node
            updateParentItem(item);
        }
    }
}

void MainWindow::writeSettings()
{
    QSettings appSettings("RS-Soft", "Seven Ways Updater");
    appSettings.beginGroup("Main");
    appSettings.setValue("lastOpenedFile", lastOpenedFile);
    appSettings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings appSettings("RS-Soft", "Seven Ways Updater");
    appSettings.beginGroup("Main");
    lastOpenedFile = appSettings.value("lastOpenedFile", "").toString();
    appSettings.endGroup();
    fillFolders();
}

void MainWindow::fillFolders()
{
    QFileInfo appPath(lastOpenedFile);
    EXEFolder = appPath.absolutePath() + QDir::separator();
    MAPSFolder = EXEFolder + "maps" + QDir::separator();
    if (!QDir(MAPSFolder).exists())
        MAPSFolder = EXEFolder + "Maps" + QDir::separator();
    CacheFolder = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QDir::separator();
    QDir cacheDir(CacheFolder);
    if (!cacheDir.exists())
        QDir().mkpath(CacheFolder);
}

void MainWindow::fillListOfMaps()
{
    mapsTree->setColumnCount(4);
    QStringList headerLabels;
    headerLabels.append(tr("group"));
    headerLabels.append((tr("map")));
    headerLabels.append(tr("size"));
    headerLabels.append(tr("date"));
    mapsTree->setHeaderLabels(headerLabels);
    for (MapsGroup mg: MapSet.Groups)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(mapsTree);
        item->setText(0, mg.Name);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setCheckState(0, Qt::Unchecked);
        mapsTree->addTopLevelItem(item);
        for (MapDescriptor md: mg.MapDescriptors)
        {
            QTreeWidgetItem *subItem = new QTreeWidgetItem();
            subItem->setText(1, md.Name);
            subItem->setText(2, md.FileSizeS);
            subItem->setText(3, md.DateS);
            subItem->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
            subItem->setCheckState(0, Qt::Unchecked);
            if (md.FileExists())
            {
                subItem->setBackground(1, mapIsOnDeviceBrush);
                subItem->setBackground(2, mapIsOnDeviceBrush);
                subItem->setBackground(3, mapIsOnDeviceBrush);
            }
            item->addChild(subItem);
        }
    }
}

void MainWindow::requestFileSize(MapDescriptor *md)
{
    HTTPFileSize *fs = new HTTPFileSize(md, this);
    QObject::connect(fs, &HTTPFileSize::mapInfoUpdated, this, &MainWindow::mapInfoUpdated);
    fs->RequestSize();
}

void MainWindow::initMaps()
{
    MapsGroup *russia = new MapsGroup(tr("RUSSIA"));
    MapDescriptor *adm = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "russia_adm.zip", tr("ADM"), MAPSFolder);
    requestFileSize(adm);
    QList<MapDescriptor> *mapsADM = new QList<MapDescriptor>();
    mapsADM->append(adm);
    russia->AddMaps(*mapsADM);

    MapsGroup *cfo = new MapsGroup(tr("CFO"));
    MapDescriptor *bel = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-BEL.zip", tr("BEL"), MAPSFolder);
    MapDescriptor *bry = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-BRY.zip", tr("BRY"), MAPSFolder);
    MapDescriptor *vla = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-VLA.zip", tr("VLA"), MAPSFolder);
    MapDescriptor *vor = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-VOR.zip", tr("VOR"), MAPSFolder);
    MapDescriptor *iva = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-IVA.zip", tr("IVA"), MAPSFolder);
    MapDescriptor *klu = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KLU.zip", tr("KLU"), MAPSFolder);
    MapDescriptor *kos = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KOS.zip", tr("KOS"), MAPSFolder);
    MapDescriptor *krs = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KRS.zip", tr("KRS"), MAPSFolder);
    MapDescriptor *lip = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-LIP.zip", tr("LIP"), MAPSFolder);
    MapDescriptor *mow = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-MOW.zip", tr("MOW"), MAPSFolder);
    MapDescriptor *mos = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-MOS.zip", tr("MOS"), MAPSFolder);
    MapDescriptor *orl = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ORL.zip", tr("ORL"), MAPSFolder);
    MapDescriptor *rya = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-RYA.zip", tr("RYA"), MAPSFolder);
    MapDescriptor *smo = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SMO.zip", tr("SMO"), MAPSFolder);
    MapDescriptor *tam = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TAM.zip", tr("TAM"), MAPSFolder);
    MapDescriptor *tve = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TVE.zip", tr("TVE"), MAPSFolder);
    MapDescriptor *tul = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TUL.zip", tr("TUL"), MAPSFolder);
    MapDescriptor *yar = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-YAR.zip", tr("YAR"), MAPSFolder);
    requestFileSize(bel);
    requestFileSize(bry);
    requestFileSize(vla);
    requestFileSize(vor);
    requestFileSize(iva);
    requestFileSize(klu);
    requestFileSize(kos);
    requestFileSize(krs);
    requestFileSize(lip);
    requestFileSize(mow);
    requestFileSize(mos);
    requestFileSize(orl);
    requestFileSize(rya);
    requestFileSize(smo);
    requestFileSize(tam);
    requestFileSize(tve);
    requestFileSize(tul);
    requestFileSize(yar);
    QList<MapDescriptor> *mapsCFO = new QList<MapDescriptor>;
    mapsCFO->append(bel);
    mapsCFO->append(bry);
    mapsCFO->append(vla);
    mapsCFO->append(vor);
    mapsCFO->append(iva);
    mapsCFO->append(klu);
    mapsCFO->append(kos);
    mapsCFO->append(krs);
    mapsCFO->append(lip);
    mapsCFO->append(mow);
    mapsCFO->append(mos);
    mapsCFO->append(orl);
    mapsCFO->append(rya);
    mapsCFO->append(smo);
    mapsCFO->append(tam);
    mapsCFO->append(tve);
    mapsCFO->append(tul);
    mapsCFO->append(yar);
    cfo->AddMaps(*mapsCFO);

    MapsGroup *szfo = new MapsGroup(tr("SZFO"));
    MapDescriptor *kr = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KR.zip", tr("KR"), MAPSFolder);
    MapDescriptor *ko = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KO.zip", tr("KO"), MAPSFolder);
    MapDescriptor *ark = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ARK.zip", tr("ARK"), MAPSFolder);
    MapDescriptor *vlg = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-VLG.zip", tr("VLG"), MAPSFolder);
    MapDescriptor *kgd = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KGD.zip", tr("KGD"), MAPSFolder);
    MapDescriptor *len = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-LEN.zip", tr("LEN"), MAPSFolder);
    MapDescriptor *mur = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-MUR.zip", tr("MUR"), MAPSFolder);
    MapDescriptor *ngr = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-NGR.zip", tr("NGR"), MAPSFolder);
    MapDescriptor *psk = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-PSK.zip", tr("PSK"), MAPSFolder);
    MapDescriptor *spe = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SPE.zip", tr("SPE"), MAPSFolder);
    MapDescriptor *nen = new MapDescriptor("megamaps*.org", "/store/navikey/russia/", "RU-NEN.zip", tr("NEN"), MAPSFolder);
    requestFileSize(kr);
    requestFileSize(ko);
    requestFileSize(ark);
    requestFileSize(vlg);
    requestFileSize(kgd);
    requestFileSize(len);
    requestFileSize(mur);
    requestFileSize(ngr);
    requestFileSize(psk);
    requestFileSize(spe);
    requestFileSize(nen);
    QList<MapDescriptor> *mapsSZFO = new QList<MapDescriptor>();
    mapsSZFO->append(kr);
    mapsSZFO->append(ko);
    mapsSZFO->append(ark);
    mapsSZFO->append(vlg);
    mapsSZFO->append(kgd);
    mapsSZFO->append(len);
    mapsSZFO->append(mur);
    mapsSZFO->append(ngr);
    mapsSZFO->append(psk);
    mapsSZFO->append(spe);
    mapsSZFO->append(nen);
    szfo->AddMaps(*mapsSZFO);

    MapsGroup *ufo = new MapsGroup(tr("UFO"));
    MapDescriptor *ad = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-AD.zip", tr("AD"), MAPSFolder);
    MapDescriptor *kl = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KL.zip", tr("KL"), MAPSFolder);
    MapDescriptor *krm = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KRM.zip", tr("KRM"), MAPSFolder);
    MapDescriptor *kda = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KDA.zip", tr("KDA"), MAPSFolder);
    MapDescriptor *ast = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-AST.zip", tr("AST"), MAPSFolder);
    MapDescriptor *vgg = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-VGG.zip", tr("VGG"), MAPSFolder);
    MapDescriptor *ros = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ROS.zip", tr("ROS"), MAPSFolder);
    MapDescriptor *sev = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SEV.zip", tr("SEV"), MAPSFolder);
    requestFileSize(ad);
    requestFileSize(kl);
    requestFileSize(krm);
    requestFileSize(kda);
    requestFileSize(ast);
    requestFileSize(vgg);
    requestFileSize(ros);
    requestFileSize(sev);
    QList<MapDescriptor> *mapsUFO = new QList<MapDescriptor>();
    mapsUFO->append(ad);
    mapsUFO->append(kl);
    mapsUFO->append(krm);
    mapsUFO->append(kda);
    mapsUFO->append(ast);
    mapsUFO->append(vgg);
    mapsUFO->append(ros);
    mapsUFO->append(sev);
    ufo->AddMaps(*mapsUFO);

    MapsGroup *skfo = new MapsGroup(tr("SKFO"));
    MapDescriptor *da  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-DA.zip", tr("DA"), MAPSFolder);
    MapDescriptor *in  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-IN.zip", tr("IN"), MAPSFolder);
    MapDescriptor *kb  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KB.zip", tr("KB"), MAPSFolder);
    MapDescriptor *kc  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KC.zip", tr("KC"), MAPSFolder);
    MapDescriptor *se  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SE.zip", tr("SE"), MAPSFolder);
    MapDescriptor *ce  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-CE.zip", tr("CE"), MAPSFolder);
    MapDescriptor *sta = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-STA.zip", tr("STA"), MAPSFolder);
    requestFileSize(da);
    requestFileSize(in);
    requestFileSize(kb);
    requestFileSize(kc);
    requestFileSize(se);
    requestFileSize(ce);
    requestFileSize(sta);
    QList<MapDescriptor> *mapsSKFO = new QList<MapDescriptor>();
    mapsSKFO->append(da);
    mapsSKFO->append(in);
    mapsSKFO->append(kb);
    mapsSKFO->append(kc);
    mapsSKFO->append(se);
    mapsSKFO->append(ce);
    mapsSKFO->append(sta);
    skfo->AddMaps(*mapsSKFO);

    MapsGroup *pfo = new MapsGroup(tr("PFO"));
    MapDescriptor *ba  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-BA.zip", tr("BA"), MAPSFolder);
    MapDescriptor *me  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ME.zip", tr("ME"), MAPSFolder);
    MapDescriptor *mo  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-MO.zip", tr("MO"), MAPSFolder);
    MapDescriptor *ta  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TA.zip", tr("TA"), MAPSFolder);
    MapDescriptor *ud  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-UD.zip", tr("UD"), MAPSFolder);
    MapDescriptor *cu  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-CU.zip", tr("CU"), MAPSFolder);
    MapDescriptor *per = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-PER.zip", tr("PER"), MAPSFolder);
    MapDescriptor *kir = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KIR.zip", tr("KIR"), MAPSFolder);
    MapDescriptor *niz = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-NIZ.zip", tr("NIZ"), MAPSFolder);
    MapDescriptor *ore = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ORE.zip", tr("ORE"), MAPSFolder);
    MapDescriptor *pnz = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-PNZ.zip", tr("PNZ"), MAPSFolder);
    MapDescriptor *sam = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SAM.zip", tr("SAM"), MAPSFolder);
    MapDescriptor *sar = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SAR.zip", tr("SAR"), MAPSFolder);
    MapDescriptor *uly = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ULY.zip", tr("ULY"), MAPSFolder);
    requestFileSize(ba);
    requestFileSize(me);
    requestFileSize(mo);
    requestFileSize(ta);
    requestFileSize(ud);
    requestFileSize(cu);
    requestFileSize(per);
    requestFileSize(kir);
    requestFileSize(niz);
    requestFileSize(ore);
    requestFileSize(pnz);
    requestFileSize(sam);
    requestFileSize(sar);
    requestFileSize(uly);
    QList<MapDescriptor> *mapsPFO = new QList<MapDescriptor>();
    mapsPFO->append(ba);
    mapsPFO->append(me);
    mapsPFO->append(mo);
    mapsPFO->append(ta);
    mapsPFO->append(ud);
    mapsPFO->append(cu);
    mapsPFO->append(per);
    mapsPFO->append(kir);
    mapsPFO->append(niz);
    mapsPFO->append(ore);
    mapsPFO->append(pnz);
    mapsPFO->append(sam);
    mapsPFO->append(sar);
    mapsPFO->append(uly);
    pfo->AddMaps(*mapsPFO);

    MapsGroup *urfo = new MapsGroup(tr("URFO"));
    MapDescriptor *kgn = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KGN.zip", tr("KGN"), MAPSFolder);
    MapDescriptor *sve = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SVE.zip", tr("SVE"), MAPSFolder);
    MapDescriptor *tyu = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TYU.zip", tr("TYU"), MAPSFolder);
    MapDescriptor *che = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-CHE.zip", tr("CHE"), MAPSFolder);
    MapDescriptor *khm = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KHM.zip", tr("KHM"), MAPSFolder);
    MapDescriptor *yan = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-YAN.zip", tr("YAN"), MAPSFolder);
    requestFileSize(kgn);
    requestFileSize(sve);
    requestFileSize(tyu);
    requestFileSize(che);
    requestFileSize(khm);
    requestFileSize(yan);
    QList<MapDescriptor> *mapsURFO = new QList<MapDescriptor>();
    mapsURFO->append(kgn);
    mapsURFO->append(sve);
    mapsURFO->append(tyu);
    mapsURFO->append(che);
    mapsURFO->append(khm);
    mapsURFO->append(yan);
    urfo->AddMaps(*mapsURFO);

    MapsGroup *sfo = new MapsGroup(tr("SFO"));
    MapDescriptor *al  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-AL.zip", tr("AL"), MAPSFolder);
    MapDescriptor *ty  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TY.zip", tr("TY"), MAPSFolder);
    MapDescriptor *kk  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KK.zip", tr("KK"), MAPSFolder);
    MapDescriptor *alt = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ALT.zip", tr("ALT"), MAPSFolder);
    MapDescriptor *kya = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KYA.zip", tr("KYA"), MAPSFolder);
    MapDescriptor *irk = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-IRK.zip", tr("IRK"), MAPSFolder);
    MapDescriptor *kem = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KEM.zip", tr("KEM"), MAPSFolder);
    MapDescriptor *nvs = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-NVS.zip", tr("NVS"), MAPSFolder);
    MapDescriptor *oms = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-OMS.zip", tr("OMS"), MAPSFolder);
    MapDescriptor *tom = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-TOM.zip", tr("TOM"), MAPSFolder);
    requestFileSize(al);
    requestFileSize(ty);
    requestFileSize(kk);
    requestFileSize(alt);
    requestFileSize(kya);
    requestFileSize(irk);
    requestFileSize(kem);
    requestFileSize(nvs);
    requestFileSize(oms);
    requestFileSize(tom);
    QList<MapDescriptor> *mapsSFO = new QList<MapDescriptor>();
    mapsSFO->append(al);
    mapsSFO->append(ty);
    mapsSFO->append(kk);
    mapsSFO->append(alt);
    mapsSFO->append(kya);
    mapsSFO->append(irk);
    mapsSFO->append(kem);
    mapsSFO->append(nvs);
    mapsSFO->append(oms);
    mapsSFO->append(tom);
    sfo->AddMaps(*mapsSFO);

    MapsGroup *dfo = new MapsGroup(tr("DFO"));
    MapDescriptor *bu  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-BU.zip", tr("BU"), MAPSFolder);
    MapDescriptor *sa  = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SA.zip", tr("SA"), MAPSFolder);
    MapDescriptor *zab = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-ZAB.zip", tr("ZAB"), MAPSFolder);
    MapDescriptor *kam = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KAM.zip", tr("KAM"), MAPSFolder);
    MapDescriptor *pri = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-PRI.zip", tr("PRI"), MAPSFolder);
    MapDescriptor *kha = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-KHA.zip", tr("KHA"), MAPSFolder);
    MapDescriptor *amu = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-AMU.zip", tr("AMU"), MAPSFolder);
    MapDescriptor *mag = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-MAG.zip", tr("MAG"), MAPSFolder);
    MapDescriptor *sak = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-SAK.zip", tr("SAK"), MAPSFolder);
    MapDescriptor *yev = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-YEV.zip", tr("YEV"), MAPSFolder);
    MapDescriptor *chu = new MapDescriptor("megamaps.org", "/store/navikey/russia/", "RU-CHU.zip", tr("CHU"), MAPSFolder);
    requestFileSize(bu);
    requestFileSize(sa);
    requestFileSize(zab);
    requestFileSize(kam);
    requestFileSize(pri);
    requestFileSize(kha);
    requestFileSize(amu);
    requestFileSize(mag);
    requestFileSize(sak);
    requestFileSize(yev);
    requestFileSize(chu);
    QList<MapDescriptor> *mapsDFO = new QList<MapDescriptor>();
    mapsDFO->append(bu);
    mapsDFO->append(sa);
    mapsDFO->append(zab);
    mapsDFO->append(kam);
    mapsDFO->append(pri);
    mapsDFO->append(kha);
    mapsDFO->append(amu);
    mapsDFO->append(mag);
    mapsDFO->append(sak);
    mapsDFO->append(yev);
    mapsDFO->append(chu);
    dfo->AddMaps(*mapsDFO);

    MapSet.AddMapsGroup(*russia);
    MapSet.AddMapsGroup(*cfo);
    MapSet.AddMapsGroup(*szfo);
    MapSet.AddMapsGroup(*ufo);
    MapSet.AddMapsGroup(*skfo);
    MapSet.AddMapsGroup(*pfo);
    MapSet.AddMapsGroup(*urfo);
    MapSet.AddMapsGroup(*sfo);
    MapSet.AddMapsGroup(*dfo);
}

void MainWindow::doUpdate(QList<MapDescriptor> *mapsToUpdate, QString folderToSave)
{
    for (MapDescriptor md: *mapsToUpdate)
    {
        ui->progressBarFile->setValue(0);
        Downloader *d = new Downloader();
        d->get(folderToSave, md.GetFullURL());
        connect(d, SIGNAL(updateDownloadProgress(qint64, qint64)), this, SLOT(updateDownloadProgress(qint64, qint64)));
    }
}

void MainWindow::mapInfoUpdated(MapDescriptor *md)
{
    //MapSet.UpdateFileInfo(md);
    for (int i = 0; i < mapsTree->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *topItem = mapsTree->topLevelItem(i);
        for (int j = 0; j < topItem->childCount(); j++)
        {
            QTreeWidgetItem *item = topItem->child(j);
            if (item->text(1) == md->Name)
            {
                item->setText(2, md->FileSizeS);
                item->setText(3, md->DateS);
                if (md->FileExists())
                {
                    if (md->FileIsOlder())
                        item->setCheckState(0, Qt::Checked);
                    else
                        item->setCheckState(0, Qt::Unchecked);
                }
            }
        }
    }
    for (int i = 0; i < MapSet.Groups.size(); i++)
    {
        for (int j = 0; j < MapSet.Groups[i].MapDescriptors.size(); j++)
        {
            if (MapSet.Groups[i].MapDescriptors[j].Name == md->Name)
            {
                MapSet.Groups[i].MapDescriptors[j] = *md;
                break;
            }
        }
    }
}


void MainWindow::on_btnFastUpddate_clicked()
{
    prepareAndUpdateMaps();
}

void MainWindow::on_btnFullUpdate_clicked()
{
    prepareAndUpdateMaps();
}

void MainWindow::prepareAndUpdateMaps()
{
    ui->progressBar->setValue(0);
    totalDownloadedBytes = 0;
    totalSizeOfSelectedMaps = 0;
    prevBytes = 0;
    QList<MapDescriptor> *mapsToUpdate = new QList<MapDescriptor>();
    for (int i = 0; i < mapsTree->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *topItem = mapsTree->topLevelItem(i);
        for (int j = 0; j < topItem->childCount(); j++)
        {
            QTreeWidgetItem *item = topItem->child(j);
            if (item->checkState(0))
            {
                QString mapName = item->text(1);
                if (!mapName.isEmpty())
                {
                    MapDescriptor md = MapSet.Find(mapName);
                    if (!md.Equals(MapDescriptor::Empty))
                    {
                        mapsToUpdate->append(md);
                        totalSizeOfSelectedMaps += md.FileSize;
                    }
                }
            }
        }
    }
    ui->progressBar->setMaximum(totalSizeOfSelectedMaps);
    doUpdate(mapsToUpdate, MAPSFolder);
    delete mapsToUpdate;
}

void MainWindow::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    totalDownloadedBytes += (bytesReceived - prevBytes);
    prevBytes = bytesReceived;
    //if (bytesReceived == bytesTotal) totalDownloadedBytes += bytesReceived;
    //ui->progressBarFile->setMaximum(bytesTotal);
    //ui->progressBarFile->setValue(bytesReceived);
    ui->progressBar->setValue(totalDownloadedBytes);
    qDebug() << QString("%1 [%2]").arg(totalDownloadedBytes).arg(totalSizeOfSelectedMaps);
}


