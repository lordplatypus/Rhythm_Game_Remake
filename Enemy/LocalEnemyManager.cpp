#include "LocalEnemyManager.h"

LocalEnemyManager::LocalEnemyManager(GlobalEnemyManager* gem) : gem_{gem}
{}

LocalEnemyManager::~LocalEnemyManager()
{
    Clear();
}

EnemyData* LocalEnemyManager::Add(int hp, int maxhp, int damage, int range, bool heal, int moneyDropRate)
{
    ID_++;
    EnemyData* temp = new EnemyData(ID_, hp, maxhp, damage, range, heal, moneyDropRate);
    ed_.push_back(temp);
    return temp;
}

EnemyData* LocalEnemyManager::GetData(const int ID)
{
    for (auto i : ed_)
    {
        if (i->ID_ == ID) return i;
    }
    return nullptr;
}

std::list<EnemyData*> LocalEnemyManager::GetEnemyData()
{
    return ed_;
}

void LocalEnemyManager::SetHP(const int ID, const int hp)
{
    GetData(ID)->hp_ = hp;
}

int LocalEnemyManager::GetHP(const int ID)
{
    return GetData(ID)->hp_;
}

void LocalEnemyManager::SetMaxHP(const int ID, const int maxHP)
{
    GetData(ID)->maxhp_ = maxHP;
}

int LocalEnemyManager::GetMaxHP(const int ID)
{
    return GetData(ID)->maxhp_;
}

void LocalEnemyManager::SetAtk(const int ID, const int atk)
{
    GetData(ID)->atk_ = atk;
}

int LocalEnemyManager::GetAtk(const int ID)
{
    return GetData(ID)->atk_;
}

void LocalEnemyManager::SetRange(const int ID, const int range)
{
    GetData(ID)->range_ = range;
}

int LocalEnemyManager::GetRange(const int ID)
{
    return GetData(ID)->range_;
}

void LocalEnemyManager::SetHeal(const int ID, const bool heal)
{
    GetData(ID)->heal_ = heal;
}

bool LocalEnemyManager::GetHeal(const int ID)
{
    return GetData(ID)->heal_;
}

void LocalEnemyManager::SetMoneyDropRate(const int ID, const int moneyDropRate)
{
    GetData(ID)->moneyDropRate_ = moneyDropRate;
}

int LocalEnemyManager::GetMoneyDropRate(const int ID)
{
    return GetData(ID)->moneyDropRate_;
}


//Local - applied only to existing enemies

void LocalEnemyManager::SetTempAtkModifier(const int atkModifier)
{
    tempAtkModifier_ = atkModifier;
}

int LocalEnemyManager::GetTempAtkModifier() const
{
    return tempAtkModifier_;
}

void LocalEnemyManager::SetTempHPModifier(const int hpModifier)
{
    tempHPModifier_ = hpModifier;
}

int LocalEnemyManager::GetTempHPModifier() const
{
    return tempHPModifier_;
}

void LocalEnemyManager::SetTempMaxHPModifier(const int maxHPModifier)
{
    tempMaxHPModifier_ = maxHPModifier;
}

int LocalEnemyManager::GetTempMaxHPModifier() const
{
    return tempMaxHPModifier_;
}

void LocalEnemyManager::SetTempRangeModifier(const int rangeModifier)
{
    tempRangeModifier_ = rangeModifier;
}
int LocalEnemyManager::GetTempRangeModifier() const
{
    return tempRangeModifier_;
}

void LocalEnemyManager::SetTempHealModifier(const bool healModifier)
{
    tempHealModifier_ = healModifier;
}

bool LocalEnemyManager::GetTempHealModifier() const
{
    return tempHealModifier_;
}

void LocalEnemyManager::SetTempMoneyModifier(const bool moneyDropRate)
{
    tempMoneyDropRate_ = moneyDropRate;
}

bool LocalEnemyManager::GetTempMoneyModifier() const
{
    return tempMoneyDropRate_;
}

void LocalEnemyManager::EnemiesTakeDamage(const int damage)
{
}


//Global + Local Modifiers

int LocalEnemyManager::GetAtkModifier() const
{
    return GetTempAtkModifier() + gem_->GetAtkModifier();
}

int LocalEnemyManager::GetHPModifier() const
{
    return GetTempHPModifier();
}

int LocalEnemyManager::GetMaxHPModifier() const
{
    return GetTempMaxHPModifier() + gem_->GetMaxHPModifier();
}

int LocalEnemyManager::GetRangeModifier() const
{
    return GetTempRangeModifier() + gem_->GetRangeModifier();
}

bool LocalEnemyManager::GetHealModifier() const
{
    if (!gem_->GetHealModifier()) return false;
    if (!GetTempHealModifier()) return false;
    return true;
}

int LocalEnemyManager::GetMoneyModifier() const
{
    return GetTempMoneyModifier() + gem_->GetMoneyModifer();
}


//Enemy Count

int LocalEnemyManager::GetEnemyCount() const
{
    return ed_.size();
}

void LocalEnemyManager::SetEnemyDeathCount(const int deathCount)
{
    deathCount_ = deathCount;
}

int LocalEnemyManager::GetEnemyDeathCount() const
{
    return deathCount_;
}


void LocalEnemyManager::Clear()
{
    for (auto i : ed_) delete i;
    ed_.clear();
}