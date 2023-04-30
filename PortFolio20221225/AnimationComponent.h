#pragma once
#include "SpriteComponent.h"
class AnimationComponent :
    public SpriteComponent
{
public:
    //AnimationComponent(class Actor* Owner, class Player* Player);
    AnimationComponent(class Actor* Owner);
    ~AnimationComponent();

    //void AddImage(int img, Player::PlayerState state);
    //void AddImage(int img, Enemy::EnemyState staet);
    //void Update() override;
    
    void UpdateDraw() override;
    //void DrawEnemy() override;

    void SetIdx(int mcuridx) { mCurIdx = mcuridx; }
    int GetIdx() { return mCurIdx; }
    void SetInterval(float interval) { mInterval = interval; }
 
private:
    int mCurIdx = 0;
    int mIndex = 0;
    float mTimer;
    float mInterval;
};

