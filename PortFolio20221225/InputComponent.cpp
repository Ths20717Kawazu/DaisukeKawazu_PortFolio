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

			//地面に接している時

			//空中にいるとき

		}
		//移動方向をベクトル正規化
		D3DXVec2Normalize(&dir, &dir);
		vel = dir * mPlayer->getSpeed();

		pos.x += vel.x;
		pos.y += vel.y;

		//新規Yの値が比較対象である、Blockの上辺のY座標より大きければ、プレイヤ座標は入力前の値に戻す
		if (pos.y > 800) //ここのif文はCollisionComponentで当たり判定の戻り値を条件としていれる。
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
	//もし、入力された値を足した場合接触するかしないか判定
	//接触する場合は、入力前の位置に戻す
	/*if (CheckObstacles(mOwner->GetACTOR().pos)) 
	{

	}
	else 
	{
		mOwner->SetPos(posx, posy);
	}*/






