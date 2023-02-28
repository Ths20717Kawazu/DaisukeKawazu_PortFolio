#pragma once
#include "Actor.h"
#include "game.h"
#include "Player.h"

class Balloon :
    public Actor
{
public:
    Balloon(class Game* game, int tagID);
    ~Balloon();
    void UpdateActor() override;

    D3DXVECTOR2 GetPos() { return mPos; }
    void SetPos(D3DXVECTOR2 pos) { mPos = pos; }


    float GetLift() { return mLift; }
    void SetPlayerLift(float lift) { GetGame()->GetPlayer()->SetLift(lift); }

    void SetOwner(class Actor*);
    /* �����I��Balloon�̃X�e�[�^�X�ύX�̉\�����邱�Ƃ���C�L
    void SetLift(float lift) { mLift = lift; }*/
    void SetDamage(int damage) { mDamage = damage; }


private:
    int mDamage;
    D3DXVECTOR2 mPos;
    D3DXVECTOR2 Dir;
    float speed;
    float mLift;
    Actor* mOwner;
    
};

