#ifndef ROOM_H_
#define ROOM_H_
#include <vector>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "RoomData.h"

class Room
{
public:
    Room(RoomData* roomData);
    ~Room();
    void Draw(sf::RenderWindow& render_window);


    //Data

    RoomData* GetRoomData() const;
    const std::string& GetRoomDataLocation() const;
    const sf::IntRect& GetRoomArea() const;
    sf::IntRect GetRoomAreaWorldCoordinates() const;
    sf::Vector2i GetRoomPosition() const;
    sf::Vector2i GetRoomPositionWorldCoordinates() const;
    sf::Vector2i GetRoomSize() const;
    const std::vector<sf::Vector2i>& GetHallPoints() const;
    const int GetEnemyCount() const;
    const int GetTransitionID() const;
    const bool PlayerRoom() const;
    const bool StairRoom() const;
    const bool BlockRandSpawn() const;


    //Map blueprint

    void SetRoomMap();
    void SetRoomMap(const std::string& roomDataLocation);
    void CreateLeftHall(sf::Vector2i position);
    void CreateRightHall(sf::Vector2i position);
    void CreateUpHall(sf::Vector2i position);
    void CreateDownHall(sf::Vector2i position);
    std::vector<std::vector<int>> GetRoomMap() const;

    //Details

    // void SetHallPoints(std::vector<sf::Vector2i> hallPoints);
    // void SetHallPoint(sf::Vector2i hallPoint);
    // std::vector<sf::Vector2i> GetHallPoints() const;
    void SetStair(sf::Vector2i stairPosition, int transitionLocID);
    void SetStairRand(int transitionLocID);

    //Set Tiles

    void SetTiles();


    //Objects
    void SetRoomObjectMap(const std::string& roomObjectDataLocation);
    void SetRoomObjectMapNull();
    void SetObject(sf::Vector2i objectPosition, int objectID);
    void SetPlayerRand();
    void SetEnemiesRand(int numOfEnemies);
    std::vector<std::vector<int>> GetRoomObjectMap() const;



    //

    int GetLocation(sf::Vector2i worldCoordinate);
    bool IsWall(sf::Vector2i worldCoordinate);


    //end

    void End();
    
protected:
    const int CellSize{32};

    //std::string roomDataLocation_{""};

    std::vector<std::vector<int>> roomMap_;
    std::vector<std::vector<int>> roomObjectMap_;
    // sf::Vector2i position_{0, 0};
    // int roomWidth_{0};
    // int roomHeight_{0};
    // sf::IntRect roomArea_{0, 0, 0, 0};
    
    //std::vector<sf::Vector2i> hallPoints_;

    //std::vector<int> tileMapKeys_;
    TileMap roomTileMap_;

    //Bools
    // bool playerRoom_{false};
    // bool stairRoom_{false};
    // bool blockRandSpawn_{false};

    RoomData* roomData_{nullptr};
};

#endif