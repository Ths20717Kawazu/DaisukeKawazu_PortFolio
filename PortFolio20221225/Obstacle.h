#pragma once
#include "Actor.h"
class Obstacle :
    public Actor
{
public:
    Obstacle(class Game* game, int tagID);
    ~Obstacle();
    void UpdateActor() override;
    void SetDamage(int damage) { mDamage = damage; }

private:
    int mDamage;
    D3DXVECTOR2 Dir;
    float speed;
    Actor* mOwner;

};

