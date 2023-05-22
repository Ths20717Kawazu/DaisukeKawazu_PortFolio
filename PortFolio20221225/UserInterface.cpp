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
	//�v���C���̈ړ����x����肵�āA��ɉ�ʂ̓����ꏊ�ɌŒ肳����
	//=================================================//
	D3DXVECTOR2 Pvel;
	Pvel = GetGame()->GetPlayer()->getVel();
	mActor.pos += Pvel;

	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

	//�v���C������ʊO�ֈړ�����̂�h���ꂽ�ۂ̏���


}