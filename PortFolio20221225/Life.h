#pragma once
#include "Actor.h"
class Life :
    public Actor
{
public:
    Life(class Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot, int num);
    ~Life();
    void UpdateActor() override;
private:
    D3DXVECTOR2 mPlayerPos;
    int mNum;
};

