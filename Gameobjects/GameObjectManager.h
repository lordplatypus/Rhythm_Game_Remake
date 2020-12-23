#ifndef GAMEOBJECT_MANAGER_H_
#define GAMEOBJECT_MANAGER_H_
#include <list>
#include "GameObject.h"

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();
    //Add a gameobject to the list of gameobjects
    void Add(GameObject* gameObject);
    //Update all gameobjects in the list
    void Update(float delta_time, float beat_time);
    //Delayed Update
    void DelayedUpdate(float delta_time, float beat_time);
    //Draw all gameobjects in the list
    void Draw(sf::RenderWindow& render_window) const;
    //Delayed Draw
    void DelayedDraw(sf::RenderWindow& render_window) const;
    //Checks ONLY collision between gameobjects
    void Collision();
    //Checks collision between gameobjects but starts from the last created object
    void ReverseCollision();
    //More intensive but more accurate
    //Checks if "A" collides with "B" and if "B" collides with "A"
    void OneWayCollision();
    //Same as above but starts at last created object
    void OneWayReverseCollision();
    //Checks for collisions and non-collisions
    void Interaction();
    void ReverseInteraction();
    void OneWayInteraction();
    void OneWayReverseInteraction();
    void Perception();
    //Remove "dead" gameobjects
    void Remove();
    //Find a specific gameobject by tag
    GameObject* Find(const std::string& string, const bool byTag = true) const;
    //Find a specific gameobject by ID
    GameObject* Find(const int ID) const;
    //given the name of the object move it to a different spot within the gameobject list. for newPos use wither "begin" or "end"
    void ChangeListOrder(const std::string& name, const std::string& newPos);  
    //Delete all gameobjects, call when scene ends
    void Clear();

    GameObjectManager(const GameObjectManager& other) = delete;
    GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
    //called by the function with the same name, dosen't need to be called outside this class 
    void ChangeListOrder(std::list<GameObject*>::iterator posInList, std::list<GameObject*>::iterator newPosInList);

private:
    std::list<GameObject*> gameObjects_; //list of GameObjects
};

#endif