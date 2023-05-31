#pragma once
#include "Actor.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"


class GameStart :
    public Actor
{
public:
    GameStart(class Game* game, enum Actor::Tag tag);
    ~GameStart();
    void UpdateActor() override;
private:
    int timepassed;
};