#pragma once
#include "SpriteComponent.h"
class AnimationComponent :
    public SpriteComponent
{
public:
    AnimationComponent(class Actor* Owner, class Player* Player);
    void AddImage(int img);
    void Update() override;
    void Draw()override;

    void SetIdx(int mcuridx) { mCurIdx = mcuridx; }
    int GetIdx() { return mCurIdx; }
    void SetInterval(float interval) { mInterval = interval; }

    int idx;
private:
    std::vector<int>mImages;
    int mCurIdx;
    float mTimer;
    float mInterval;

};

