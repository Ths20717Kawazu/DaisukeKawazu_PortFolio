#pragma once

#include "Component.h"
#include "Player.h"
#include "main.h"

class CollisionComponent :
    public Component
{
public:
    CollisionComponent(class Actor* Owner);
    CollisionComponent(class Actor* Owner, class Player* Player);
    void Update()override;
   /* void SetHalfW(float w) { mHalfW = w; }
    void SetHalfH(float h) { mHalfH = h; }
    float GetHalfW() const { return mHalfW; }
    float GetHalfH() const { return mHalfH; }*/
  
private:
    /*float mHalfW;
    float mHalfH;*/

};

bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB);
//bool CheckObstacles(D3DXVECTOR2 posA);
