#ifndef CAMERA_H_
#define CAMERA_H_
#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(sf::RenderWindow* render_window);
    ~Camera();
    const sf::View& GetCamera();
    void SetTarget(sf::Vector2f position);
    void SetCameraViewSize(float width, float height);
    void SetCameraViewSize(sf::Vector2f size);
    void SetCameraViewSize(const sf::FloatRect& area);
    sf::IntRect GetCameraRect() const;
    const sf::Vector2f& GetCameraCenter() const;
    const sf::Vector2f& GetCameraViewSize() const;
    float GetCameraRightEdge() const;
    float GetCameraLeftEdge() const;
    float GetCameraTopEdge() const;
    float GetCameraBottomEdge() const;

private:
    sf::View mainCamera;
    sf::RenderWindow* window_{nullptr};
};

#endif