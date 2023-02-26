#pragma once
#include "Actor.h"
class Enemy :
    public Actor
{

public:
    Enemy(class Game* game, int tagID);
    ~Enemy();
    void UpdateActor() override;
    bool hit = false;

    int count = 0;

private:
        

};

