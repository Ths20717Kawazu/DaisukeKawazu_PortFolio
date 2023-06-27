#pragma once
#include "Enemy.h"

class Bat :
    public Enemy
{
public:
    Bat(Game* game, enum Actor::Tag tagID, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot);
    ~Bat();
    void UpdateActor()override;
private:
};

