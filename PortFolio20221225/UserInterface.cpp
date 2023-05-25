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
	//�v���C���̈ړ����x����肵�āA��ɉ�ʂ̓����ꏊ�ɌŒ肳����
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

	//�v���C������ʊO�ֈړ�����̂�h���ꂽ�ۂ̏���


}