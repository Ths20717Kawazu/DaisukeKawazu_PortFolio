#include "UserInterface.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"

UserInterface::UserInterface(Game* game, Actor::Tag tag) :Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 700);
	SC->SetTextureID(LoadTexture((char*)"images/UI_Shita.png"));

}

UserInterface::~UserInterface() {};

void UserInterface::UpdateActor()
{
	//プレイヤの移動速度を入手して、常に画面の同じ場所に固定させる
	//=================================================//
	D3DXVECTOR2 Pvel;
	D3DXVECTOR2 Ppos;


	Pvel = GetGame()->GetPlayer()->getVel();
	Ppos = GetGame()->GetPlayer()->GetPos();
	/*if (Ppos.x > 1000) 
	{
		mActor.pos += Pvel;
	}*/
	

	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

	//プレイヤが画面外へ移動するのを防がれた際の処理


}