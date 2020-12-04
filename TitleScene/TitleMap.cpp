#include <SFML/Graphics.hpp>
#include <fstream>
#include "TitleMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"

TitleMap::TitleMap(Scene *scene)
{
    scene_ = scene;
    mapWidth_ = 60;
    mapHeight_ = 10;
    SetMapArea(60, 10);

    LoadTilesFromCSC("./Resources/Map/Title_Map_Factory_Main.csv");
    LoadDetailsFromCSC("./Resources/Map/Title_Map_Factory_Detail.csv");
}