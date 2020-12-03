#include "MapTest.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include <fstream>
#include <cstdlib>
#include "../Map/Room1.h"
#include "../Map/Room2.h"
#include "../Map/Room3.h"

MapTest::MapTest(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{    
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    CreateMap();
    // mapWidth_ = objectMap_.size();
    // mapHeight_ = objectMap_[0].size();
    // PlaceObjectsUsingObjectMap(objectMap_);
}

MapTest::~MapTest()
{
    int tileMapKeysLength = tileMapKeys_.size();
    for (int i = 0; i < tileMapKeysLength; i++)
    {
        LP::DeleteSprite(tileMapKeys_[i]);
    }
}

void MapTest::CreateMap()
{
    sf::Vector2i currentPosition(0, 0);
    Room* prevRoom = new Room1(currentPosition);
    rooms_.push_back(prevRoom);

    prevRoom->SetPlayerRand();

    for (int i = 1; i < 5; i++)
    {
        int temp = rand() % 3;
        Room* currentRoom = nullptr;
        if (temp == 0) currentRoom = new Room1(currentPosition);
        else if (temp == 1) currentRoom = new Room2(currentPosition);
        else currentRoom = new Room3(currentPosition);
        rooms_.push_back(currentRoom);
        bool done = false;
        while (!done)
        {
            currentPosition = sf::Vector2i(prevRoom->GetRoomArea().left, prevRoom->GetRoomArea().top);
            //sf::Vector2i prevRoomHallPoint = prevRoom->GetHallPoints()[rand() % prevRoom->GetHallPoints().size()];

            sf::Vector2i hallPoint = prevRoom->GetHallPoints()[rand() % prevRoom->GetHallPoints().size()] + prevRoom->GetRoomPosition();

            if (hallPoint.x == prevRoom->GetRoomArea().left)//left
            {
                currentPosition = sf::Vector2i(hallPoint.x - currentRoom->GetRoomArea().width, hallPoint.y - 4);
                hallPoint.x--; //makes the calc in the for loop easier
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.x == prevRoom->GetRoomArea().left + prevRoom->GetRoomArea().width - 1)//right
            {
                hallPoint.x++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x, hallPoint.y - 4);
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->GetRoomArea().top)//top
            {
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y - currentRoom->GetRoomArea().height);
                hallPoint.y--; //makes the calc in the for loop easier
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->GetRoomArea().top + prevRoom->GetRoomArea().height - 1)//bottom
            {
                hallPoint.y++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y);
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            if (!done) continue;

            currentRoom->SetRoomPosition(currentPosition);
            for (int i = 0; i < rooms_.size() - 1; i++)
            {
                if (currentRoom->GetRoomArea().intersects(rooms_[i]->GetRoomArea())) 
                {
                    done = false;
                    currentRoom->SetRoomPosition(prevRoom->GetRoomPosition());
                }
            }
        }
        prevRoom = currentRoom;
    }

    for (auto i = rooms_.begin(); i != rooms_.end(); i++)
    {
        for (auto j = next(i); j != rooms_.end(); j++)
        {
            for (auto current : (*i)->GetHallPoints())
            {
                sf::Vector2i wc_current = current + (*i)->GetRoomPosition(); //world coordinate
                for (auto other : (*j)->GetHallPoints())
                {
                    sf::Vector2i wc_other = other + (*j)->GetRoomPosition(); //world coordinate
                    if (sf::Vector2i(wc_current.x - 1, wc_current.y) == wc_other) //left
                    {
                        (*i)->CreateLeftHall(current);
                        (*j)->CreateRightHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x + 1, wc_current.y) == wc_other) //right
                    {
                        (*i)->CreateRightHall(current);
                        (*j)->CreateLeftHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x, wc_current.y - 1) == wc_other) //top
                    {
                        (*i)->CreateUpHall(current);
                        (*j)->CreateDownHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x, wc_current.y + 1) == wc_other) //bottom
                    {
                        (*i)->CreateDownHall(current);
                        (*j)->CreateUpHall(other);
                    }
                }
            }
        }
    }

    rooms_.back()->SetStairRand(transitionManager_->GetSceneID("Stage1_2"));

    for (auto i : rooms_)
    {
        i->SetTiles();
        i->SetEnemiesRand(rand() % 3);
        PlaceObjectsInRoom(i->GetRoomArea(), i->GetRoomObjectMap());
    }

    
}

void MapTest::Draw()
{
    for (auto i : rooms_)
    {
        i->Draw();
    }
}

bool MapTest::IsWall(sf::Vector2f worldCoordinate)
{
    for (auto i : rooms_)
    {
        if (i->GetRoomArea().contains(sf::Vector2i(worldCoordinate.x / CellSize, worldCoordinate.y / CellSize))) return i->IsWall(sf::Vector2i(worldCoordinate.x, worldCoordinate.y)); 
    }
}

void MapTest::RandomRoom(sf::Vector2i position)
{
    rooms_.push_back(new Room1(position));
}