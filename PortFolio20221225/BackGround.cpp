#include "BackGround.h"
#include "Game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"


BackGround::BackGround(Game* game, enum Actor::Tag tag):Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 100);
	SC->SetTextureID(LoadTexture((char*)"images/mori.jpg"));
}

BackGround::~BackGround() {};

void BackGround::UpdateActor() 
{
	//プレイヤの移動速度を入手して、逆方向へ移動させる
	//=================================================//
	D3DXVECTOR2 Pvel;
	if (GetGame()->GetPlayer()->GetState() == Actor::EActive) 
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

//初期化の際に、Playerのコンストラクタが呼び出される前にBackgroundのコンストラクタが呼び出されるため
//GetPosはNULLであるためエラーが発生する。よって、描画順序とコンストラクタは別にする必用がある。
  //mPlayerPos = GetPPos();
};