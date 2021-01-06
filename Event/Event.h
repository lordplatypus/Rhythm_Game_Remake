#ifndef EVENT_H_
#define EVENT_H_
#include "../Gameobjects/GameObject.h"
#include "../Engine/Camera.h"
#include "../Transition/TransitionManager.h"

class Event : public GameObject
{
public:
    Event();
    ~Event() override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;

    void Lock();
    void Unlock();

    void SetInstructionText(const std::string& text);
    void SetInstructionTextString(const std::string& text);
    void DisplayInstructionsText(float delta_time);

    void End();

private:
    void Setup();
    void Type();
    void Fadeout();
    void Display();

public:
    virtual void EventTrigger();

private:
    enum State{Setup_, Type_, Fadeout_, Display_};
    State state_{Setup_};
    float timer_{0.0f};
    int count_{0};
    float alpha_{255};
    std::string string_{""};
    std::string displayString_{""};

protected:
    std::string target_{""};
    sf::Text instructionText_;

    Camera* camera_{nullptr};
    TransitionManager* transitionManager_{nullptr};
};

#endif