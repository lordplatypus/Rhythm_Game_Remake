#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_
#include "Scene.h"

//Null scene, used as a buffer when switching scenes
class SceneNull : public Scene
{
public:
    virtual void Init() override {}
    virtual void Update(float delta_time, float beat_time) override {}
    virtual void Draw(sf::RenderWindow& render_window) override {}
    virtual void AddGameObject(GameObject* gameObject) override {}
    virtual GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override {return nullptr;}
    virtual void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override {}
    virtual void ChangeScene(const std::string& sceneName) override {}
    virtual void End() override {}
};

#endif