#include "PlayerManager.h"

PlayerManager::PlayerManager()
{}

PlayerManager::~PlayerManager()
{}

void PlayerManager::Init(const int ID, const int HP, const int maxHP, const int range, const int specialCooldown, const int wallet)
{
    SetID(ID);
    SetHP(HP);
    SetMaxHP(maxHP);
    SetPerception(range);
    SetWallet(wallet);
    SetSpecialCooldown(specialCooldown);
}

void PlayerManager::Init()
{
    SetHP(3);
    SetMaxHP(3);
    SetPerception(64);
    SetWallet(1000);
    SetSpecialCooldown(5);
}

void PlayerManager::SetID(const int ID)
{
    ID_ = ID;
}

int PlayerManager::GetID()
{
    return ID_;
}

void PlayerManager::SetHP(const int newHP)
{
    HP_ = newHP;
}

void PlayerManager::SetMaxHP(const int maxHP)
{
    maxHP_ = maxHP;
}

int PlayerManager::GetMaxHP() const
{
    return maxHP_;
}

int PlayerManager::GetHP() const
{
    return HP_;
}

void PlayerManager::AddHP(const int HP)
{
    if (GetHP() < GetMaxHP())
    {
        if (HP + GetHP() > GetMaxHP()) 
        {
            SetHP(GetMaxHP());
        }
        else
        {
            SetHP(GetHP() + HP);
        }
    }
}

void PlayerManager::SubHP(const int HP)
{
    HP_ -= HP;
}

void PlayerManager::SetWallet(const int money)
{
    wallet_ = money;
}

int PlayerManager::GetWallet() const
{
    return wallet_;
}

void PlayerManager::AddMoney(const int money)
{
    wallet_ += money;
}

void PlayerManager::SubMoney(const int money)
{
    wallet_ -= money;
}

void PlayerManager::SetPerception(const int perception)
{
    perception_ = perception;
}

int PlayerManager::GetPerception() const
{
    return perception_;
}

void PlayerManager::SetSpecialCooldown(const int newCooldown)
{
    specialCooldown_ = newCooldown;
}

int PlayerManager::GetSpecialCooldown() const
{
    return specialCooldown_;
}

void PlayerManager::SetKillCount(const int killCount)
{
    killCount_ = killCount;
}

int PlayerManager::GetKillCount() const
{
    return killCount_;
}

void PlayerManager::AddKillToCount()
{
    killCount_++;
}

void PlayerManager::SubKillToCount()
{
    killCount_--;
}