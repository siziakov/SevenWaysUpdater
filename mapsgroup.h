#ifndef MAPSGROUP_H
#define MAPSGROUP_H

#include <QString>
#include <QList>

#include "mapdescriptor.h"

class MapsGroup
{
public:
    MapsGroup();
    MapsGroup(QString name);
    ~MapsGroup();

    QString Name;

    QList<MapDescriptor> MapDescriptors;

    void AddMaps(QList<MapDescriptor> maps);
    int Count();

    MapDescriptor Find(QString name);
    void UpdateFileInfo(MapDescriptor md);
};

#endif // MAPSGROUP_H
