#include "Map1_3.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include <fstream>
#include <cstdlib>

Map1_3::Map1_3(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{    
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    GenerateRandomRoomPlacement();
    CreateMap();
    //PlaceObjects();
    mapWidth_ = objectMap_.size();
    mapHeight_ = objectMap_[0].size();
    PlaceObjectsUsingObjectMap(objectMap_);
}

Map1_3::~Map1_3()
{
    int tileMapKeysLength = tileMapKeys_.size();
    for (int i = 0; i < tileMapKeysLength; i++)
    {
        LP::DeleteSprite(tileMapKeys_[i]);
    }
}

void Map1_3::GenerateRandomRoomPlacement()
{
    int numOfRoomsToPlace = 4; //not including the starting room, so 5 rooms in total
    sf::Vector2f move(0, 0);
    roomCoordinates.push_back(move); //starting coordinates
    srand(time(NULL)); //Needs to be outside the loop to work properly
    while (numOfRoomsToPlace > 0)
    {
        int randDirection = rand() % 4; //4 choices, 4 directions
        if (randDirection == 0) move.x++; //move right
        else if (randDirection == 1) move.x--; //move left
        else if (randDirection == 2) move.y++; //move down
        else move.y--; //move up

        for (int i = 0; i < roomCoordinates.size(); i++)
        {
            if (move == roomCoordinates[i])
            {//if the next room placement is the same as a previous room, try placing it somewhere else
                move = roomCoordinates[roomCoordinates.size() - 1];
                break;
            }
        }

        if (move != roomCoordinates[roomCoordinates.size() - 1])
        {//if the new location is unique add the new coordinate to the list of coordinates
            roomCoordinates.push_back(move);
            numOfRoomsToPlace--;
        }
        else continue;

        //I need to know the extremes of room placement for the next part in the map creating process
        if (move.x > maxRight) maxRight = move.x;
        if (move.x < maxLeft) maxLeft = move.x;
        if (move.y > maxDown) maxDown = move.y;
        if (move.y < maxUp) maxUp = move.y;
    }
    //find the number of rows and collumns of rooms
    mapWidth_ = 1 + maxRight + abs(maxLeft); //starting room + right most room num + left most room num
    mapHeight_ = 1 + maxDown + abs(maxUp);
}

void Map1_3::CreateMap()
{
    //make sure the 2 dimensional vectors that hold the map data are sized correctly
    //uses the width and height found above
    //*10 because the actual room will be 10 x 10 tiles
    std::vector<int> resize(mapHeight_ * 10);
    map_.resize(mapWidth_ * 10, resize);
    objectMap_.resize(mapWidth_ * 10, resize);

    //Translate the room coordinates found in "roomCoordinates" into 10x10 tile rooms and store that info in "map_"
    int x2 = 0; //"map_" x coordinate, starts at 0
    int y2 = 0; //"map_" y coordinate, starts at 0
    bool placePlayer = false;
    int roomNum = 0;
    for (int y = maxUp; y < maxUp + mapHeight_; y++)
    {//start at the left most room
        for (int x = maxLeft; x < maxLeft + mapWidth_; x++)
        {//start at the top most room
            bool buildRoom = false; //is there a room at the current coordinate?
            bool leftNeighbourRoom = false; //is there a room to the left of the current room?
            bool rightNeighbourRoom = false; //is there a room to the right of the current room?
            bool upNeighbourRoom = false; //is there a room to the top of the current room?
            bool downNeighbourRoom = false; //is there a room to the bottom of the current room?

            for (int i = 0; i < roomCoordinates.size(); i++)
            {//if the current coordinate maches a room coordinate, build that room
                if (roomCoordinates[i] == sf::Vector2f(x, y)) buildRoom = true;
            }

            if (buildRoom)
            {//Building a room     
                roomNum++;

                for (int i = 0; i < roomCoordinates.size(); i++)
                {//check other room coordinate to see if they neighbor the current selected room
                    if (roomCoordinates[i] == sf::Vector2f(x - 1, y)) leftNeighbourRoom = true;
                    if (roomCoordinates[i] == sf::Vector2f(x + 1, y)) rightNeighbourRoom = true;
                    if (roomCoordinates[i] == sf::Vector2f(x, y - 1)) upNeighbourRoom = true;
                    if (roomCoordinates[i] == sf::Vector2f(x, y + 1)) downNeighbourRoom = true;
                }
                CreateRoom(sf::Vector2i(x2 * 10, y2 * 10), leftNeighbourRoom, rightNeighbourRoom, upNeighbourRoom, downNeighbourRoom); //pass info to room builder function
                
                if (roomNum == 5)
                {
                    PlaceStaircase(sf::Vector2i(x2 * 10, y2 * 10));
                }

                if (roomNum == 3)
                {
                    PlaceJunkYard(sf::Vector2i(x2 * 10, y2 * 10));
                }

                if (!placePlayer)
                {
                    PlacePlayer(sf::Vector2i(x2 * 10, y2 * 10));
                    placePlayer = true;
                }
                else PlaceEnemy(sf::Vector2i(x2 * 10, y2 * 10));
            }
            else CreateEmptyRoom(sf::Vector2i(x2 * 10, y2 * 10)); //if there is no room to be built at the coordinates, fill "map_" with -1 (empty tiles)
            x2++; //increment "map_" x
        }
        y2++; //increment "map_" y
        x2 = 0; //start of new x line
    }

    //Create tile sprites using "map_" as the blueprint
    for (int y = 0; y < mapHeight_ * 10; y++)
    {
        for (int x = 0; x < mapWidth_ * 10; x++)
        {
            if (map_[x][y] == -1) continue; //-1 = no tile / empty
            tileMapKeys_.push_back(LP::SetSprite(tile_map, sf::Vector2f(x*CellSize, y*CellSize), CellSize, CellSize, map_[x][y]));
        }
    }
}

void Map1_3::CreateRoom(sf::Vector2i position, bool left, bool right, bool up, bool down)
{
    int randomRoom = rand() % 6;

    std::ifstream mapData;
    if (randomRoom == 0) mapData.open("./Resources/Map/Factory_Room01_Main.csv");
    else if (randomRoom == 1) mapData.open("./Resources/Map/Factory_Room02_Main.csv");
    else if (randomRoom == 2) mapData.open("./Resources/Map/Factory_Room03_Main.csv");
    else if (randomRoom == 3) mapData.open("./Resources/Map/Factory_Room04_Main.csv");
    else if (randomRoom == 4) mapData.open("./Resources/Map/Factory_Room05_Main.csv");
    else mapData.open("./Resources/Map/Factory_Room06_Main.csv");
    char dummy;
    for (int y2 = position.y; y2 < position.y + 10; y2++)
    {
        for (int x2 = position.x; x2 < position.x + 10; x2++)
        {
            mapData >> map_[x2][y2];
            if (map_[x2][y2] == 32) map_[x2][y2] = (rand() % 4) + 35; //random wall tiles
            if (map_[x2][y2] == 41) map_[x2][y2] = (rand() % 15) + 41; //random floor tiles
            if (x2 < position.x + 9) 
            {//removes "," 
                mapData >> dummy;
            }
        }
    }
    mapData.close();

    if (left)
    {
        CreateLeftHall(sf::Vector2i(position.x, position.y + 2));
    }
    if (right)
    {
        CreateRightHall(sf::Vector2i(position.x + 9, position.y + 2));
    }
    if (up)
    {
        CreateUpHall(sf::Vector2i(position.x + 3, position.y));
    }
    if (down)
    {
        CreateDownHall(sf::Vector2i(position.x + 3, position.y + 9));
    }
}

void Map1_3::CreateEmptyRoom(sf::Vector2i position)
{
    for (int y2 = position.y; y2 < position.y + 10; y2++)
    {
        for (int x2 = position.x; x2 < position.x + 10; x2++)
        {//empty space, no room
            map_[x2][y2] = -1;
            objectMap_[x2][y2] = -1;
        }
    }
}

void Map1_3::CreateLeftHall(sf::Vector2i position)
{
    std::ifstream mapData("./Resources/Map/Factory_Hall_Left_Main.csv");
    for (int y2 = position.y; y2 < position.y + 5; y2++)
    {
        mapData >> map_[position.x][y2];
        if (map_[position.x][y2] == 41) map_[position.x][y2] = (rand() % 15) + 41; //random floor tiles
    }
    mapData.close();
}

void Map1_3::CreateRightHall(sf::Vector2i position)
{
    std::ifstream mapData("./Resources/Map/Factory_Hall_Right_Main.csv");
    for (int y2 = position.y; y2 < position.y + 5; y2++)
    {
        mapData >> map_[position.x][y2];
        if (map_[position.x][y2] == 41) map_[position.x][y2] = (rand() % 15) + 41; //random floor tiles
    }
    mapData.close();
}

void Map1_3::CreateUpHall(sf::Vector2i position)
{
    std::ifstream mapData("./Resources/Map/Factory_Hall_Top_Main.csv");
    char dummy;
    for (int y2 = position.y; y2 < position.y + 2; y2++)
    {
        for (int x2 = position.x; x2 < position.x + 4; x2++)
        {
            mapData >> map_[x2][y2];
            if (map_[x2][y2] == 41) map_[x2][y2] = (rand() % 15) + 41; //random floor tiles
            if (x2 < position.x + 3) 
            {//removes "," 
                mapData >> dummy;
            }
        }
    }
    mapData.close();
}

void Map1_3::CreateDownHall(sf::Vector2i position)
{
    std::ifstream mapData("./Resources/Map/Factory_Hall_Bottom_Main.csv");
    char dummy;
    for (int x2 = position.x; x2 < position.x + 4; x2++)
    {
        mapData >> map_[x2][position.y];
        if (map_[x2][position.y] == 41) map_[x2][position.y] = (rand() % 15) + 41; //random floor tiles
        if (x2 < position.x + 3) 
        {//removes "," 
            mapData >> dummy;
        }
    }
    mapData.close();
}

void Map1_3::PlacePlayer(sf::Vector2i position)
{
    for (int y = position.y; y < position.y + 10; y++)
    {
        for (int x = position.x; x < position.x + 10; x++)
        {
            objectMap_[x][y] = -1;
        }
    }
    int playerX;
    int playerY;
    int saftyNet = 0;
    bool placePlayer = false;
    while (!placePlayer && saftyNet < 100)
    {
        saftyNet++;
        int playerX = (rand() % 8) + 1 + position.x;
        int playerY = (rand() % 7) + 2 + position.y;
        if (map_[playerX][playerY] >= 41)
        {
            objectMap_[playerX][playerY] = 0;
            placePlayer = true;
        }
    }
}

void Map1_3::PlaceEnemy(sf::Vector2i position)
{
    for (int y = position.y; y < position.y + 10; y++)
    {
        for (int x = position.x; x < position.x + 10; x++)
        {
            if (map_[x][y] == 40) continue;
            else if (objectMap_[x][y] >= 100) continue;
            else if (map_[x][y] < 40) 
            {
                objectMap_[x][y] = -1;
                continue;
            }

            if (rand() % 10 == 0) objectMap_[x][y] = rand() % 4 + 1;
            else objectMap_[x][y] = -1;
        }
    }
}

void Map1_3::PlaceStaircase(sf::Vector2i position)
{
    int saftyNet = 0;
    while (saftyNet < 100)
    {
        saftyNet++;
        int x = (rand() % 8) + 1 + position.x;
        int y = (rand() % 7) + 2 + position.y;
        if (map_[x][y] >= 41)
        {
            map_[x][y] = 40;
            objectMap_[x][y] = transitionManager_->GetSceneID("Lobby");
            //scene_->AddEvent(sf::Vector2f(CellSize * x, CellSize * y), "Stage1_2", scene_);
            return;
        }
    }
}

void Map1_3::PlaceJunkYard(sf::Vector2i position)
{
    int saftyNet = 0;
    while (saftyNet < 100)
    {
        saftyNet++;
        int x = (rand() % 8) + 1 + position.x;
        int y = (rand() % 7) + 2 + position.y;
        if (map_[x][y] >= 41)
        {
            objectMap_[x][y] = transitionManager_->GetSceneID("JunkYard");
            return;
        }
    }
}

// void Map1_3::PlaceObjects()
// {
//     for (int y = 0; y < mapHeight_ * 10; y++)
//     {
//         for (int x = 0; x < mapWidth_ * 10; x ++)
//         {
//             sf::Vector2f position(x*CellSize, y*CellSize);
//             if (objectMap_[x][y] == -1) continue;
//             else if (objectMap_[x][y] == 0) 
//             {
//                 scene_->AddPlayer(sf::Vector2f(CellSize * x, CellSize * y), scene_);
//             }
//             else if (objectMap_[x][y] < 100)
//             {
//                 scene_->AddEnemy(objectMap_[x][y], sf::Vector2f(CellSize * x, CellSize * y), scene_);
//             }
//             else if (objectMap_[x][y] < 200)
//             {
//                 scene_->AddItem(objectMap_[x][y], sf::Vector2f(CellSize * x, CellSize * y), scene_);
//             }
//             else if (objectMap_[x][y] < 300)
//             {
//                 scene_->AddTransition(objectMap_[x][y], sf::Vector2f(CellSize * x, CellSize * y), false, scene_);
//             }
//         }
//     }
// }

void Map1_3::Draw()
{
    for (int i = 0; i < tileMapKeys_.size(); i++)
    {
        LP::DrawSprite(tileMapKeys_[i]);
    }
}