#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{

public:
    enum EnemyState {
        IDLE,
        WALK,
        RUN

    };
    Enemy(class Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot);
    ~Enemy();//継承先のデストラクタを機能させるためにVirtualは忘れないこと
    void UpdateActor() override;
    void Damage(int damage) override;
    void AddImage(int img, Enemy::EnemyState state);
    void AddAnimOrders(int order, Enemy::EnemyState state);
    //派生クラスの画像配列を取得する。
    std::vector<int> GetAnimImages(Enemy::EnemyState state);
    std::vector<int> GetAnimOrders(Enemy::EnemyState state);


    enum EnemyState SetState(enum EnemyState state) { mState = state; }
    enum EnemyState GetState() { return mState; }

    float getGravity() { return Actor::mGravity; };
    void setGravity(float gravity) { Actor::mGravity = gravity; }


    int getWidth() { return EnemyWidth;}
    int getHeight() { return EnemyHeight; }

    void SetVel(float x, float y) { mVel.x = x, mVel.y = y;  }

    int GetEScore() { return mEscore; }
protected:
    D3DXVECTOR2 mDir{ 1.0f, 0 };
    bool isInAir = false;
    int EnemyWidth = 100;
    int EnemyHeight = 100;
    D3DXVECTOR2 mVel{0.0f, 0.0f};
    enum EnemyState mState;
    //画像配列
    std::vector<int>mIdleImages;
    std::vector<int>mWalkImages; 
    //画像表示順序
    std::vector<int>animIdleOrders;
    int mEscore;
    float mSpeed = 2.0f;
};

