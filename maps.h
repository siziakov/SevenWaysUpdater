#ifndef MAPS_H
#define MAPS_H

#include "mapsgroup.h"

class Maps
{
public:
    Maps();
    ~Maps();

    void AddMapsGroup(MapsGroup *mapsGroup);
    int Count();

    QList<MapsGroup> *Groups;
};

#endif // MAPS_H
