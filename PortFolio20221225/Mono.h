#pragma once
#include "Actor.h"
class Mono :
    public Actor
{
public:
    Mono(class Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot);
    ~Mono();
    void UpdateActor() override;
    void SetDamage(int damage) { mDamage = damage; }
private:
    int mDamage;
    D3DXVECTOR2 Dir;
    float speed;
    Actor* mOwner;

};

