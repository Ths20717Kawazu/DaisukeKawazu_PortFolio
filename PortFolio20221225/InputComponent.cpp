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
	D3DXVECTOR2 dir(0, 0);
	D3DXVECTOR2 vel;
	D3DXVECTOR2 pos;
	float posx;
	float posy;
	//float speed = mPlayer->getSpeed();
	pos.x = mOwner->GetACTOR().pos.x;
	pos.y = mOwner->GetACTOR().pos.y;


	D3DXVECTOR2 lastpos;
	lastpos = mOwner->GetPos();
	//bool hit = false;


	if (mPlayer->getState() != Actor::EDead)
	{

		if (GetKeyboardPress(DIK_LEFT))
		{
				dir.x = -1.0;
				//posx += vel.x;
		}

		if (GetKeyboardPress(DIK_RIGHT))
		{
				dir.x = 1.0;
				//posx += vel.x;	
		}
		if (GetKeyboardPress(DIK_UP))
		{
				dir.y = -1.0;
				//posy -= vel.y;	
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			    dir.y = 1.0;
				//posy += vel.y;

			//�n�ʂɐڂ��Ă��鎞

			//�󒆂ɂ���Ƃ�

		}
		//�ړ��������x�N�g�����K��
		D3DXVec2Normalize(&dir, &dir);
		vel = dir * mPlayer->getSpeed();

		pos.x += vel.x;
		pos.y += vel.y;

		//�V�KY�̒l����r�Ώۂł���ABlock�̏�ӂ�Y���W���傫����΁A�v���C�����W�͓��͑O�̒l�ɖ߂�
		if (pos.y > 800) //������if����CollisionComponent�œ����蔻��̖߂�l�������Ƃ��Ă����B
		//if (checkBlock == false)
		{
			pos.y = lastpos.y;
			//pos
		}


		mOwner->SetPos(pos.x, pos.y);
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






