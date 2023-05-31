#pragma once
#include "Actor.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"


class GameOver :
    public Actor
{
public:
    GameOver(class Game* game, enum Actor::Tag tag);
    ~GameOver();
    void UpdateActor() override;
private:
};

