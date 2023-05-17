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
	//設定したインターバル毎に描画を更新していく
	if (mTimer == mInterval)
	{
		mTimer = 0;
		mIndex++;
		//画像配列順序の末尾まで到達したならIndexを０に戻す。
		if (mIndex == mOwner->GetActorAnimOrders().size())
		{
			mIndex = 0;
		}
	}
	//セットする画像の番号（ID）はAnimOrdersのmIndex番目に示されている。
	//SpriteComponent::SetTextureID(mOwner->GetActorAnimImages()[0]);
	SpriteComponent::SetTextureID(mOwner->GetActorAnimImages()[mOwner->GetActorAnimOrders()[mIndex]]);
	//セットした画像を表示
	SpriteComponent::Draw();
}
