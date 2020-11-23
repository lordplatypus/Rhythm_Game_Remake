#ifndef ITEM_H_
#define ITEM_H_
#include "../Gameobjects/GameObject.h"
#include "../UI/UIArrow.h"
#include "../Player/PlayerManager.h"
#include "../Particle/ParticleManager.h"

class Item : public GameObject
{
public:
    Item();
    ~Item();
    virtual void Effect() = 0;
    int GetPriceTag() const;
    void SparkleRandom(float delta_time);
    void Kill() override;
    
private:
    void TakeDamage(const int damage) override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;
    void Sparkle();

private:
    float sparkleTime{0.0f};

protected:
    UIArrow* arrow_{nullptr};
    PlayerManager* playerManager_{nullptr};
    ParticleManager* pm_{nullptr};

    int sprite_{0};
    int priceTag_{0};
    bool ifSeesPlayer_{false};
    int HP_{0};

    int text_{0};
};

#endif