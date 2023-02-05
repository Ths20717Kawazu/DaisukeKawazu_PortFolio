#pragma once
#include "InputComponent.h"
#include <stdlib.h>
#include <iostream>


InputComponent::InputComponent(Actor* Owner):MoveComponent(Owner)
{

}

InputComponent::~InputComponent() {};



void InputComponent::ProcessInput(void) 
{
	
	D3DXVECTOR2 dir(0,0);
	float posx = 0;
	float posy = 0;
	posx = mOwner->GetACTOR().pos.x;
	posy = mOwner->GetACTOR().pos.y;

	if (GetKeyboardPress(DIK_LEFT)) 
	{
		//mPlayer->playerState = mPlayer->FACE_LEFT;

		posx += -10.0f;
	}

	if (GetKeyboardPress(DIK_RIGHT))
	{
		//mPlayer->playerState = mPlayer->FACE_RIGHT;
		posx += 10.0f;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		//mPlayer->playerState = mPlayer->JUMP;
		posy -= 10.0f;
	}
	if (GetKeyboardPress(DIK_DOWN)) 
	{
		//’n–Ê‚ÉÚ‚µ‚Ä‚¢‚éŽž
				
		//‹ó’†‚É‚¢‚é‚Æ‚«

		posy += 10.0f;
	}
		mOwner->SetACTOR(posx, posy);
		
};



