#ifndef GLOBAL_ENEMY_MANAGER_H_
#define GLOBAL_ENEMY_MANAGER_H_

class GlobalEnemyManager
{
public:
    GlobalEnemyManager();
    ~GlobalEnemyManager();

    //Global - lasts between scenes
    void SetAtkModifier(const int atkModifier);
    int GetAtkModifier() const;
    void SetMaxHPModifier(const int maxHPModifier);
    int GetMaxHPModifier() const;
    void SetRangeModifier(const int rangeModifier);
    int GetRangeModifier() const;
    void SetHealModifier(const bool healModifier);
    bool GetHealModifier() const;

    //
    void Clear();

private:
    int atkModifier_{0};
    int maxHPModifier_{0};
    int rangeModifier_{0};
    bool healModifier_{true};
};

#endif