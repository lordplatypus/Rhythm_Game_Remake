#ifndef JUNK_YARD_MAP_H_
#define JUNK_YARD_MAP_H_
#include "../Map/Map.h"

class JunkYardMap : public Map
{
public:
    JunkYardMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~JunkYardMap() override;
    void CreateMap() override;
    void PlaceObjects() override;
    void Draw() override;

private:
    int GenerateItem();
    int PrevScene();

private:
    std::vector<int> itemIDs_;
};

#endif