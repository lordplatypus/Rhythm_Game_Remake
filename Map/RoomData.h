#ifndef ROOM_DATA_H_
#define ROOM_DATA_H_
#include <SFML/Graphics.hpp>

struct RoomData
{
    RoomData() = default;
    RoomData(const std::string& roomDataLocation, const sf::IntRect& roomArea, const std::vector<sf::Vector2i>& hallPoints, int enemyCount, int transitionID = -1, bool playerRoom = false, bool stairRoom = false, bool blockRandSpawn = false);

    sf::Vector2i GetPosition() const;
    void SetPosition(const sf::Vector2i& position);
    sf::Vector2i GetSize() const;
    void SetSize(const sf::Vector2i& size);

    std::string roomDataLocation_{""};
    sf::IntRect roomArea_{0, 0, 0, 0}; //holds: room world coordinates, room width, and room height
    std::vector<sf::Vector2i> hallPoints_; //where hallways to other rooms can spawn
    int enemyCount_{0}; //how many enemies will spawn in the room

    bool playerRoom_{false}; //is the room where the player spawns?
    bool stairRoom_{false}; //is the room where the staircase spawns?
    bool blockRandSpawn_{false}; //should this room block objects from spawning (playerRoom_ bool overrides this)

    int transitionID_{-1};
};

#endif