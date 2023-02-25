#pragma once
#include "Actor.h"

class Block :
    public Actor
{

public:
    Block(class Game* game);

    float BlockWidth = 100.0f;
    float BlockHeight = 100.0f;

private:

};

