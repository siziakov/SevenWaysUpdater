#include "maps.h"

Maps::Maps()
{
    Groups = new QList<MapsGroup>();
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
