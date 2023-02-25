#pragma once
#include "Actor.h"
#include "game.h"

//#include "InputComponent.h" ���]�v��Include

class Player :
    public Actor
{
public: 

    enum PlayerState
    {
        EIDLE,
        EFACE_RIGHT,
        EFACE_LEFT,
        ERUN_RIGHT,
        ERUN_LEFT,
        EJUMP,
        EFALL,
        ELAND,
        EDAMAGE,
  };
      Player(Game* game);
      ~Player();
      void DrawPlayer(void);
      void UpdateActor() override;

      void Damage();
      void setState( enum Actor::STATE state) { mState = state; }
      enum Actor::STATE getState() { return mState;  }

      void setHP(int inputNum) { mHP = inputNum; }
      int getHP() { return mHP; }
      
      float getSpeed() { return mSpeed; }
      void setSpeed(float speed) { mSpeed = speed; }
      Player* addPlayer() {};

      bool getIsInAir() { return isInAir; }
      void setIsInAir(bool isinair) { isInAir = isinair; }

      float  getPlayerHeight() { return PlayerHeight; }
      float  getPlayerWidth() { return PlayerWidth; }

      float getGravity() { return mGravity; };

      D3DXVECTOR2 getDir() { return mDir; }
      void setDir(D3DXVECTOR2 dir) { mDir = dir; }
      D3DXVECTOR2 getVel() { return mVel; }
      void setVel(D3DXVECTOR2 vel) { mVel = vel; }
      D3DXVECTOR2 getPos() { return mPos; }
      void setPos(D3DXVECTOR2 pos) { mPos = pos; }

      bool GetHasballoon(){ return hasBalloon; }
      void SetHasballoon(bool hasballoon) { hasBalloon = hasballoon; }

      void SetLift(float lift) { mLift = lift; }

      float GetJumpVel() { return mJumpVel; }
      void SetJumpVel(float jumpvel) { mJumpVel = jumpvel; }

    float PlayerHeight = 300.0f;
    float PlayerWidth = 300.0f;
private:
    //enum Player::PlayerState mState {ESTAND};
    
    enum Actor::STATE mState = Actor::EActive;
    int mHP ;
    float mSpeed;
    Game* mGame;
    //D3DXVECTOR2 playerPos;
    bool isInAir = false;
    D3DXVECTOR2 mDir;
    D3DXVECTOR2 mVel;
    D3DXVECTOR2 mPos;
    D3DXVECTOR2 mLastpos;

    float mGravity;
    float mJumpVel;
    float mLift;
    bool hasBalloon = false;
   

};