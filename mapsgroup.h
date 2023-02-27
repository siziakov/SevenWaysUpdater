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
};

#endif // MAPSGROUP_H
