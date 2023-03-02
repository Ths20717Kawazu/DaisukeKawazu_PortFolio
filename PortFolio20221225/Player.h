#pragma once
#include "Actor.h"
#include "game.h"

class Player :
    public Actor
{
public: 

    enum PlayerState
    {
        EIDLE,
        EWALK,
        ERUN,
        EJUMP,
        EFALL,
        EDAMAGE,
        EFACE_RIGHT,
        EFACE_LEFT,
        ELAND,
        EStatenums
  };
      Player(Game* game, enum Tag tag);
      ~Player();
      void DrawPlayer(void);
      void UpdateActor() override;

      void Damage(int damage) override;
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

      void SetLift(float lift) { P_mLift = lift; }
      float GetLift() { return P_mLift; }

      float GetJumpVel() { return mJumpVel; }
      void SetJumpVel(float jumpvel) { mJumpVel = jumpvel; }

      bool GetCloseToEnemy() { return mCloseToEnemy; }
      void SetClosetoEnemy(bool closetoenemy) { mCloseToEnemy = closetoenemy; }

    float PlayerHeight = 300.0f;
    float PlayerWidth = 300.0f;

    //void AddTagIDs(class Enemy*);
    //void RemoveTagIDs(class Enemy*);
    //std::vector<class Enemy*>& GetTagIDs() { return mTagIDs; }

private:
    //enum Player::PlayerState mState {ESTAND};
    //std::vector<class Enemy*>mTagIDs;
    
    enum Actor::STATE mState = Actor::EActive;
    Game* mGame;
    //D3DXVECTOR2 playerPos;
    D3DXVECTOR2 mDir;
    D3DXVECTOR2 mVel;
    D3DXVECTOR2 mLastpos;

    int mHP ;

    float mSpeed;
    float mGravity;
    float mJumpVel;
    float P_mLift;
    
    bool isInAir = false;
    bool hasBalloon = false;
    bool mCloseToEnemy = false;
};