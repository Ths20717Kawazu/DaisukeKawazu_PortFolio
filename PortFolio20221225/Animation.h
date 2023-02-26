#pragma once
#include "SpriteComponent.h"
class Animation :
    public SpriteComponent
{
public:
    Animation(class Actor* owner, 0);
    void AddImage(int img);
    void Update() override;
    void draw()override;
    void SetInterval(float interval) { mInterval = interval; }
private:
    std::vector<int>mImages;
    int mCurIdx;
    float mTimer;
    float mInterval;

};

