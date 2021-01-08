#include "Camera.h"

Camera::Camera(sf::RenderWindow* render_window) : window_{render_window} {}

Camera::~Camera() {}

const sf::View& Camera::GetCamera()
{
    return mainCamera;
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

sf::IntRect Camera::GetCameraRect() const
{
    sf::IntRect test(GetCameraLeftEdge(), GetCameraTopEdge(), GetCameraViewSize().x, GetCameraViewSize().y);
    return test;
}

const sf::Vector2f& Camera::GetCameraCenter() const
{
    return mainCamera.getCenter();
}

const sf::Vector2f& Camera::GetCameraViewSize() const
{
    return mainCamera.getSize();
}

float Camera::GetCameraRightEdge() const
{
    return GetCameraCenter().x + (GetCameraViewSize().x / 2);
}

float Camera::GetCameraLeftEdge() const
{
    return GetCameraCenter().x - (GetCameraViewSize().x / 2);
}

float Camera::GetCameraTopEdge() const
{
    return GetCameraCenter().y - (GetCameraViewSize().y / 2);
}

float Camera::GetCameraBottomEdge() const
{
    return GetCameraCenter().y + (GetCameraViewSize().y / 2);
}