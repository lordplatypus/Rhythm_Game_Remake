#include "EnemyData.h"

EnemyData::EnemyData(int ID, int hp, int maxhp, int atk, int range, bool heal, int moneyDropRate) : 
    ID_{ID}, hp_{hp}, maxhp_{maxhp}, atk_{atk}, range_{range}, heal_{heal}, moneyDropRate_{moneyDropRate}
{}