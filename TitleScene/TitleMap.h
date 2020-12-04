#ifndef TITLE_MAP_H_
#define TITLE_MAP_H_
#include "../Map/SingleRoomMap.h"
#include "../Scene/Scene.h"

class TitleMap : public SingleRoomMap
{
public:
    TitleMap(Scene *scene);
};

#endif