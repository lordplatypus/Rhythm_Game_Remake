#ifndef UI_ARROW_H_
#define UI_ARROW_H_
#include <SFML/Graphics.hpp>
#include "../Particle/ParticleManager.h"

class UIArrow
{
public:
    UIArrow(ParticleManager* pm, sf::Vector2f position, int numOfArrows, int arrowPosition = 0);
    ~UIArrow();
    void Update(float delta_time, float beat_time);
    void Draw() const;

    int GetCurrentArrow() const;
    void UpdatePosition(const sf::Vector2f position);
    void UpdateVisiblity(const bool isVisible);
    void TakeDamage();
    void Heal();

    void AddArrow(int numOfArrowsToAdd);
    void RemoveArrow(int numOfArrowsToRemove);

private:
    void Init();
    void IndividualArrowVisibilty(const bool isVisible);
    void HPBarManager(bool currentHPBar, bool nextHPBar, bool hiddenHPBar);
    int ReportNextNonDamagedArrow(int arrowCount);

private:
    ParticleManager* pm_{nullptr};
    sf::Vector2f position_;
    UIArrow* nextArrow_{nullptr};
    int numOfArrows_{0};
    int arrowPosition_{0};
    bool isVisible_{false};
    //0 = left, 1 = right, 2 = up, 3 = down
    int arrowDirection_{-1};

    //images
    int arrow_;
    int greyArrow_;

    //Damage
    bool isDamaged_{false};
};

#endif