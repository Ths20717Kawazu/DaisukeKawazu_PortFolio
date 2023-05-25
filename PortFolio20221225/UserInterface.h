#pragma once
#include "Actor.h"

class UserInterface :
    public Actor
{
    public:
        UserInterface(class Game* game, enum Actor::Tag tag);
        ~UserInterface();
        void UpdateActor() override;
    private:
        D3DXVECTOR2 mPlayerPos;

};

