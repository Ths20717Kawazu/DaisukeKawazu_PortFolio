#pragma once
#include "main.h"
#include "input.h"
#include "Component.h"
#include "MoveComponent.h"

//↓余計なInclude
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
    int buffertime = 0;//場面を切り替えた際に前の場面での操作が次の場面に反映されないようバッファを設定する。
};
