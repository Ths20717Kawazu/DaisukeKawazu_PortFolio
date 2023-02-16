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
			//地面に接している時

			//空中にいるとき

		}
		mPlayer->setDir(dir);


		//新規Yの値が比較対象である、Blockの上辺のY座標より大きければ、プレイヤ座標は入力前の値に戻す
		//if (pos.y > 800) //ここのif文はCollisionComponentで当たり判定の戻り値を条件としていれる。
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
	//もし、入力された値を足した場合接触するかしないか判定
	//接触する場合は、入力前の位置に戻す
	/*if (CheckObstacles(mOwner->GetACTOR().pos)) 
	{

	}
	else 
	{
		mOwner->SetPos(posx, posy);
	}*/






