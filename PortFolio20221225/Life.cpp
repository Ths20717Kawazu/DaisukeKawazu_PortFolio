#include "Life.h"
#include "SpriteComponent.h"
#include "texture.h"

Life::Life(Game* game, Actor::Tag tag) : Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this, 750);
	SC->SetTextureID(LoadTexture((char*)"images/Life.png"));
	GetGame()->AddLife(this);
}

Life::~Life()
{
	GetGame()->RemoveLife(this);

};

void Life::UpdateActor()
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