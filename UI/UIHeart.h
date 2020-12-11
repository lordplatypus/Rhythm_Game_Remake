#ifndef UI_HEART_H_
#define UI_HEART_H_
#include <SFML/Graphics.hpp>
#include "../Engine/Camera.h"

class UIHeart
{
public:
    UIHeart(Camera* camera, int numOfHearts, int heartPosition = 0);
    ~UIHeart();
    void Update(float delta_time, float beat_time);
    void Draw() const;

    bool IsDamaged();

    void TakeDamage(int amountOfDamage);
    void Heal();
    void Heal(int amountToHeal);
    void AddHeart(int numOfNewHearts);
    void RemoveHeart(int numOfHeartsToRemove);

    int GetNumOfHeart() const;
    void SetNumOfHeart(const int numOfHeart);
    int GetDamage(int count = 0) const;
    void SetDamage(const int damage);

    void SetBPM(float bpm);

private:
    Camera* camera_{nullptr};
    sf::Vector2f position_;
    UIHeart* nextHeart_{nullptr};
    int numOfHearts_{0};
    int heartPosition_{0};

    //images
    int heart_;
    int heartSmall_;
    int greyHeart_;
    int greyHeartSmall_;

    //Animation
    bool isSmall_{false};
    float bpm_{1};

    //Damage
    bool isDamaged_{false};
};

#endif