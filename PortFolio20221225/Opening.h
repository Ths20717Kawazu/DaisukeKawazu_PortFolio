#pragma once
#include "Actor.h"
class Opening :
    public Actor
{
 public:
    Opening(Game* game, enum Tag tag);
    ~Opening();
    void UpdateActor() override;
 private:
};
