#ifndef JUNK_YARD_MAP_H_
#define JUNK_YARD_MAP_H_
#include "../Map/SingleRoomMap.h"

class JunkYardMap : public SingleRoomMap
{
public:
    JunkYardMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    virtual void LoadObjectsFromCSC(const std::string& CSCFilePath) override;

private:
    int GenerateItem();
    int PrevScene();

private:
    std::vector<int> itemIDs_;
};

#endif