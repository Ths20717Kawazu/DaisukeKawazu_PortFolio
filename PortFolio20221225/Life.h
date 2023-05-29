#pragma once
#include "Actor.h"
class Life :
    public Actor
{
public:
    Life(class Game* game, enum Actor::Tag tag);
    ~Life();
    void UpdateActor() override;
private:
    D3DXVECTOR2 mPlayerPos;
};

