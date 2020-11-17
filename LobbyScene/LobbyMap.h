#ifndef Lobby_Map_H_
#define Lobby_Map_H_
#include "../Map/Map.h"

class LobbyMap : public Map
{
public:
    LobbyMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~LobbyMap() override;
    void CreateMap() override;
    void DetailMap();
    void PlaceObjects() override;
    void Draw() override;

private:
    std::vector<int> MenuText;
};

#endif