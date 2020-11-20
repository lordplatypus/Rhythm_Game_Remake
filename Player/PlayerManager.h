#ifndef PLAYER_MANAGER_H_
#define PLAYER_MANAGER_H_

class PlayerManager
{
public:
    PlayerManager();
    ~PlayerManager();
    void Init(const int ID, const int HP, const int maxHP, const int range, const int specialCooldown, const int wallet);
    void Init();
    void SetID(const int ID);
    int GetID();
    void SetHP(const int newHP);
    int GetHP() const;
    void SetMaxHP(const int maxHP);
    int GetMaxHP() const;
    void AddHP(const int HP);
    void SubHP(const int HP);
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
    //Player Parameters
    int wallet_{0};
    int walletText_{0};
    int perception_{0};
    int HP_{0};
    int maxHP_{0};
    int ID_{0};
    int specialCooldown_{0};
    int killCount_{0};
};

#endif