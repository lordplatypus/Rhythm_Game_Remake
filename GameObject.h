#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Scene;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    //Update
    virtual void Update(float delta_time);
    //Draw
    virtual void Draw();

    //This is called when colliding with another gameobject, write reaction logic here
    virtual void ReactOnCollision(GameObject& other);
    //Marks the gameobject as "dead" so that it can be removed
    virtual void Kill();

    //Hitbox
    //Left edge of the hitbox
    int GetLeft() const;
    void SetLeft(const int left);
    //Right edge of the hitbox
    int GetRight() const;
    void SetRight(const int right);
    //Top edge of the hitbox
    int GetTop() const;
    void SetTop(const int top);
    //Bottom edge of the hitbox
    int GetBottom() const;
    void SetBottom(const int bottom);
    //Return a vector of points that make up the hitbox
    const std::vector<sf::Vector2f> GetHitBox();

    //Collision
    //Check if collision happened between this gameobject and "other"
    bool IsCollision(GameObject& other);
    //If collision occured, call "ReactOnCollision" for this gameobject and "other"
    void OnCollision(GameObject& other);

    //Data
    //Store position
    void StorePosition();
    //Returns current position
    sf::Vector2f GetPosition() const;
    //Returns stored position
    sf::Vector2f GetPrevPosition() const;
    //Returns "living" state
    bool IsDead() const;
    //Return tag
    const std::string& GetTag() const;
    //Return name
    const std::string& GetName() const;
    //return ID
    int GetID() const;

    GameObject(const GameObject& other) = delete;
    GameObject& operator = (const GameObject& other) = delete;

private:
    int left_{0}; //Left edge of the hitbox
    int right_{0}; //Right edge of the hitbox
    int top_{0}; //Top edge of the hitbox
    int bottom_{0}; //Bottom edge of the hitbox
    sf::Vector2f prevPosition_{0.0f, 0.0f}; //store prev position

protected:
    Scene* scene_{nullptr}; //Gives access to the scene, Set this up in the gameobjects constructor
    sf::Vector2f position_{0.0f, 0.0f}; //gameobjects position
    sf::Vector2f velocity_{0.0f, 0.0f}; //gameobjects velocity
    bool isDead_{false}; //"Death" flag
    int sprite_{0}; //Used to store sprite ID - Used for drawing/editing sprite
    int imageWidth_{0}; //sprite width - Set up in the constructor
    int imageHeight_{0}; //sprite height - Set up in the constructor
    std::string tag_{""}; //gameobject tag - Set up in the constructor
    std::string name_{""}; //gameobject name - Set up in the constructor
    int ID_{0}; //gameobject ID - Set up in the constructor
};

#endif