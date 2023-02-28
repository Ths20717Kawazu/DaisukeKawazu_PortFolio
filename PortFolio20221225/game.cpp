
#pragma once

#include "main.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Component.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Block.h"
#include "Obstacle.h"

//========================追加======================//

#define PLAYER_HEIGHT (300.0f)
#define PLAYER_WIDTH (300.0f)


//********デバッグ用***********************************************************
//enum Actor::STATE state;
//bool hit;
//int count = 0;
//*****************************************************************************

void Game::gameInit(void) {
	Actor* a;
	a = new Player(this, 1);
	a->SetACTOR(100.0f, 350.0f, PLAYER_HEIGHT, PLAYER_WIDTH, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	for (int i = 0; i < 5; i++) {
		a = new Enemy(this, (1000 + i));
		a->SetACTOR(100 * i * 2 + 500, 200.0f, 200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	}
	
	for (int i = 0; i < 20; i++) {
		a = new Block(this, 10000);
		a->SetACTOR(100.0f * i, 900.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	}

	a = new Obstacle(this, 10000);
	a->SetACTOR(1300.0f,  800.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	//for (int i = 0; i < 4; i++) {
	//	a = new Obstacle(this, (10000 + i + 5));
	//	a->SetACTOR(i * 150 + 800.0f,  800.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	//}

	for (int i = 0; i < 3; i++) {
		a = new Block(this, 10000);
		a->SetACTOR(100.0f * i, 700.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}


void Game::gameUninit(void) {

	//delete mActors.back();

}

void Game::gameUpdate(void) {
	////=======デバッグ用========//
	//for (auto enemy : mEnemies) {
	//	state = enemy->GetState();
	//	hit = enemy->hit;
	//	count = enemy->count;
	//}
	//========================//

	
	
	for (auto actor : mActors) 
	{
		if (actor->GetState() == Actor::EActive) 
		{
			actor->UpdateActor();
		}

		if (actor->GetState() == Actor::EDead)
		{
			delete actor;
		}
	}


}

void Game::gameRunloop(void) 
{
	
	//StartTime;

	// バックバッファクリア
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//描画実施
	
	gameProcessInput();
	gameDraw();
	gameUpdate();
	//バックバッファ、
	SwapBuffers();
	
	//EndTime;
}

//描画は別に用意する
void Game::gameDraw(void) 
{
	for (auto component : mSprites)
	{
		component->Draw();
	}
};

void Game::RemoveActor(class Actor* actor) {
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}


void Game::gameProcessInput(void) {
	UpdateInput();//入力処理の更新処理
	for (auto actor : mActors)
	{
		actor->ProcessInput();
	}

	//消去の確認用
	/*if (GetKeyboardPress(DIK_SPACE)) {
		if (!mActors.empty()) {
			delete mActors.back();

		}
	}*/

}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

//衝突判定用に、敵とブロックを分けて、それぞれ判定する。
void Game::AddBlock(class Block* block) 
{
	mBlocks.emplace_back(block);
}

//衝突判定用に、敵とブロックを分けて、それぞれ判定する。
void Game::AddEnemy(class Enemy* enemy) {

	mEnemies.emplace_back(enemy);
}

void Game::AddSprites(SpriteComponent* sprite) 
{
	mSprites.emplace_back(sprite);
}
