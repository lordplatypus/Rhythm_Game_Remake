#ifndef LOCAL_ENEMY_MANAGER_H_
#define LOCAL_ENEMY_MANAGER_H_
#include <list>
#include "EnemyData.h"
#include "GlobalEnemyManager.h"

class LocalEnemyManager
{
public:
    LocalEnemyManager(GlobalEnemyManager* gem);
    ~LocalEnemyManager();

    //Individual - affects only the individual
    EnemyData* Add(int hp, int maxhp, int damage, int range, bool heal, int moneyDropRate, bool visibility);
    EnemyData* GetData(const int ID);
    std::list<EnemyData*> GetEnemyData();
    void SetHP(const int ID, const int hp);
    int GetHP(const int ID);
    void SetMaxHP(const int ID, const int maxHP);
    int GetMaxHP(const int ID);
    void SetAtk(const int ID, const int atk);
    int GetAtk(const int ID);
    void SetRange(const int ID, const int range);
    int GetRange(const int ID);
    void SetHeal(const int ID, const bool heal);
    bool GetHeal(const int ID);
    void SetMoneyDropRate(const int ID, const int moneyDropRate);
    int GetMoneyDropRate(const int ID);
    void SetVisibility(const int ID, const bool visible);
    bool GetVisibility(const int ID);

    //local only for the current scene
    void SetTempAtkModifier(const int atkModifier);
    int GetTempAtkModifier() const;
    void SetTempHPModifier(const int hpModifier);
    int GetTempHPModifier() const;
    void SetTempMaxHPModifier(const int maxHPModifier);
    int GetTempMaxHPModifier() const;
    void SetTempRangeModifier(const int rangeModifier);
    int GetTempRangeModifier() const;
    void SetTempHealModifier(const bool healModifier);
    bool GetTempHealModifier() const;
    void SetTempMoneyModifier(const bool moneyDropRate);
    bool GetTempMoneyModifier() const;
    void SetTempVisibility(const bool visible);
    bool GetTempVisibility() const;

    void EnemiesTakeDamage(const int damage);

    //Get All modifiers
    int GetAtkModifier() const;
    int GetHPModifier() const;
    int GetMaxHPModifier() const;
    int GetRangeModifier() const;
    bool GetHealModifier() const;
    int GetMoneyModifier() const;
    bool GetVisibilityModifier() const;

    //Enemy Count
    int GetEnemyCount() const;
    void SetEnemyDeathCount(const int deathCount);
    int GetEnemyDeathCount() const;

    //
    void Remove(const int ID);
    void Clear();

private:
    GlobalEnemyManager* gem_{nullptr};
    std::list<EnemyData*> ed_;

    int ID_{-1};

    int tempAtkModifier_{0};
    int tempHPModifier_{0};
    int tempMaxHPModifier_{0};
    int tempRangeModifier_{0};
    bool tempHealModifier_{true};
    int tempMoneyDropRate_{0};
    bool tempVisibility_{true};

    int deathCount_{0};
};

#endif