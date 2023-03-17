#include "maps.h"

Maps::Maps()
{
    //Groups = new QList<MapsGroup>();
}

Maps::~Maps()
{
    Groups.clear();
}

void Maps::AddMapsGroup(MapsGroup mapsGroup)
{
    Groups.append(mapsGroup);
}

int Maps::Count()
{
    return Groups.size();
}

MapDescriptor Maps::Find(QString name)
{
    for (MapsGroup mg: Groups)
    {
        MapDescriptor md = mg.Find(name);
        if (!md.Equals(MapDescriptor::Empty))
            return md;
    }
    return MapDescriptor::Empty;
}

void Maps::UpdateFileInfo(MapDescriptor md)
{
    for (MapsGroup mg: Groups)
    {
        mg.UpdateFileInfo(md);
    }
}
