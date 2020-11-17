#ifndef UI_TEXT_H_
#define UI_TEXT_H_
#include <SFML/Graphics.hpp>
#include "UI.h"

class UIText : public UI
{
public:
    UIText(const int textKey, const int ID);
    ~UIText();
    virtual void Init();
    virtual void Update(float delta_time, float beat_time);
    virtual void Draw() const;

    void SetText(const std::string& text);
    void SetTextPosition(const sf::Vector2f position);
    void SetTextColor(const int red, const int green, const int blue, const int alpha);
    void SetTextSize(const int textSize);
    void SetTextScale(const float textScale);
    void SetTextVisiblity(const bool isVisible);

private:
    int textKey_{0};
    bool isVisible_{true};
};

#endif