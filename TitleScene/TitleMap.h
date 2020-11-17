#ifndef TITLE_MAP_H_
#define TITLE_MAP_H_
#include "../Map/Map.h"
#include "../Scene/Scene.h"

class TitleMap : public Map
{
public:
    TitleMap(Scene *scene);
    ~TitleMap() override;
    void CreateMap() override;
    void DetailMap();
    void PlaceObjects() override;
    //void Update() override;
    void Draw() override;

private:
    Scene *scene_;
};

#endif