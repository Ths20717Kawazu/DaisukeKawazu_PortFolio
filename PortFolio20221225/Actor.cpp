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
	//Gameクラスで集中管理しているActor配列mActorsから本アクタを削除する。
	mGame->RemoveActor(this);
	//アクタにアタッチされている全てのComponentの子クラスを削除
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
	//InputComponentはPlayerのみが保有しているため、ProcessInputが自動的に呼び出される
	for (auto comp : mComponents) {
		comp->ProcessInput();
	}

};




