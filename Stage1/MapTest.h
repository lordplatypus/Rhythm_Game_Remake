#ifndef MAP_Test_H_
#define MAP_Test_H_
#include "../Map/Map.h"
#include "../Scene/Scene.h"
#include "../Map/Room.h"
#include <list>

class MapTest : public Map
{
public:
    MapTest(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~MapTest() override;
    void CreateMap() override;

    // void PlacePlayer(sf::Vector2i position);
    // void PlaceEnemy(sf::Vector2i position);
    // void PlaceStaircase(sf::Vector2i position);
    // void PlaceJunkYard(sf::Vector2i position);
    void Draw() override;
    bool IsWall(sf::Vector2f worldCoordinate) override;

private:
    void RandomRoom(sf::Vector2i position);

private:
    std::vector<Room*> rooms_;

    //

};

#endif