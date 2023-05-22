#include "game.h"
#include "UserInterface.h"
#include "Block.h"
#include "SpriteComponent.h"
#include "texture.h"

UserInterface::UserInterface(class Game* game, enum Actor::Tag tag) :Actor(game, tag)
{
	auto SC = SpriteComponent(this, 700);

};

UserInterface::~UserInterface() {};

void UserInterface::UpdateActor()
{
	//プレイヤの移動速度を入手して、常に画面の同じ場所に固定させる
	//=================================================//
	D3DXVECTOR2 Pvel;
	Pvel = GetGame()->GetPlayer()->getVel();
	mActor.pos += Pvel;

	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

	//プレイヤが画面外へ移動するのを防がれた際の処理


}