#pragma once
#include "game.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "Balloon.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
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
		
		if (GetKeyboardPress(DIK_DOWN))
		{
			dir.y = 1.0;
			mPlayer->setDir(dir);
		}

		if (!mPlayer->getIsInAir() && GetKeyboardTrigger(DIK_SPACE))
		{
			dir.y = -1.0;
			mPlayer->SetJumpVel(-30.0f);
			mPlayer->setDir(dir);
			mPlayer->setIsInAir(true);
		}
		//if if �Ɓ@if else if�̑g�ݍ��킹�͋������قȂ�
		if (!mPlayer->GetHasballoon())
		{
			if (GetKeyboardTrigger(DIK_RETURN)) 
			{
				Actor* a;
				a = new Balloon(mPlayer->GetGame(), 100);
				a->SetACTOR(mPlayer->getPos().x + 50, mPlayer->getPos().y - 50, 250.0f, 250.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
				mPlayer->SetHasballoon(true);
			}
		}
		else if (mPlayer->GetHasballoon()) 
		{

			
			if (HitCheckBC(mPlayer->GetGame()->GetBalloon()->GetPos(), 150, mPlayer->GetGame()->GetObstacle()->GetPos(), 150))
			{
				if (GetKeyboardTrigger(DIK_RETURN))
				{
					mPlayer->GetGame()->GetBalloon()->SetOwner(mPlayer->GetGame()->GetObstacle());
				}
			}
			////���D�������[�X
			//else if (GetKeyboardTrigger(DIK_RETURN))
			//{
			//	 mPlayer->GetGame()->GetBalloon()->SetOwner(0);
			//}


			//Enemy�Ƀo���[�����Ƃ����B�i���L�̂Ƃ��肾�ƁA�Ώۂ͔͈͓���Enemy�̔z�񏇂̏����������D�悳���j
			/*for (auto enemy : mPlayer->GetGame()->GetEnemies())
			{
				if (HitCheckBC(mPlayer->GetGame()->GetBalloon()->GetPos(), 200, enemy->GetPos(), 200))
				{
					if (GetKeyboardTrigger(DIK_RETURN)) 
					{
						mPlayer->GetGame()->GetBalloon()->SetOwner(enemy);
					}
				};
			}*/


		}

		//if (mPlayer->GetHasballoon()) 
		//{
		//	if (mPlayer->GetCloseToEnemy() && !mPlayer->GetTagIDs().empty())
		//	{
		//		if (GetKeyboardTrigger(DIK_RETURN)) 
		//		{
		//			for (auto tagID : mPlayer->GetTagIDs()) 
		//			{
		//				mPlayer->GetGame()->GetBalloon()->SetOwner(tagID);
		//				//mPlayer->GetGame()->GetBalloon()->SetPos(tagID->GetPos());
		//			}

		//		}

		//	}
		//}

		mPlayer->setDir(dir);

	}
}

	






