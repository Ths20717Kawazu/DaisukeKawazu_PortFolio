﻿#pragma once
#include "game.h"
#include "InputComponent.h"
#include "CollisionComponent.h"
#include "Balloon.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include <stdlib.h>
#include <iostream>

enum Scene;

//InputComponent::InputComponent(Actor* Owner):MoveComponent(Owner)
//{
//
//}

InputComponent::InputComponent(Actor* Owner, class Player* Player):MoveComponent(Owner, Player)
{

}

InputComponent::~InputComponent() {};

void InputComponent::ProcessInput(void)
{

	if (mPlayer->GetGame()->GetScene() == mPlayer->GetGame()->Game::OPENING) 
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			mPlayer->GetGame()->SetScene(Game::STAGE);
		}
	}
	

	if (mPlayer->GetGame()->GetScene() == mPlayer->GetGame()->Game::STAGE)
	{
		buffertime++;//OPENINGでの操作がダイレクトに反映されないよう、バッファを設定する。
		if (buffertime > 50)
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
					dir.x = 1.0f;
					mPlayer->setDir(dir);
				}

				if (GetKeyboardPress(DIK_DOWN))
				{
					/*dir.y = 1.0f;
					mPlayer->setDir(dir);*/
				}

				if (mPlayer->getIsInAir() == false && GetKeyboardTrigger(DIK_SPACE))
				{
					//float lift = mPlayer->GetLift();
					dir.y = -1.0f;
					mPlayer->SetJumpVel(-20.0f);

					mPlayer->setDir(dir);
					mPlayer->setIsInAir(true);
				}
				//if if と　if else ifの組み合わせは挙動が異なる

				if (!mPlayer->GetHasballoon())
				{
					if (GetKeyboardTrigger(DIK_RETURN))
					{
						Actor* a;
						a = new Balloon(mPlayer->GetGame(), Actor::Balloon);
						a->SetACTOR(mPlayer->Actor::GetPos().x + 50, mPlayer->Actor::GetPos().y - 50, 250.0f, 250.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
						mPlayer->SetHasballoon(true);
					}
				}

				else if (mPlayer->GetHasballoon())
				{
					/*if (HitCheckBC(mPlayer->GetGame()->GetBalloon()->GetPos(), 150, mPlayer->GetGame()->GetObstacle()->GetPos(), 150))
					{
						if (GetKeyboardTrigger(DIK_RETURN))
						{
							mPlayer->GetGame()->GetBalloon()->SetOwner(mPlayer->GetGame()->GetObstacle());
						}
					}*/
					////風船をリリース
					if (GetKeyboardTrigger(DIK_RETURN))
					{
						mPlayer->GetGame()->GetBalloon()->SetOwner(0);
					}
					mPlayer->setDir(dir);

				}

			}
		}
	}
}

	







			//複数のObstaclesを利用する場合下記コードでは正常に機能いしないので要修正
			/*for (auto obstacle : mPlayer->GetGame()->GetObstacles()) 
			{

				if (HitCheckBC(mPlayer->GetGame()->GetBalloon()->GetPos(), 150, obstacle->GetPos(), 150))
				{
					if (GetKeyboardTrigger(DIK_RETURN))
					{
						mPlayer->GetGame()->GetBalloon()->SetOwner(obstacle);
					}
				}
			}*/

			//Enemyにバルーンをとりつける。（下記のとおりだと、対象は範囲内のEnemyの配列順の小さい方が優先される→距離を優先するよう修正する）
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