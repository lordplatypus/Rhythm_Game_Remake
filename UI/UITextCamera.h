#ifndef UI_TEXT_CAMERA_H_
#define UI_TEXT_CAMERA_H_
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Camera.h"

class UITextCamera : public UI
{
public:
    UITextCamera(const int textKey, const std::string& name, sf::Vector2f position, Camera* camera);
    ~UITextCamera();
    virtual void Init();
    virtual void Update(float delta_time, float beat_time);
    virtual void Draw() const;

    void SetText(const std::string& text);
    void SetTextPosition(const sf::Vector2f position);
    void SetTextColor(const int red, const int green, const int blue, const int alpha);
    void SetTextSize(const int textSize);
    void SetTextScale(const float textScale);
    void SetTextVisiblity(const bool isVisible);
    void SetTextOrigin(const sf::Vector2f origin);
    void SetTextOriginCenter();

private:
    int textKey_{0};
    bool isVisible_{true};
    Camera* camera_{nullptr};
    sf::Vector2f position_{0.0f, 0.0f};
};

#endif