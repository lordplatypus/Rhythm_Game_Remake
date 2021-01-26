#ifndef SINGLE_ROOM_MAP_H_
#define SINGLE_ROOM_MAP_H_
#include "Map.h"
#include "TileMap.h"

class SingleRoomMap : public Map
{
public:
    SingleRoomMap();
    ~SingleRoomMap();
    virtual void Draw(sf::RenderWindow& render_window) override;
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
    TileMap tileMap_;
    TileMap tileMapDetails_;
};

#endif