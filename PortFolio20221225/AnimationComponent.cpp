#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player),
mInterval(10),
animIDs{ 0,0,0,1,2,2,2,2}
{

}


void AnimationComponent::AddImage(int img, Player::PlayerState state) {

	if (state == Player::PlayerState::EIDLE)
	{
		mImages.emplace_back(img);
	}
	/*if (state == Player::PlayerState::EIDLE) 
	{

	}
	if (state == Player::PlayerState::EIDLE) {

	}
	if (state == Player::PlayerState::EIDLE) {

	}*/

}

void AnimationComponent::Update() 
{
	
}

int index = 0;

void AnimationComponent::Draw() 
{
	mTimer++;
	//�ݒ肵���C���^�[�o�����ɕ`����X�V���Ă���
	if (mTimer == mInterval)
	{
		mTimer = 0;
		//index++;
		idx = GetIdx();
		idx++;
		SetIdx(idx);
		//�摜�z��̖����܂œ��B�����Ȃ�ID���O�ɖ߂�
		if (AnimationComponent::GetIdx() == animIDs.size())
		{
			SetIdx(0);
		}
	}
	//���͂����G���AanimIDs�z�񂩂�Ƃ肾���ĕ\������B
	
		SpriteComponent::SetTextureID(animIDs[AnimationComponent::GetIdx()]);

	//case (Player::EIDLE)
	//{

	//}
	//break;
	//case(Player::PlayerState)
	//{


	//}
	//
	


	SpriteComponent::Draw();
}


//=============================================================//
//State�ƃA�j���[�V����ID
//ID�̂O�`�R�@���@Idle

