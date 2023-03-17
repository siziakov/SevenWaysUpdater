#ifndef MAPS_H
#define MAPS_H

#include "mapsgroup.h"

class Maps
{
public:
    Maps();
    ~Maps();

    void AddMapsGroup(MapsGroup mapsGroup);
    int Count();

    MapDescriptor Find(QString name);
    void UpdateFileInfo(MapDescriptor md);

    QList<MapsGroup> Groups;
};

#endif // MAPS_H
