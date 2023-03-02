#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player),
mInterval(10),
animIDs{0,0,0,1,2,2,2,2}//TextureID�̔z��
{
	mOwner = Player;
	SpriteComponent::AddAnim(this);
}


AnimationComponent::AnimationComponent(class Actor* Owner): SpriteComponent(Owner),
mInterval(10)
{
	SpriteComponent::AddAnim(this);
}

//�v���C���̏�ԕʂɉ摜ID�ɓ���
void AnimationComponent::AddImage(int img, Player::PlayerState state) {

	if (state == Player::PlayerState::EIDLE)
	{
		mIdleImages.emplace_back(img);//0,1,2
	}
	if (state == Player::PlayerState::EWALK) 
	{
		mWalkImages.emplace_back(img);
	}

	
	/*if (state == Player::PlayerState::ERUN) 
	{
		mRunImages.emplace_back(img);
	}
	if (state == Player::PlayerState::EJUMP) 
	{
		mJumpImages.emplace_back(img);
	}
	if (state == Player::PlayerState::EFALL)
	{
		mFallImages.emplace_back(img);
	}*/
}


void AnimationComponent::AddImage(int img, Enemy::EnemyState state) 
{

	if (state == Enemy::EnemyState::EEIDLE)
	{
		mEIdleImages.emplace_back(img);//0,1,2
	}
}
void AnimationComponent::Update() 
{
	
}

int index = 0;

void AnimationComponent::Draw2()
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
	
	//SpriteComponent::SetTextureID(mIdleImages[0]);
	//Owner�̗L����^�O�ɂ��\������摜��؂�ւ���
	if (mOwner->GetTag() == Actor::Player) 
	{

	    SpriteComponent::SetTextureID(mIdleImages[animIDs[AnimationComponent::GetIdx()]]);
		//SpriteComponent::SetTextureID(0);
	}
	else if (mOwner->GetTag() == Actor::Enemy)

	{
		SpriteComponent::SetTextureID(mEIdleImages[0]);
		//SpriteComponent::SetTextureID(mWalkImages[0]);
	}
	//SpriteComponent::SetTextureID(1);
	SpriteComponent::Draw();


}

void AnimationComponent::DrawEnemy() 
{


	SpriteComponent::SetTextureID(3);
	SpriteComponent::Draw();
}


//=============================================================//
//State�ƃA�j���[�V����ID
//ID�̂O�`�R�@���@Idle
//
//void AnimSpriteComponent::AddImage(int img)
//{
//	mImgs.emplace_back(img);
//}
//
//void AnimSpriteComponent::Update()
//{
//	mTimer += delta;
//	if (mTimer > mInterval)
//	{
//		mTimer -= mInterval;
//		mCurIdx++;
//		mCurIdx %= mImgs.size();
//	}
//}
//
//void AnimSpriteComponent::Draw()
//{
//	SetImage(mImgs[mCurIdx]);
//	SpriteComponent::Draw();
//}
//
