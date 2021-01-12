#include "RoomData.h"

RoomData::RoomData(const std::string& roomDataLocation, const sf::IntRect& roomArea, const std::vector<sf::Vector2i>& hallPoints, int enemyCount, int transitionID, bool playerRoom, bool stairRoom, bool blockRandSpawn) :
    roomDataLocation_{roomDataLocation}, roomArea_{roomArea}, hallPoints_{hallPoints}, enemyCount_{enemyCount}, transitionID_{transitionID}, playerRoom_{playerRoom}, stairRoom_{stairRoom}, blockRandSpawn_{blockRandSpawn} {}


sf::Vector2i RoomData::GetPosition() const
{
    return sf::Vector2i(roomArea_.left, roomArea_.top);
}

void RoomData::SetPosition(const sf::Vector2i& position)
{
    roomArea_.left = position.x;
    roomArea_.top = position.y;
}

sf::Vector2i RoomData::GetSize() const
{
    return sf::Vector2i(roomArea_.width, roomArea_.height);
}

void RoomData::SetSize(const sf::Vector2i& size)
{
    roomArea_.width = size.x;
    roomArea_.height = size.y;
}