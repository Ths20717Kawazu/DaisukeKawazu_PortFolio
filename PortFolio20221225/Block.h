#pragma once
#include "Actor.h"

class Block :
    public Actor
{

public:

    enum BlockState {

        STABLE,
        NUMS

    };
    Block(class Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot);
    ~Block();
    void UpdateActor() override;
private:
   
};

