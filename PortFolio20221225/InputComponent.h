#pragma once
#include "main.h"
#include "input.h"
#include "Component.h"
#include "MoveComponent.h"

//���]�v��Include
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
    int buffertime = 0;//��ʂ�؂�ւ����ۂɑO�̏�ʂł̑��삪���̏�ʂɔ��f����Ȃ��悤�o�b�t�@��ݒ肷��B
};
