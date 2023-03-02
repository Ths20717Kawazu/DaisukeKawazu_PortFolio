#pragma once
#include "SpriteComponent.h"
class AnimationComponent :
    public SpriteComponent
{
public:
    AnimationComponent(class Actor* Owner, class Player* Player);
    AnimationComponent(class Actor* Owner);
    void AddImage(int img, Player::PlayerState state);
    void AddImage(int img, Enemy::EnemyState staet);
    void Update() override;
    
    void Draw2() override;
    void DrawEnemy() override;
    void SetIdx(int mcuridx) { mCurIdx = mcuridx; }
    int GetIdx() { return mCurIdx; }
    void SetInterval(float interval) { mInterval = interval; }

    

    int idx;
 
private:
    std::vector<int>animIDs;
    std::vector<int>mIdleImages;
    std::vector<int>mWalkImages;
    std::vector<int>mRunImages;
    std::vector<int>mJumpImages;
    std::vector<int>mFallImages;

    std::vector<int>mEIdleImages;

    int mCurIdx;
    float mTimer;
    float mInterval;

};

