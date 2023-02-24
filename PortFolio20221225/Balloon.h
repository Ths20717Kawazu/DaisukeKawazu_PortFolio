#pragma once
#include "Actor.h"
class Balloon :
    public Actor
{
public:
    Balloon(class Game* game);
    void UpdateActor() override;

    D3DXVECTOR2 GetPos() { return mPos; }
    void SetPos(D3DXVECTOR2 pos) { mPos = pos; }

private:
    D3DXVECTOR2 mPos;
    D3DXVECTOR2 Dir;
    float speed;

};

