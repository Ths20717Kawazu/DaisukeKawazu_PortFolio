#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player), mInterval(10)
{

}


void AnimationComponent::AddImage(int img) {

	mImages.emplace_back(img);
}

void AnimationComponent::Update() 
{
	
	
}

void AnimationComponent::Draw() 
{
	mTimer++;
	if (mTimer == mInterval)
	{
		mTimer = 0;
		idx = GetIdx();
		idx++;
		SetIdx(idx);

		if (AnimationComponent::GetIdx() == mImages.size())
		{
			SetIdx(0);
		}
	}
	SpriteComponent::SetTextureID(mImages[AnimationComponent::GetIdx()]);
	//入力した絵を表示する。
	SpriteComponent::Draw();
}
