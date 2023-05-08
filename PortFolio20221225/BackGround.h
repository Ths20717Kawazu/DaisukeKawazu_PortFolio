#pragma once
#include "Actor.h"
class BackGround :
    public Actor
{
public:
    BackGround(Game* game, enum Tag tag);
    ~BackGround();
    void UpdateActor() override;
private:
    D3DXVECTOR2 mPlayerPos;
};

