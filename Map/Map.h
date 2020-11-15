#ifndef MAP_H_
#define MAP_H_
#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
    Map();
    virtual ~Map();
    virtual void CreateMap();
    virtual void PlaceObjects();
    //virtual void Update();
    virtual void Draw();
    virtual int GetLocation(float worldX, float worldY);
    virtual bool IsWall(float worldX, float worldY);
    virtual bool IsStair(sf::Vector2f worldCoordinate);

protected:
    const int CellSize = 32;
    int MapSize_ = 30;
    int mapWidth_ = 0;
    int mapHeight_ = 0;
    
    std::vector<std::vector<int> > map_;
    std::vector<std::vector<int> > objectMap_;
    std::vector<int> tileMapKeys_;
};

#endif