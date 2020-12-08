#ifndef PLAYER_MANAGER_H_
#define PLAYER_MANAGER_H_
#include "../Engine/Camera.h"
#include "../UI/UIHeart.h"

class PlayerManager
{
public:
    PlayerManager(Camera* camera);
    ~PlayerManager();
    void Init(const int ID, const int HP, const int maxHP, const int range, const int specialCooldown, const int wallet);
    void Init();
    void SetID(const int ID);
    int GetID();
    void SetHPUI();
    UIHeart* GetHPUI();
    void SetMaxHP(const int maxHP);
    int GetMaxHP() const;
    void AddMaxHP(const int numToAdd);
    void SetHP(const int newHP);
    int GetHP() const;
    void AddHP(const int HP);
    void SubHP(const int HP);
    void SetHeal(const bool heal);
    bool GetHeal() const;
    void SetWallet(const int money);
    int GetWallet() const;
    void AddMoney(const int money);
    void SubMoney(const int money);
    void SetWalletText();
    int GetWalletText() const;
    void SetPerception(const int newPerception);
    int GetPerception() const;
    void SetSpecialCooldown(const int newCooldown);
    int GetSpecialCooldown() const;
    void SetKillCount(const int killCount);
    int GetKillCount() const;
    void AddKillToCount();
    void SubKillToCount();

    void Reset();

private:
    Camera* camera_{nullptr};

    //Player Parameters
    int wallet_{0};
    int walletText_{0};
    int perception_{0};
    UIHeart* uiHeart_{nullptr};
    int HP_{0};
    int maxHP_{0};
    bool heal_{true};
    int ID_{0};
    int specialCooldown_{0};
    int killCount_{0};
};

#endif