#ifndef CAMERA_H_
#define CAMERA_H_
#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    sf::View* GetCamera();
    void SetTarget(sf::Vector2f position);
    void SetCameraViewSize(float width, float height);
    void SetCameraViewSize(sf::Vector2f size);
    void SetCameraViewSize(sf::FloatRect area);
    sf::Vector2f GetCameraCenter();
    sf::Vector2f GetCameraViewSize();
    float GetCameraRightEdge();
    float GetCameraLeftEdge();
    float GetCameraTopEdge();
    float GetCameraBottomEdge();

private:
    sf::View mainCamera;
};

#endif