#pragma once
#include "Actor.h"
#include "Component.h"
#include "game.h"

Actor::Actor(Game* game, enum Tag tag): mGame(game),mState(EActive), mTag(tag)
{
	mGame->AddActor(this);	
}

Actor::~Actor() 
{
	//Game�N���X�ŏW���Ǘ����Ă���Actor�z��mActors����{�A�N�^���폜����B
	mGame->RemoveActor(this);
	//�A�N�^�ɃA�^�b�`����Ă���S�Ă�Component�̎q�N���X���폜
	/*while (!mComponents.empty()) 
	{
		for (auto component : mComponents) 
		{
			delete component;
		}
	}*/
	while (!mComponents.empty())
	{
		auto component = mComponents.back();
		mComponents.pop_back();
		delete component;
	}

};

void Actor::AddComponent(Component* component) 
{
	mComponents.emplace_back(component);

}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}


void Actor::ProcessInput(void)
{
	//Player�͔�΂��Ă��̂܂�Component�[��InputComponent��ProcessInput���Ăяo�����
	for (auto comp : mComponents) {
		comp->ProcessInput();
	}

};




