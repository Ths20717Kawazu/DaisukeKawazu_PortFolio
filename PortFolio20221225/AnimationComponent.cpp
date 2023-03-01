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
	//設定したインターバル毎に描画を更新していく
	if (mTimer == mInterval)
	{
		mTimer = 0;
		//index++;
		idx = GetIdx();
		idx++;
		SetIdx(idx);
		//画像配列の末尾まで到達したならIDを０に戻す
		if (AnimationComponent::GetIdx() == animIDs.size())
		{
			SetIdx(0);
		}
	}
	//入力した絵を、animIDs配列からとりだして表示する。
	
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
//StateとアニメーションID
//IDの０～３　＝　Idle

