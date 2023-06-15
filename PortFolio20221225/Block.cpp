#include "game.h"
#include "Block.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "texture.h"


Block::Block(Game* game, enum Actor::Tag tag) : Actor(game, tag)
{
	animate = false;
	auto SC = new SpriteComponent(this,200);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/Block.png"));
	GetGame()->AddBlock(this);

	//Grid‚Ö‚Ì“o˜^
	mMygrid = GetGame()->getGrid(Actor::GetPos().x, Actor::GetPos().y);
	mMygrid->addMembersIngrid(this);
}

Block::~Block() 
{
	GetGame()->RemoveBlock(this);
}

void Block::UpdateActor()
{
	//GetGame()->GetPlayer() == NULL ||
		//ƒvƒŒƒCƒ„‚ÌˆÚ“®‘¬“x‚ð“üŽè‚µ‚ÄA‹t•ûŒü‚ÖˆÚ“®‚³‚¹‚é
	//=================================================//
		D3DXVECTOR2 Pvel;
	if ( GetGame()->GetPlayer()->GetState() == Actor::EActive)
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
		SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//
	//else if(GetGame()->GetPlayer() == NULL)
	//{
	//	SetPos(100, 500);

	//}
}

