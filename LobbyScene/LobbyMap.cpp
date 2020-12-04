#include <fstream>
#include "LobbyMap.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"


LobbyMap::LobbyMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;
    // MapSize_ = 11;
    // mapWidth_ = 11;
    // mapHeight_ = 11;
    SetMapArea(11, 11);

    LoadTilesFromCSC("./Resources/Map/Lobby_Map_Factory_Main.csv");
    LoadDetailsFromCSC("./Resources/Map/Lobby_Map_Factory_Details.csv");
    LoadObjectsFromCSC("./Resources/Map/Lobby_Map_Factory_Object.csv");

    //CreateMap();
    //DetailMap();
    //PlaceObjects();

    MenuText.push_back(LP::SetText("Tutorial", sf::Vector2f(CellSize * 1, CellSize * 2), 16));
    MenuText.push_back(LP::SetText("Stage 1", sf::Vector2f(CellSize * 3, CellSize * 2), 16));
    MenuText.push_back(LP::SetText("Test Map", sf::Vector2f(CellSize * 3, CellSize * 6), 16));
    MenuText.push_back(LP::SetText("Music\nSelect", sf::Vector2f(CellSize * 7, CellSize * 2), 16));
    MenuText.push_back(LP::SetText("BPM\nCheck", sf::Vector2f(CellSize * 9, CellSize * 2), 16));
    MenuText.push_back(LP::SetText("Class\nSelect", sf::Vector2f(CellSize * 7, CellSize * 4), 16));
    for (auto i : MenuText) LP::SetTextScale(i, .1f, .1f);
}

LobbyMap::~LobbyMap()
{
    int tileMapKeysLength = tileMapKeys_.size();
    for (int i = 0; i < tileMapKeysLength; i++)
    {
        LP::DeleteSprite(tileMapKeys_[i]);
    }
    for (auto i : MenuText)
    {
        LP::DeleteText(i);
    }
}

void LobbyMap::Draw()
{
    for (int i = 0; i < tileMapKeys_.size(); i++)
    {
        LP::DrawSprite(tileMapKeys_[i]);
    }

    for (int i = 0; i < MenuText.size(); i++)
    {
        LP::DrawText(MenuText[i]);
    }
}