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
	//�v���C���̈ړ����x����肵�āA�t�����ֈړ�������
	//=================================================//
	D3DXVECTOR2 Pvel;
	if (GetGame()->GetPlayer()->GetState() == Actor::EActive) 
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

//�������̍ۂɁAPlayer�̃R���X�g���N�^���Ăяo�����O��Background�̃R���X�g���N�^���Ăяo����邽��
//GetPos��NULL�ł��邽�߃G���[����������B����āA�`�揇���ƃR���X�g���N�^�͕ʂɂ���K�p������B
  //mPlayerPos = GetPPos();
};