#pragma once
#include "Actor.h"
#include "game.h"

class UserInterface :
    public Actor
{
    public:
        UserInterface(class Game* game, enum Actor::Tag tag);
        ~UserInterface();
        void UpdateActor() override;
    private:

};

