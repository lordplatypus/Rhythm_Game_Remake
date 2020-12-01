#ifndef ROOM_H_
#define ROOM_H_
#include <vector>
#include <SFML/Graphics.hpp>

class Room
{
public:
    Room();
    ~Room();
    void Draw();


    //Setup

    void SetRoomArea(int left, int top, int width, int height);
    void SetRoomArea(sf::IntRect area);
    sf::IntRect GetRoomArea() const;
    void SetRoomPosition(sf::Vector2i position);
    sf::Vector2i GetRoomPosition() const;


    //Map blueprint

    void SetRoomMap();
    void SetRoomMap(const std::string& roomDataLocation);
    void CreateLeftHall(sf::Vector2i position);
    void CreateRightHall(sf::Vector2i position);
    void CreateUpHall(sf::Vector2i position);
    void CreateDownHall(sf::Vector2i position);
    std::vector<std::vector<int>> GetRoomMap() const;

    virtual void SetRoomObjectMap();
    std::vector<std::vector<int>> GetRoomObjectMap() const;


    //Details

    void SetHallPoints(std::vector<sf::Vector2i> hallPoints);
    void SetHallPoint(sf::Vector2i hallPoint);
    std::vector<sf::Vector2i> GetHallPoints() const;
    bool CheckForHallConnection(std::vector<sf::Vector2i> other);


    //Set Tiles

    void SetTiles();



    //

    int GetLocation(sf::Vector2i worldCoordinate);
    bool IsWall(sf::Vector2i worldCoordinate);
    bool PlayerRoom() const;
    bool StairRoom() const;


    //end

    void End();
    
protected:
    const int CellSize{32};

    std::string roomDataLocation_{""};

    std::vector<std::vector<int>> roomMap_;
    std::vector<std::vector<int>> roomObjectMap_;
    sf::Vector2i position_{0, 0};
    int roomWidth_{0};
    int roomHeight_{0};
    sf::IntRect roomArea_{0, 0, 0, 0};
    
    std::vector<sf::Vector2i> hallPoints_;

    std::vector<int> tileMapKeys_;

    //Bools
    bool playerRoom_{false};
    bool stairRoom_{false};
};

#endif