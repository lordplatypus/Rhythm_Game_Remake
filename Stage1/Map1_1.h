#ifndef MAP_1_1_H_
#define MAP_1_1_H_
#include "../Map/Map.h"
#include "../Scene/Scene.h"

class Map1_1 : public Map
{
public:
    Map1_1(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~Map1_1() override;
    void GenerateRandomRoomPlacement();
    void CreateMap() override;
    void CreateRoom(sf::Vector2i position, bool left, bool right, bool up, bool down);
    void CreateEmptyRoom(sf::Vector2i position);
    void CreateLeftHall(sf::Vector2i position);
    void CreateRightHall(sf::Vector2i position);
    void CreateUpHall(sf::Vector2i position);
    void CreateDownHall(sf::Vector2i position);
    void PlacePlayer(sf::Vector2i position);
    void PlaceEnemy(sf::Vector2i position);
    void PlaceStaircase(sf::Vector2i position);
    void PlaceJunkYard(sf::Vector2i position);
    //void PlaceObjects() override;
    void Draw() override;

private:
    std::vector<sf::Vector2f> roomCoordinates;
    int maxLeft = 0;
    int maxRight = 0;
    int maxUp = 0;
    int maxDown = 0;

    sf::Vector2f playerPosition;
};

#endif