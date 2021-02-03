#include "GlobalEnemyManager.h"

GlobalEnemyManager::GlobalEnemyManager()
{
    SetAtkModifier(0);
    SetMaxHPModifier(0);
    SetRangeModifier(0);
    SetHealModifier(true);
    SetMoneyModifier(0);
}

GlobalEnemyManager::~GlobalEnemyManager()
{
    Clear();
}

void GlobalEnemyManager::SetAtkModifier(const int atkModifier)
{
    atkModifier_ = atkModifier;
}

int GlobalEnemyManager::GetAtkModifier() const
{
    return atkModifier_;
}

void GlobalEnemyManager::SetMaxHPModifier(const int maxHPModifier)
{
    maxHPModifier_ = maxHPModifier;
}

int GlobalEnemyManager::GetMaxHPModifier() const
{
    return maxHPModifier_;
}

void GlobalEnemyManager::SetRangeModifier(const int rangeModifier)
{
    rangeModifier_ = rangeModifier;
}

int GlobalEnemyManager::GetRangeModifier() const
{
    return rangeModifier_;
}

void GlobalEnemyManager::SetHealModifier(const bool healModifier)
{
    healModifier_ = healModifier;
}

bool GlobalEnemyManager::GetHealModifier() const
{
    return healModifier_;
}

void GlobalEnemyManager::SetMoneyModifier(const int moneyDropRate)
{
    moneyDropRate_ = moneyDropRate;
}

int GlobalEnemyManager::GetMoneyModifer() const
{
    return moneyDropRate_ + 2;
}

void GlobalEnemyManager::Clear()
{
    atkModifier_ = 0;
    maxHPModifier_ = 0;
    rangeModifier_ = 0;
    healModifier_ = true;
    moneyDropRate_ = 0;
}