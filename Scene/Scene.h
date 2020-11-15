#ifndef SCENE_H_
#define SCENE_H_
#include <string>
#include "../Gameobjects/GameObject.h"

class GameObject;

class Scene
{
public:
    virtual ~Scene() = default;
    //This is called everytime this scene is loaded
    virtual void Init() = 0;
    //Scene Update
    virtual void Update(float delta_time, float beat_time) = 0;
    //Scene Draw
    virtual void Draw() = 0;
    //Add gameobject to the list of gameobjects
    virtual void AddGameObject(GameObject* gameObject) = 0;
    //Find an object by either ID, Tag, or Name
    virtual GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) = 0;
    //Move a gameobject to a new position within the list of GameObjects
    virtual void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) = 0;
    //Change to a different scene
    virtual void ChangeScene(const std::string& sceneName) = 0;
    //This is called when switching to a different scene, delete unneeded pointers and sprites here
    virtual void End() = 0;
};

#endif