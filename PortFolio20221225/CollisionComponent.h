#pragma once

#include "Component.h"
#include "Player.h"
#include "Block.h"
#include "main.h"

class CollisionComponent :
    public Component
{
public:
    CollisionComponent(class Actor* Owner);
    ~CollisionComponent();
    void Update()override;
    //CollisionComponent(class Actor* Owner, class Player* Player);
   /* void SetHalfW(float w) { mHalfW = w; }
    void SetHalfH(float h) { mHalfH = h; }
    float GetHalfW() const { return mHalfW; }
    float GetHalfH() const { return mHalfH; }*/
  
private:
    /*float mHalfW;
    float mHalfH;*/

};


//bool CheckBlocks();

bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB);
bool HitGroundCheck(class Actor* Block, class Player* Player);
bool HitCheckBLK2(class Actor* Block, class Player* Player);
bool HitCheckBB(D3DXVECTOR2 boxApos, float boxAwidth, float boxAheight,
    D3DXVECTOR2 boxBpos, float boxBwidth, float boxBheight);
bool HitCheckBLK(D3DXVECTOR2 tempPos, class Actor* , class Player*);
bool HitCheckBLK(D3DXVECTOR2 tempPos, class Actor* , class Enemy*);
//bool CheckObstacles(D3DXVECTOR2 posA);
