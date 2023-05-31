#include "Obstacle.h"
#include "Enemy.h"
#include "game.h"
#include "texture.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"



Obstacle::Obstacle(Game* game, enum Actor::Tag tag) :Actor(game, tag),
mDamage(100)
{
	mHP = 100;
	auto SC = new SpriteComponent(this,200);
	auto CC = new CollisionComponent(this);
	SC->SetTextureID(LoadTexture((char*)"images/obstacle.png"));
	GetGame()->AddObstacle(this);
}

Obstacle::~Obstacle() {


}

void Obstacle::UpdateActor() 
{
	//�v���C���̈ړ����x����肵�āA�t�����ֈړ�������
//=================================================//
	D3DXVECTOR2 Pvel;
	//Player�����ł����ۂɁAUpdateActor���X�V����Ȃ��Ȃ�s������L�̏����������ĉ�������B
	//Player�̈ʒu�����擾�������镔���ɂ��ẮA���̏��������s��
	if (GetGame()->GetPlayer()->GetState() == Actor::EActive) 
	{
		Pvel = GetGame()->GetPlayer()->getVel();
		mActor.pos -= Pvel;
	}
	SetPos(mActor.pos.x, mActor.pos.y);
	//=================================================//

	for (auto enemy : GetGame()->GetEnemies()) 
	{
		if (HitCheckBC(Obstacle::GetPos(), 100, enemy->GetPos(), 100))
		{
			enemy->Damage(mDamage);
			Actor::SetState(EDead);
			//hit = true;
		};
	}
}
