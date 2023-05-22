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
}

Block::~Block() 
{
	GetGame()->RemoveBlock(this);
}

void Block::UpdateActor()
{
	//�v���C���̈ړ����x����肵�āA�t�����ֈړ�������
	//=================================================//
	D3DXVECTOR2 Pvel;
	Pvel = GetGame()->GetPlayer()->getVel();
	mActor.pos -= Pvel;

	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//
}

