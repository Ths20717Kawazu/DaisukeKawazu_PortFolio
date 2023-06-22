#pragma once
#include "Actor.h"
class Ending :
    public Actor
{
public:
    Ending(Game* game, enum Tag tag);
    ~Ending();
    void UpdateActor() override;
private:
};
