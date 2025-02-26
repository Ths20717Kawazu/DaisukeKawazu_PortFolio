#include "game.h"
#include "Block.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "texture.h"


Block::Block(Game* game, enum Actor::Tag tag, float posX, float posY, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot) : Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this,200);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/Block.png"));
	GetGame()->AddBlock(this);
	SetACTOR(posX, posY, BoxH, BoxW, UvU, UvV, VH, VW, Rot);
	//Gridへの登録
	//インスタンス化した段階であると、全てのブロックの当初の場所が同じであることから、登録されるＧｒｉｄがすべて同じになってしまう。
	//原因究明にいたらなかったが、Updateの段階でGridに登録しないと正常に登録されない
	/*GetGame()->getGrid(posX, posY)->addMembersIngrid(this);
	mMygrid = GetGame()->getGrid(posX, posY);*/
}

Block::~Block() 
{
	GetGame()->RemoveBlock(this);
}

void Block::UpdateActor()
{
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);

	//GetGame()->GetPlayer() == NULL ||
		//プレイヤの移動速度を入手して、逆方向へ移動させる
	//=================================================//
	/*	D3DXVECTOR2 Pvel;
	if ( GetGame()->GetPlayer()->GetState() == Actor::EActive)
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
		SetPos(mActor.pos.x, mActor.pos.y);*/
	//=================================================//
	//else if(GetGame()->GetPlayer() == NULL)
	//{
	//	SetPos(100, 500);

	//}
}

