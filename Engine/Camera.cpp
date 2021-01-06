#include "Camera.h"

Camera::Camera(sf::RenderWindow* render_window) : window_{render_window}
{
    //mainCamera.reset(sf::FloatRect(0.f, 0.f, 1080.f, 720.f));
    //mainCamera.setSize();
}

Camera::~Camera() {}

sf::View* Camera::GetCamera()
{
    return &mainCamera;
}

void Camera::SetTarget(sf::Vector2f position)
{
    mainCamera.setCenter(position);
    window_->setView(mainCamera);
}

void Camera::SetCameraViewSize(float width, float height)
{
    mainCamera.setSize(width, height);
    window_->setView(mainCamera);
}

void Camera::SetCameraViewSize(sf::Vector2f size)
{
    mainCamera.setSize(size);
    window_->setView(mainCamera);
}

void Camera::SetCameraViewSize(const sf::FloatRect& area)
{
    //mainCamera.reset(area);
    mainCamera.setViewport(area);
    window_->setView(mainCamera);
}

sf::IntRect Camera::GetCameraRect()
{
    sf::IntRect test(GetCameraLeftEdge(), GetCameraTopEdge(), GetCameraViewSize().x, GetCameraViewSize().y);
    return test;
}

sf::Vector2f Camera::GetCameraCenter()
{
    return mainCamera.getCenter();
}

sf::Vector2f Camera::GetCameraViewSize()
{
    return mainCamera.getSize();
}

float Camera::GetCameraRightEdge()
{
    return GetCameraCenter().x + (GetCameraViewSize().x / 2);
}

float Camera::GetCameraLeftEdge()
{
    return GetCameraCenter().x - (GetCameraViewSize().x / 2);
}

float Camera::GetCameraTopEdge()
{
    return GetCameraCenter().y - (GetCameraViewSize().y / 2);
}

float Camera::GetCameraBottomEdge()
{
    return GetCameraCenter().y + (GetCameraViewSize().y / 2);
}