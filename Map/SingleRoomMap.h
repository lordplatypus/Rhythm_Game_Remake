#ifndef SINGLE_ROOM_MAP_H_
#define SINGLE_ROOM_MAP_H_
#include "Map.h"

class SingleRoomMap : public Map
{
public:
    SingleRoomMap();
    ~SingleRoomMap();
    virtual void Draw(const sf::RenderWindow& render_window) override;
    void SetMapArea(int width, int height);
    std::vector<sf::IntRect> GetMapArea() const override;
    virtual bool IsWall(sf::Vector2f worldCoordinate) override;
    int GetLocation(sf::Vector2f worldCoordinate);

    virtual void LoadTilesFromCSC(const std::string& CSCFilePath);
    virtual void LoadDetailsFromCSC(const std::string& CSCFilePath);
    virtual void LoadObjectsFromCSC(const std::string& CSCFilePath);

protected:
    std::vector<std::vector<int> > map_;
    std::vector<std::vector<int> > objectMap_;
    //std::vector<int> tileMapKeys_;
    int tileMap_{0};
    int tileMapDetails_{0};
};

#endif