#include "PlayerManager.h"
#include "../Engine/LP.h"

PlayerManager::PlayerManager(Camera* camera) : camera_{camera}
{}

PlayerManager::~PlayerManager()
{}

void PlayerManager::Init(const int ID, const int HP, const int maxHP, const int atk, const int range, const int specialCooldown, const int wallet)
{
    SetID(ID);
    SetHP(HP);
    SetMaxHP(maxHP);
    SetAtk(atk);
    SetPerception(range);
    SetWallet(wallet);
    SetSpecialCooldown(specialCooldown);
}

void PlayerManager::Init()
{
    Reset();

    SetHeal(true);
    SetMaxHPChangeBool(true);
    SetWalletChangeBool(true);
    SetAtkChangeBool(true);
    SetPerceptionChangeBool(true);

    SetHP(3);
    SetMaxHP(3);
    SetHPUI();
    SetAtk(1);
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

void PlayerManager::SetHPUI()
{
    uiHeart_ = new UIHeart(camera_, GetHP());
}

UIHeart* PlayerManager::GetHPUI()
{
    return uiHeart_;
}

void PlayerManager::SetMaxHP(const int maxHP)
{
    maxHP_ = maxHP;
}

int PlayerManager::GetMaxHP() const
{
    return maxHP_;
}

void PlayerManager::AddMaxHP(const int numToAdd)
{
    if (!GetMaxHPChangeBool()) return;

    uiHeart_->AddHeart(numToAdd);
    uiHeart_->TakeDamage(numToAdd);
    maxHP_ += numToAdd;
}

void PlayerManager::SubMaxHP(const int numToSub)
{
    if (!GetMaxHPChangeBool()) return;

    uiHeart_->RemoveHeart(numToSub);
    maxHP_ -= numToSub;
    if (maxHP_ <= 0) maxHP_ = 1;
    if (HP_ > maxHP_) HP_ = maxHP_;
}

void PlayerManager::SetMaxHPChangeBool(const bool allow)
{
    allowMaxHPChange_ = allow;
}

bool PlayerManager::GetMaxHPChangeBool() const
{
    return allowMaxHPChange_;
}

void PlayerManager::SetHP(const int newHP)
{
    HP_ = newHP;
}

int PlayerManager::GetHP() const
{
    return HP_;
}

void PlayerManager::AddHP(const int HP)
{
    if (!GetHeal()) return;

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
    for (int i = 0; i < HP; i++) uiHeart_->Heal();
}

void PlayerManager::SubHP(const int HP)
{
    HP_ -= HP;
    uiHeart_->TakeDamage(HP);
}

void PlayerManager::SetHeal(const bool heal)
{
    heal_ = heal;
}

bool PlayerManager::GetHeal() const
{
    return heal_;
}

void PlayerManager::SetAtk(const int atk)
{
    if (!GetAtkChangeBool()) return;
    atk_ = atk;
}

int PlayerManager::GetAtk() const
{
    return atk_;
}

void PlayerManager::SetAtkChangeBool(const bool allow)
{
    allowAtkChange_ = allow;
}

bool PlayerManager::GetAtkChangeBool() const
{
    return allowAtkChange_;
}

void PlayerManager::SetWallet(const int money)
{
    if (!GetWalletChangeBool()) return;

    wallet_ = money;
    walletText_ = LP::SetText(std::to_string(wallet_), sf::Vector2f(0, 0), 64);
    LP::SetTextScale(walletText_, 0.1f, 0.1f);
    LP::SetTextOriginCenter(walletText_);
}

int PlayerManager::GetWallet() const
{
    return wallet_;
}

void PlayerManager::AddMoney(const int money)
{
    if (!GetWalletChangeBool()) return;
    wallet_ += money;
    SetWalletText();
}

void PlayerManager::SubMoney(const int money)
{
    wallet_ -= money;
    SetWalletText();
}

void PlayerManager::SetWalletChangeBool(const bool allow)
{
    allowWalletChange_ = allow;
}

bool PlayerManager::GetWalletChangeBool() const
{
    return allowWalletChange_;
}

void PlayerManager::SetWalletText()
{
    LP::SetTextString(walletText_, std::to_string(wallet_));
}

int PlayerManager::GetWalletText() const
{
    return walletText_;
}

void PlayerManager::SetPerception(const int perception)
{
    if (!GetPerceptionChangeBool()) return;
    perception_ = perception;
}

int PlayerManager::GetPerception() const
{
    return perception_;
}

void PlayerManager::SetPerceptionChangeBool(const bool allow)
{
    allowPerceptionChange_ = allow;
}

bool PlayerManager::GetPerceptionChangeBool() const
{
    return allowPerceptionChange_;
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

void PlayerManager::Reset()
{
    wallet_ = 0;
    LP::DeleteText(walletText_);
    perception_ = 0;
    delete uiHeart_;
    HP_ = 0;
    maxHP_ = 0;
    ID_ = 0;
    specialCooldown_ = 0;
    killCount_ = 0;
}