#pragma once
#include "Actor.h"
#include "game.h"

class Player :
    public Actor
{
public: 
    int deltatime = 0;

    enum PlayerState
    {
        IDLE,
        WALK,
        RUN,
        JUMP,
        FALL,
        DAMAGE,
        FACE_RIGHT,
        FACE_LEFT,
        LAND,
        Statenums
  };
      Player(Game* game, enum Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot);
      ~Player();//基底クラスが削除された際に連動してデストラクタが発動する

      //void DrawPlayer(void);
      void UpdateActor() override;
      void Damage(int damage) override;


      //表示する画像及びその表示順序について入力
      void AddImage(int img, Player::PlayerState state);
      void AddAnimOrders(int order, Player::PlayerState state);

      void setState( enum Actor::STATE state) { mState = state; }
      enum Actor::STATE getState() { return mState;  }

      void setState(enum Player::PlayerState state) { mPState = state; }
      enum Player::PlayerState GetState() { return mPState; }

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
     /* D3DXVECTOR2 getPos() { return mPos; }
      void setPos(D3DXVECTOR2 pos) { mPos = pos; }*/

      bool GetHasballoon(){ return hasBalloon; }
      void SetHasballoon(bool hasballoon) { hasBalloon = hasballoon; }

      void SetLift(float lift) { P_mLift = lift; }
      float GetLift() { return P_mLift; }

      float GetJumpVel() { return mJumpVel; }
      void SetJumpVel(float jumpvel) { mJumpVel = jumpvel; }

      bool GetCloseToEnemy() { return mCloseToEnemy; }
      void SetClosetoEnemy(bool closetoenemy) { mCloseToEnemy = closetoenemy; }

      //ライフの残存数をプレイヤ側で管理    
      void SetLives(int lives) { mRemainLives = lives; }
      int GetLives() { return mRemainLives; }

    //派生クラスの画像配列を取得する。
    std::vector<int> GetAnimImages(Player::PlayerState state);
    std::vector<int> GetAnimOrders(Player::PlayerState state);

    int GetScore() { return mScore; }
    void SetScore(int score) { mScore = score; }

    float PlayerHeight = 300.0f;
    float PlayerWidth = 300.0f;
    int mcount = 0;

private:
    //画像配列
    std::vector<int>mIdleImages;
    std::vector<int>mWalkImages;

    //画像表示順序
    std::vector<int>animIdleOrders;

    enum Actor::STATE mState = Actor::EActive;
    enum Player::PlayerState mPState = Player::IDLE;
    SpriteComponent* mSprite;
    AnimationComponent* mAnimate;

    Game* mGame;
    //D3DXVECTOR2 playerPos;
    D3DXVECTOR2 mDir {0, 0};
    D3DXVECTOR2 mVel{ 0, 0 };
    D3DXVECTOR2 mLastpos{ 0, 0 };

    int mHP ;

    float mSpeed = 0;
    float mGravity= 0;
    float mJumpVel= 0;
    float P_mLift = 0;
    
    bool isInAir = false;
    bool hasBalloon = false;
    bool mCloseToEnemy = false;

    int mScore = 0 ;

    int mRemainLives = 0;

    int damageableTime = 0;//別で定める時間を超えるとダメージを受ける。
    bool damageable = false;
};