#pragma once
#include "main.h"
#include "input.h"
#include "Component.h"
#include "MoveComponent.h"

//Å´ó]åvÇ»Include
//#include "Actor.h"
//#include "Player.h"



class InputComponent :
    public MoveComponent

{
    public:
    InputComponent(class Actor* Owner);
    InputComponent(class Actor* Owner, class Player* Player);
    virtual ~InputComponent();
	void ProcessInput(void) override;



	private:
};
