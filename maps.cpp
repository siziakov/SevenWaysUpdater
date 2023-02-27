#include "maps.h"

Maps::Maps()
{
    Groups = new QList<MapsGroup>();
//    initMaps();
}

Maps::~Maps()
{
    Groups->clear();
}

void Maps::AddMapsGroup(MapsGroup *mapsGroup)
{
    Groups->append(*mapsGroup);
}

int Maps::Count()
{
    return Groups->size();
}

//void Maps::initMaps()
//{
//    russia = MapsGroup(tr("RUSSIA"));
//    adm = MapDescriptor("megamaps.org", "/store/navikey/russia/russia_adm.zip", tr("ADM"));
//    mapsADM.push_back(adm);
//    russia.AddMaps(mapsADM);
//    Groups.push_back(russia);
//    return;

//    MapsGroup *cfo = new MapsGroup(tr("CFO"));
//    MapDescriptor *bel = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-BEL.zip"), tr("BEL"));
//    MapDescriptor *bry = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-BRY.zip"), tr("BRY"));
//    MapDescriptor *vla = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-VLA.zip"), tr("VLA"));
//    MapDescriptor *vor = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-VOR.zip"), tr("VOR"));
//    MapDescriptor *iva = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-IVA.zip"), tr("IVA"));
//    MapDescriptor *klu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KLU.zip"), tr("KLU"));
//    MapDescriptor *kos = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KOS.zip"), tr("KOS"));
//    MapDescriptor *krs = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KRS.zip"), tr("KRS"));
//    MapDescriptor *lip = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-LIP.zip"), tr("LIP"));
//    MapDescriptor *mow = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-MOW.zip"), tr("MOW"));
//    MapDescriptor *mos = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-MOS.zip"), tr("MOS"));
//    MapDescriptor *orl = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ORL.zip"), tr("ORL"));
//    MapDescriptor *rya = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-RYA.zip"), tr("RYA"));
//    MapDescriptor *smo = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SMO.zip"), tr("SMO"));
//    MapDescriptor *tam = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TAM.zip"), tr("TAM"));
//    MapDescriptor *tve = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TVE.zip"), tr("TVE"));
//    MapDescriptor *tul = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TUL.zip"), tr("TUL"));
//    MapDescriptor *yar = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-YAR.zip"), tr("YAR"));
//    QList<MapDescriptor> mapsCFO;
//    mapsCFO.append(*bel);
//    mapsCFO.append(*bry);
//    mapsCFO.append(*vla);
//    mapsCFO.append(*vor);
//    mapsCFO.append(*iva);
//    mapsCFO.append(*klu);
//    mapsCFO.append(*kos);
//    mapsCFO.append(*krs);
//    mapsCFO.append(*lip);
//    mapsCFO.append(*mow);
//    mapsCFO.append(*mos);
//    mapsCFO.append(*orl);
//    mapsCFO.append(*rya);
//    mapsCFO.append(*smo);
//    mapsCFO.append(*tam);
//    mapsCFO.append(*tve);
//    mapsCFO.append(*tul);
//    mapsCFO.append(*yar);
//    cfo->AddMaps(mapsCFO);

//    MapsGroup *szfo = new MapsGroup(tr("SZFO"));
//    MapDescriptor *kr = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KR.zip"), tr("KR"));
//    MapDescriptor *ko = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KO.zip"), tr("KO"));
//    MapDescriptor *ark = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ARK.zip"), tr("ARK"));
//    MapDescriptor *vlg = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-VLG.zip"), tr("VLG"));
//    MapDescriptor *kgd = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KGD.zip"), tr("KGD"));
//    MapDescriptor *len = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-LEN.zip"), tr("LEN"));
//    MapDescriptor *mur = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-MUR.zip"), tr("MUR"));
//    MapDescriptor *ngr = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-NGR.zip"), tr("NGR"));
//    MapDescriptor *psk = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-PSK.zip"), tr("PSK"));
//    MapDescriptor *spe = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SPE.zip"), tr("SPE"));
//    MapDescriptor *nen = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-NEN.zip"), tr("NEN"));
//    QList<MapDescriptor> mapsSZFO;
//    mapsSZFO.append(*kr);
//    mapsSZFO.append(*ko);
//    mapsSZFO.append(*ark);
//    mapsSZFO.append(*vlg);
//    mapsSZFO.append(*kgd);
//    mapsSZFO.append(*len);
//    mapsSZFO.append(*mur);
//    mapsSZFO.append(*ngr);
//    mapsSZFO.append(*psk);
//    mapsSZFO.append(*spe);
//    mapsSZFO.append(*nen);
//    szfo->AddMaps(mapsSZFO);

//    MapsGroup *ufo = new MapsGroup(tr("UFO"));
//    MapDescriptor *ad = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-AD.zip"), tr("AD"));
//    MapDescriptor *kl = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KL.zip"), tr("KL"));
//    MapDescriptor *krm = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KRM.zip"), tr("KRM"));
//    MapDescriptor *kda = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KDA.zip"), tr("KDA"));
//    MapDescriptor *ast = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-AST.zip"), tr("AST"));
//    MapDescriptor *vgg = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-VGG.zip"), tr("VGG"));
//    MapDescriptor *ros = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ROS.zip"), tr("ROS"));
//    MapDescriptor *sev = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SEV.zip"), tr("SEV"));
//    QList<MapDescriptor> mapsUFO;
//    mapsUFO.append(*ad);
//    mapsUFO.append(*kl);
//    mapsUFO.append(*krm);
//    mapsUFO.append(*kda);
//    mapsUFO.append(*ast);
//    mapsUFO.append(*vgg);
//    mapsUFO.append(*ros);
//    mapsUFO.append(*sev);
//    ufo->AddMaps(mapsUFO);

//    MapsGroup *skfo = new MapsGroup(tr("SKFO"));
//    MapDescriptor *da = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-DA.zip"), tr("DA"));
//    MapDescriptor *in = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-IN.zip"), tr("IN"));
//    MapDescriptor *kb = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KB.zip"), tr("KB"));
//    MapDescriptor *kc = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KC.zip"), tr("KC"));
//    MapDescriptor *se = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SE.zip"), tr("SE"));
//    MapDescriptor *ce = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-CE.zip"), tr("CE"));
//    MapDescriptor *sta = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-STA.zip"), tr("STA"));
//    QList<MapDescriptor> mapsSKFO;
//    mapsSKFO.append(*da);
//    mapsSKFO.append(*in);
//    mapsSKFO.append(*kb);
//    mapsSKFO.append(*kc);
//    mapsSKFO.append(*se);
//    mapsSKFO.append(*ce);
//    mapsSKFO.append(*sta);
//    skfo->AddMaps(mapsSKFO);

//    MapsGroup *pfo = new MapsGroup(tr("PFO"));
//    MapDescriptor *ba = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-BA.zip"), tr("BA"));
//    MapDescriptor *me = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ME.zip"), tr("ME"));
//    MapDescriptor *mo = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-MO.zip"), tr("MO"));
//    MapDescriptor *ta = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TA.zip"), tr("TA"));
//    MapDescriptor *ud = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-UD.zip"), tr("UD"));
//    MapDescriptor *cu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-CU.zip"), tr("CU"));
//    MapDescriptor *per = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-PER.zip"), tr("PER"));
//    MapDescriptor *kir = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KIR.zip"), tr("KIR"));
//    MapDescriptor *niz = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-NIZ.zip"), tr("NIZ"));
//    MapDescriptor *ore = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ORE.zip"), tr("ORE"));
//    MapDescriptor *pnz = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-PNZ.zip"), tr("PNZ"));
//    MapDescriptor *sam = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SAM.zip"), tr("SAM"));
//    MapDescriptor *sar = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SAR.zip"), tr("SAR"));
//    MapDescriptor *uly = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ULY.zip"), tr("ULY"));
//    QList<MapDescriptor> mapsPFO;
//    mapsPFO.append(*ba);
//    mapsPFO.append(*me);
//    mapsPFO.append(*mo);
//    mapsPFO.append(*ta);
//    mapsPFO.append(*ud);
//    mapsPFO.append(*cu);
//    mapsPFO.append(*per);
//    mapsPFO.append(*kir);
//    mapsPFO.append(*niz);
//    mapsPFO.append(*ore);
//    mapsPFO.append(*pnz);
//    mapsPFO.append(*sam);
//    mapsPFO.append(*sar);
//    mapsPFO.append(*uly);
//    pfo->AddMaps(mapsPFO);

//    MapsGroup *urfo = new MapsGroup(tr("URFO"));
//    MapDescriptor *kgn = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KGN.zip"), tr("KGN"));
//    MapDescriptor *sve = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SVE.zip"), tr("SVE"));
//    MapDescriptor *tyu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TYU.zip"), tr("TYU"));
//    MapDescriptor *che = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-CHE.zip"), tr("CHE"));
//    MapDescriptor *khm = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KHM.zip"), tr("KHM"));
//    MapDescriptor *yan = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-YAN.zip"), tr("YAN"));
//    QList<MapDescriptor> mapsURFO;
//    mapsURFO.append(*kgn);
//    mapsURFO.append(*sve);
//    mapsURFO.append(*tyu);
//    mapsURFO.append(*che);
//    mapsURFO.append(*khm);
//    mapsURFO.append(*yan);
//    urfo->AddMaps(mapsURFO);

//    MapsGroup *sfo = new MapsGroup(tr("SFO"));
//    MapDescriptor *al = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-AL.zip"), tr("AL"));
//    MapDescriptor *ty = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TY.zip"), tr("TY"));
//    MapDescriptor *kk = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KK.zip"), tr("KK"));
//    MapDescriptor *alt = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ALT.zip"), tr("ALT"));
//    MapDescriptor *kya = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KYA.zip"), tr("KYA"));
//    MapDescriptor *irk = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-IRK.zip"), tr("IRK"));
//    MapDescriptor *kem = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KEM.zip"), tr("KEM"));
//    MapDescriptor *nvs = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-NVS.zip"), tr("NVS"));
//    MapDescriptor *oms = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-OMS.zip"), tr("OMS"));
//    MapDescriptor *tom = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-TOM.zip"), tr("TOM"));
//    QList<MapDescriptor> mapsSFO;
//    mapsSFO.append(*al);
//    mapsSFO.append(*ty);
//    mapsSFO.append(*kk);
//    mapsSFO.append(*alt);
//    mapsSFO.append(*kya);
//    mapsSFO.append(*irk);
//    mapsSFO.append(*kem);
//    mapsSFO.append(*nvs);
//    mapsSFO.append(*oms);
//    mapsSFO.append(*tom);
//    sfo->AddMaps(mapsSFO);

//    MapsGroup *dfo = new MapsGroup(tr("DFO"));
//    MapDescriptor *bu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-BU.zip"), tr("BU"));
//    MapDescriptor *sa = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SA.zip"), tr("SA"));
//    MapDescriptor *zab = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-ZAB.zip"), tr("ZAB"));
//    MapDescriptor *kam = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KAM.zip"), tr("KAM"));
//    MapDescriptor *pri = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-PRI.zip"), tr("PRI"));
//    MapDescriptor *kha = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-KHA.zip"), tr("KHA"));
//    MapDescriptor *amu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-AMU.zip"), tr("AMU"));
//    MapDescriptor *mag = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-MAG.zip"), tr("MAG"));
//    MapDescriptor *sak = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-SAK.zip"), tr("SAK"));
//    MapDescriptor *yev = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-YEV.zip"), tr("YEV"));
//    MapDescriptor *chu = new MapDescriptor(tr("megamaps.org"), tr("/store/navikey/russia/RU-CHU.zip"), tr("CHU"));
//    QList<MapDescriptor> mapsDFO;
//    mapsDFO.append(*bu);
//    mapsDFO.append(*sa);
//    mapsDFO.append(*zab);
//    mapsDFO.append(*kam);
//    mapsDFO.append(*pri);
//    mapsDFO.append(*kha);
//    mapsDFO.append(*amu);
//    mapsDFO.append(*mag);
//    mapsDFO.append(*sak);
//    mapsDFO.append(*yev);
//    mapsDFO.append(*chu);
//    dfo->AddMaps(mapsDFO);

//    Groups.append(russia);
//    Groups.append(*cfo);
//    Groups.append(*szfo);
//    Groups.append(*ufo);
//    Groups.append(*skfo);
//    Groups.append(*pfo);
//    Groups.append(*urfo);
//    Groups.append(*sfo);
//    Groups.append(*dfo);
//}
