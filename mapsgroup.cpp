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
}

int MapsGroup::Count()
{
    return MapDescriptors.size();
}

MapDescriptor MapsGroup::Find(QString name)
{
    for (MapDescriptor md: MapDescriptors)
    {
        if (QString::compare(name, md.Name) == 0)
            return md;
    }
    return MapDescriptor::Empty;
}

void MapsGroup::UpdateFileInfo(MapDescriptor md)
{
    for (MapDescriptor map: MapDescriptors)
    {
        if (QString::compare(map.Name, md.Name) == 0)
        {
            map = md;
            //map.UpdateFileInfo(md);
            break;
        }
    }
}
