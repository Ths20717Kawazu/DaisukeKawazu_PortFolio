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
    Block(class Game* game, enum Actor::Tag tag);

    float BlockWidth = 100.0f;
    float BlockHeight = 100.0f;

private:
   
};

