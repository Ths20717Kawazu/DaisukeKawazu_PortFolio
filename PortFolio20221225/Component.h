#pragma once
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
//#include "AnimationComponent.h"


class Component
{
	public:
		Component(class Actor* Owner);
		Component(class Actor* Owner, class Player* Player);
		virtual ~Component();
		virtual void ProcessInput() {};
		virtual void Update() {};
		bool tempCollision{ false };//�A�N�^�̃f�X�g���N�^�Ŋe�R���|�l���g���폜����ۂ�CollisionComponent�̍폜�̒i�K�Ń������ǂݎ��G���[���������邽��

	protected:
		class Actor* mOwner;
		class Player* mPlayer{nullptr};
		//class AnimationComponent* manimcomp{ nullptr };
	
};

