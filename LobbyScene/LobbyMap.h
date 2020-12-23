#ifndef Lobby_Map_H_
#define Lobby_Map_H_
#include "../Map/SingleRoomMap.h"

class LobbyMap : public SingleRoomMap
{
public:
    LobbyMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~LobbyMap() override;
    void Draw(const sf::RenderWindow& render_window) override;

private:
    std::vector<int> MenuText;
};

#endif