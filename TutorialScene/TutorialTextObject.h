#ifndef TUTORIAL_TEXT_OBJECT_H_
#define TUTORIAL_TEXT_OBJECT_H_
#include "../Gameobjects/GameObject.h"

class TutorialTextObject : public GameObject
{
public:
    TutorialTextObject(sf::Vector2f position, const std::string& text, Scene *scene);
    ~TutorialTextObject() override;
    void Update(float delta_time, float beat_time) override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;

private:
    sf::Text text_;
    bool displayText_{false};
};

#endif