#include "MultiRoomMap.h"

MultiRoomMap::MultiRoomMap(const int numOfRooms, const std::string& transitionTo, Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager,  GlobalEnemyManager* globalEnemyManager,TransitionManager* transitionManager, ParticleManager* particleManager)
{
    numOfRooms_ = numOfRooms;
    transitionTo_ = transitionTo;

    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    globalEnemyManager_ = globalEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    SetRoomPositions(numOfRooms_); //put rooms into position
    SetRoomTileMap(); //generate room maps
    SetRoomHalls(); //generate halls between rooms
    SetRoomObjectMap(); //generate room object maps
    SetRoomObjects(); //place objects in rooms
    SetRoomTileMapSprite(); //create tilemap sprites for each room
}

MultiRoomMap::~MultiRoomMap()
{
    for (auto room : rooms_) delete room;
}

void MultiRoomMap::Draw(sf::RenderWindow& render_window)
{
    for (auto i : rooms_)
    {
        if (camera_->GetCameraRect().intersects(i->GetRoomAreaWorldCoordinates()))
            i->Draw(render_window);
    }
}

std::vector<sf::IntRect> MultiRoomMap::GetMapArea() const
{
    std::vector<sf::IntRect> temp;
    for (auto room : rooms_)
    {
        temp.push_back(room->GetRoomArea());
    }
    return temp;
}

bool MultiRoomMap::IsWall(sf::Vector2f worldCoordinate)
{
    for (auto i : rooms_)
    {
        if (i->GetRoomArea().contains(sf::Vector2i(worldCoordinate.x / CellSize, worldCoordinate.y / CellSize))) return i->IsWall(sf::Vector2i(worldCoordinate.x, worldCoordinate.y)); 
    }
    return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 1: Place rooms in sensable positions (rooms don't collide / hallways can be placed between rooms)
////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiRoomMap::SetRoomPositions(int numOfRooms)
{
    sf::Vector2i currentPosition(0, 0); //starting position is always (0, 0)
    Room* prevRoom = GetRandRoom(currentPosition, 0, numOfRooms); //create first room
    rooms_.push_back(prevRoom);

    for (int i = 1; i < numOfRooms; i++)
    {
        Room* currentRoom = GetRandRoom(currentPosition, i, numOfRooms);
        bool done = false;
        int changeRoom = 0;
        while (!done)
        {
            currentPosition = prevRoom->GetRoomPosition();

            changeRoom++;
            if (changeRoom >= 10)
            {//if the program fails to place a room 10 times, try a different room
                changeRoom = 0;
                delete currentRoom;
                currentRoom = GetRandRoom(currentPosition, i, numOfRooms);
            }

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
                if (currentRoom->GetRoomArea().intersects(rooms_[i]->GetRoomArea()) || currentRoom->GetRoomPosition() == rooms_[i]->GetRoomPosition())
                {
                    done = false;
                    prevRoom = rooms_[rand() % (rooms_.size() - 1)];
                    currentRoom->SetRoomPosition(prevRoom->GetRoomPosition());
                }
            }
        }
        //Succeded in placing a room
        rooms_.push_back(currentRoom); //add the new room to the vector of rooms
        prevRoom = currentRoom; //set up the new starting position for the next room
    }
}

Room* MultiRoomMap::GetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum)
{
    Room* room;
    std::string roomName = "";
    sf::IntRect roomArea;
    std::vector<sf::Vector2i> hallPoints;

    if (roomBuildOrderNum == 0)
    {
        roomName = "Factory_Room_9x9_01";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        room = new Room(roomName, roomArea, hallPoints);
        return room;
    }

    int randRoom = rand() % 15;
    switch (randRoom)
    {
        case 0:
        if (roomBuildOrderNum != 0 && roomBuildOrderNum != maxRoomNum - 1) 
        {
            roomName = "Factory_Room_Junkyard";
            roomArea = sf::IntRect(position.x, position.y, 9, 14);
            hallPoints.push_back(sf::Vector2i(0, 9)); //left anchor
            hallPoints.push_back(sf::Vector2i(4, 13)); //top anchor
            hallPoints.push_back(sf::Vector2i(8, 9)); //right anchor
            break;
        }
        roomName = "Factory_Room_9x9_01";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 1:
        roomName = "Factory_Room_9x9_01";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 2:
        roomName = "Factory_Room_9x9_02";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 3:
        roomName = "Factory_Room_9x9_03";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 4:
        roomName = "Factory_Room_9x9_04";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 5:
        roomName = "Factory_Room_9x9_05";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        break;

        case 6:
        roomName = "Factory_Room_9x9_06";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        break;

        case 7:
        roomName = "Factory_Room_9x9_07";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 8:
        roomName = "Factory_Room_9x9_08";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 9:
        roomName = "Factory_Room_9x15_01";
        roomArea = sf::IntRect(position.x, position.y, 9, 15);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(0, 7));
        hallPoints.push_back(sf::Vector2i(0, 11));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(8, 4));
        hallPoints.push_back(sf::Vector2i(8, 7));
        hallPoints.push_back(sf::Vector2i(8, 11));
        hallPoints.push_back(sf::Vector2i(4, 14));
        break;

        case 10:
        roomName = "Factory_Room_9x15_02";
        roomArea = sf::IntRect(position.x, position.y, 9, 15);
        hallPoints.push_back(sf::Vector2i(0, 7));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(8, 7));
        hallPoints.push_back(sf::Vector2i(4, 14));
        break;

        case 11:
        roomName = "Factory_Room_9x18_01";
        roomArea = sf::IntRect(position.x, position.y, 9, 18);
        hallPoints.push_back(sf::Vector2i(4, 0)); //N
        hallPoints.push_back(sf::Vector2i(0, 4)); //W
        hallPoints.push_back(sf::Vector2i(0, 13)); //W
        hallPoints.push_back(sf::Vector2i(4, 17)); //S
        hallPoints.push_back(sf::Vector2i(8, 4)); //E
        hallPoints.push_back(sf::Vector2i(8, 13)); //E
        break;

        case 12:
        roomName = "Factory_Room_9x18_02";
        roomArea = sf::IntRect(position.x, position.y, 9, 18);
        hallPoints.push_back(sf::Vector2i(0, 4)); //W
        hallPoints.push_back(sf::Vector2i(0, 13)); //W
        hallPoints.push_back(sf::Vector2i(4, 17)); //S
        hallPoints.push_back(sf::Vector2i(8, 4)); //E
        hallPoints.push_back(sf::Vector2i(8, 13)); //E
        break;

        case 13:
        roomName = "Factory_Room_15x9_01";
        roomArea = sf::IntRect(position.x, position.y, 15, 9);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(7, 0));
        hallPoints.push_back(sf::Vector2i(10, 0));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(14, 4));
        hallPoints.push_back(sf::Vector2i(4, 8));
        hallPoints.push_back(sf::Vector2i(7, 8));
        hallPoints.push_back(sf::Vector2i(10, 8));
        break;

        case 14:
        roomName = "Factory_Room_18x9_01";
        roomArea = sf::IntRect(position.x, position.y, 18, 9);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(13, 0));
        hallPoints.push_back(sf::Vector2i(17, 4));
        hallPoints.push_back(sf::Vector2i(4, 8));
        hallPoints.push_back(sf::Vector2i(13, 8));
        break;

        default:
        break;
    }

    room = new Room(roomName, roomArea, hallPoints);
    
    return room;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 2: Generate room maps - includes hallway generation
////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiRoomMap::SetRoomTileMap()
{
    for (auto room : rooms_)
    {
        std::string roomName = room->GetRoomName();
        if (roomName == "Factory_Room_9x9_01") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_01.csv");
        else if (roomName == "Factory_Room_9x9_02") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_02.csv");
        else if (roomName == "Factory_Room_9x9_03") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_03.csv");
        else if (roomName == "Factory_Room_9x9_04") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_04.csv");
        else if (roomName == "Factory_Room_9x9_05") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_05.csv");
        else if (roomName == "Factory_Room_9x9_06") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_06.csv");
        else if (roomName == "Factory_Room_9x9_07") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_07.csv");
        else if (roomName == "Factory_Room_9x9_08") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x9_08.csv");
        else if (roomName == "Factory_Room_9x15_01") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x15_01.csv");
        else if (roomName == "Factory_Room_9x15_02") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x15_02.csv");
        else if (roomName == "Factory_Room_9x18_01") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x18_01.csv");
        else if (roomName == "Factory_Room_9x18_02") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_9x18_02.csv");
        else if (roomName == "Factory_Room_15x9_01") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_15x9_01.csv");
        else if (roomName == "Factory_Room_18x9_01") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_18x9_01.csv");
        else if (roomName == "Factory_Room_Junkyard") room->SetRoomTileMap("./Resources/Map/Room/Factory_Room_Junkyard.csv");
    }
}

void MultiRoomMap::SetRoomHalls()
{
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
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 3: Place objects in rooms
////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiRoomMap::SetRoomObjectMap()
{
    int count = 0;
    for (auto room : rooms_)
    {
        room->SetRoomObjectMapNull(); //initial setup

        if (count == 0) 
        {//The first will generate the player
            room->SetPlayerRand();
            count++;
            continue; //skip enemy generation, etc.
        }
        else if (count == numOfRooms_ - 1) room->SetStairRand(transitionManager_->GetSceneID(transitionTo_)); //last room will generate the staircase

        std::string roomName = room->GetRoomName();

        if (roomName != "Factory_Room_Junkyard") room->SetEnemiesRand(rand() % 5); //generate enemies

        if (roomName == "Factory_Room_Junkyard")
        {//special rules for junkyard room
            std::vector<int> placedItems;
            std::vector<sf::Vector2i> itemPositions
            {
                sf::Vector2i(2, 7),
                sf::Vector2i(4, 7),
                sf::Vector2i(6, 7)
            };

            for (int i = 0; i < 3; i++)
            {
                bool done = false;
                int failsafe = 0;
                while(!done)
                {
                    done = true;
                    int randItemID = rand() % 8 + 101; //pick random item
                    for (auto i : placedItems)
                    {//checks for duplicate items
                        if (i == randItemID) done = false;
                    }
                    if (done)
                    {//if not duplicate add ID to object map
                        room->SetObject(itemPositions[i], randItemID);
                        placedItems.push_back(randItemID);
                    }

                    failsafe++; //if for some reason the above code fails 100 times, break out of loop
                    if (failsafe >= 100) done = true;
                }
            }
        }
        count++;
    }
}

void MultiRoomMap::SetRoomObjects()
{
    for (auto i : rooms_)
    {
        PlaceObjectsInRoom(i->GetRoomArea(), i->GetRoomObjectMap());
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 4: Create tilemap sprites
////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiRoomMap::SetRoomTileMapSprite()
{
    for (auto i : rooms_)
    {
        i->SetTileMapSprite();
    }
}