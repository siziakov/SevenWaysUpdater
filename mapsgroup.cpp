#include "mapsgroup.h"

MapsGroup::MapsGroup()
{
}

MapsGroup::MapsGroup(QString name): MapsGroup()
{
    this->Name = name;
}

MapsGroup::~MapsGroup()
{
    MapDescriptors.clear();
}

void MapsGroup::AddMaps(QList<MapDescriptor> maps)
{
    MapDescriptors = maps;
//    for (MapDescriptor map : maps)
//    {
//        MapDescriptors.push_back(map);
//    }
}

int MapsGroup::Count()
{
    return MapDescriptors.size();
}
