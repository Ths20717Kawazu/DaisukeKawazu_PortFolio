#pragma once
#include "game.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include <stdlib.h>
#include <iostream>


InputComponent::InputComponent(Actor* Owner):MoveComponent(Owner)
{

}

InputComponent::InputComponent(Actor* Owner, class Player* Player):MoveComponent(Owner, Player)
{

}


InputComponent::~InputComponent() {};



void InputComponent::ProcessInput(void)
{
	D3DXVECTOR2 dir = mPlayer->getDir();

	if (mPlayer->getState() != Actor::EDead)
	{

		if (GetKeyboardPress(DIK_LEFT))
		{
			dir.x = -1.0f;
			mPlayer->setDir(dir);
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
				dir.x = 1.0;
				mPlayer->setDir(dir);
		}
		if (GetKeyboardPress(DIK_UP))
		{
				dir.y = -1.0;
				mPlayer->setDir(dir);	
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			    dir.y = 1.0;
				mPlayer->setDir(dir);
			//�n�ʂɐڂ��Ă��鎞

			//�󒆂ɂ���Ƃ�

		}
		mPlayer->setDir(dir);


		//�V�KY�̒l����r�Ώۂł���ABlock�̏�ӂ�Y���W���傫����΁A�v���C�����W�͓��͑O�̒l�ɖ߂�
		//if (pos.y > 800) //������if����CollisionComponent�œ����蔻��̖߂�l�������Ƃ��Ă����B
		////if (checkBlock == false)
		//{
		//	pos = lastpos;
		//	//pos
		//}


	}
}

	
	/*if (HitCheckBC)
	{

	}
	else 
	{
	
	}*/
	//�����A���͂��ꂽ�l�𑫂����ꍇ�ڐG���邩���Ȃ�������
	//�ڐG����ꍇ�́A���͑O�̈ʒu�ɖ߂�
	/*if (CheckObstacles(mOwner->GetACTOR().pos)) 
	{

	}
	else 
	{
		mOwner->SetPos(posx, posy);
	}*/






