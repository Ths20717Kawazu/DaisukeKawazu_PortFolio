#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(class Actor* Owner, class Player* Player) :SpriteComponent(Owner, Player), mInterval(10)
{

}


void AnimationComponent::AddImage(int img) {

	mImages.emplace_back(img);
}

void AnimationComponent::Update() 
{
	
	//mTimer++;
	///*if (mTimer >= 10) 
	//{
	//	mTimer = 0;
	//}*/
	//if (mTimer == mInterval) 
	//{
	//	mTimer = 0;
	//	idx = GetIdx();
	//	idx++;
	//	SetIdx(idx);
	//	
	//	if (AnimationComponent::GetIdx() == mImages.size())
	//	{
	//		SetIdx(0);
	//	}
	//}
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
	//ì¸óÕÇµÇΩäGÇï\é¶Ç∑ÇÈÅB
	SpriteComponent::Draw();
}
