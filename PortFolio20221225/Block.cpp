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
	//Grid�ւ̓o�^
	//�C���X�^���X�������i�K�ł���ƁA�S�Ẵu���b�N�̓����̏ꏊ�������ł��邱�Ƃ���A�o�^�����f�����������ׂē����ɂȂ��Ă��܂��B
	//���������ɂ�����Ȃ��������AUpdate�̒i�K��Grid�ɓo�^���Ȃ��Ɛ���ɓo�^����Ȃ�
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
		//�v���C���̈ړ����x����肵�āA�t�����ֈړ�������
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

