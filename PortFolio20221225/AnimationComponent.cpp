#include "AnimationComponent.h"

//AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player),
//mInterval(10)
//{
//	mOwner = Player;
//	SpriteComponent::AddAnim(this);
//}


AnimationComponent::AnimationComponent(class Actor* Owner, int drawOrder): SpriteComponent(Owner, drawOrder),
mInterval(10)
{
	
	mOwner = Owner;
	SpriteComponent::AddAnim(this);
}

AnimationComponent::~AnimationComponent() {};



void AnimationComponent::UpdateDraw()
{
	mTimer++;
	//�ݒ肵���C���^�[�o�����ɕ`����X�V���Ă���
	if (mTimer == mInterval)
	{
		mTimer = 0;
		mIndex++;
		//�摜�z�񏇏��̖����܂œ��B�����Ȃ�Index���O�ɖ߂��B
		if (mIndex == mOwner->GetActorAnimOrders().size())
		{
			mIndex = 0;
		}
	}
	//�Z�b�g����摜�̔ԍ��iID�j��AnimOrders��mIndex�ԖڂɎ�����Ă���B
	//SpriteComponent::SetTextureID(mOwner->GetActorAnimImages()[0]);
	SpriteComponent::SetTextureID(mOwner->GetActorAnimImages()[mOwner->GetActorAnimOrders()[mIndex]]);
	//�Z�b�g�����摜��\��
	SpriteComponent::Draw();
}
