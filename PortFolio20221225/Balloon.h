#pragma once
#include "Actor.h"
#include "game.h"
#include "Player.h"

class Balloon :
    public Actor
{
public:
    Balloon(class Game* game, enum Actor::Tag tag);
    ~Balloon();
    void UpdateActor() override;

    D3DXVECTOR2 GetPos() { return mPos; }
    void SetPos(D3DXVECTOR2 pos) { mPos = pos; }

    float GetLift() { return mLift; }
    void SetOwner(class Actor*);
    void SetDamage(int damage) { mDamage = damage; }

    
    //void SetLift(float lift) { mLift = lift; }
    //void SetPlayerLift(float lift) { GetGame()->GetPlayer()->SetLift(lift); }


private:
    int mDamage;
    D3DXVECTOR2 mPos;
    D3DXVECTOR2 Dir;
    float speed;
    float mLift;
    Actor* mOwner;
    
};

