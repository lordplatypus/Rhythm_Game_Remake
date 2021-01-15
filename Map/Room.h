#ifndef ROOM_H_
#define ROOM_H_
#include <vector>
#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Room
{
public:
    Room(const std::string& name, const sf::IntRect& roomArea, const std::vector<sf::Vector2i>& hallPoints);
    ~Room();
    void Draw(sf::RenderWindow& render_window);


    //Get Data
    const std::string& GetRoomName() const;
    const sf::IntRect& GetRoomArea() const;
    sf::IntRect GetRoomAreaWorldCoordinates() const;
    sf::Vector2i GetRoomPosition() const;
    sf::Vector2i GetRoomPositionWorldCoordinates() const;
    sf::Vector2i GetRoomSize() const;
    const std::vector<sf::Vector2i>& GetHallPoints() const;
    // const int GetEnemyCount() const;
    // const int GetTransitionID() const;
    // const bool PlayerRoom() const;
    // const bool StairRoom() const;
    // const bool BlockRandSpawn() const;
    std::vector<std::vector<int>> GetRoomMap() const;
    std::vector<std::vector<int>> GetRoomObjectMap() const;

    //Set room position
    void SetRoomPosition(const sf::Vector2i& position);

    //Map Generation (filling the maps with numbers / placing tiles comes later)
    void SetRoomTileMap(const std::string& roomDataLocation);
    void CreateLeftHall(sf::Vector2i position);
    void CreateRightHall(sf::Vector2i position);
    void CreateUpHall(sf::Vector2i position);
    void CreateDownHall(sf::Vector2i position);

    //Objects
    void SetRoomObjectMap(const std::string& roomObjectDataLocation);
    void SetRoomObjectMapNull();
    void SetObject(sf::Vector2i objectPosition, int objectID);
    void SetPlayerRand();
    void SetStair(sf::Vector2i stairPosition, int transitionLocID);
    void SetStairRand(int transitionLocID);
    void SetEnemiesRand(int numOfEnemies);

    //Set Tiles / Create ilemap sprites
    void SetTileMapSprite();

    //For Collision
    int GetLocation(sf::Vector2i worldCoordinate);
    bool IsWall(sf::Vector2i worldCoordinate);

    //end
    void End();
    
protected:
    std::string name_{""};
    const int CellSize{32};

    //std::string roomDataLocation_{""};

    std::vector<std::vector<int>> roomMap_;
    std::vector<std::vector<int>> roomObjectMap_;
    sf::IntRect roomArea_{0, 0, 0, 0};
    std::vector<sf::Vector2i> hallPoints_;
    TileMap roomTileMap_;

    // int enemyCount_{0};
    // int transitionID_{0};

    //Bools
    // bool playerRoom_{false};
    // bool stairRoom_{false};
    // bool blockRandSpawn_{false};
};

#endif