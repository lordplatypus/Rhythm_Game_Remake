#ifndef ENEMY_DATA_H_
#define ENEMY_DATA_H_

struct EnemyData
{
    EnemyData() = default;
    EnemyData(int ID, int hp, int maxhp, int atk, int range, bool heal);

    int ID_{0};
    int hp_{0};
    int maxhp_{0};
    int atk_{0};
    int range_{0};
    bool heal_{true};
};

#endif