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
	//Grid‚Ö‚Ì“o˜^
	//ƒCƒ“ƒXƒ^ƒ“ƒX‰»‚µ‚½’iŠK‚Å‚ ‚é‚ÆA‘S‚Ä‚ÌƒuƒƒbƒN‚Ì“–‰‚ÌêŠ‚ª“¯‚¶‚Å‚ ‚é‚±‚Æ‚©‚çA“o˜^‚³‚ê‚é‚f‚’‚‰‚„‚ª‚·‚×‚Ä“¯‚¶‚É‚È‚Á‚Ä‚µ‚Ü‚¤B
	//Œ´ˆö‹†–¾‚É‚¢‚½‚ç‚È‚©‚Á‚½‚ªAUpdate‚Ì’iŠK‚ÅGrid‚É“o˜^‚µ‚È‚¢‚Æ³í‚É“o˜^‚³‚ê‚È‚¢
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
		//ƒvƒŒƒCƒ„‚ÌˆÚ“®‘¬“x‚ð“üŽè‚µ‚ÄA‹t•ûŒü‚ÖˆÚ“®‚³‚¹‚é
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

