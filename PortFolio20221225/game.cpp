
#pragma once

#include "main.h"
#include "CameraComponent.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Component.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Block.h"
#include "Mono.h"
#include "BackGround.h"
#include "UserInterface.h"
#include "GameOver.h"
#include "GameStart.h"
#include "Life.h"
#include "Grid.h"
#include "Opening.h"
#include "Ending.h"
#include <stdio.h>

//========================追加======================//

#define PLAYER_HEIGHT (200.0f)
#define PLAYER_WIDTH (200.0f)

//********デバッグ用***********************************************************
//enum Actor::STATE state;
//bool hit;
//int count = 0;
//*****************************************************************************
void Game::gameInit(void)
{
	mCameraComponent = new CameraComponent();
	//mOpening = new Opening(this, Actor::OPENING, 100.0f, 100.0f, 500.0f, 500.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	Grid* grid;
	for (int j = 0; j < Game::GridRow; j++)
	{
		for (int i = 0; i < Game::GridColumn; i++)
		{
			grid = new Grid();
			mGrids[j][i] = grid;
		}
	}

	Actor* a;

	a = new Opening(this, Actor::OPENING);
	a->SetACTOR(1000.0f, 1000.0f, 2000.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	a = new Ending(this, Actor::ENDING);
	a->SetACTOR(1000.0f, 1000.0f, 2000.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	a = new GameStart(this, Actor::Background);
	a->SetACTOR(1000.0f, 500.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	//※アニメーションしないアクタについては、必ずSetActorで初期の表示サイズ等を設定すること。

	a = new UserInterface(this, Actor::Background);
	a->SetACTOR(950.0f, 400.0f, 500.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	a = new BackGround(this, Actor::Background);
	a->SetACTOR(1000.0f, 1000.0f, 2000.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	for (int i = 0; i < 5; i++)
	{
		a = new Life(this, Actor::Background, 950.0f + 50 * i, 870.0f, 50.0f, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, i);
	}

	for (int Y = 0; Y < 10; Y++) //行
	{
		for (int X = 0; X < 100; X++)//列 
		{
			if (maps[Y][X] == 1) a = new Block (this, Actor::Block, 100.0f * X, 100.0f * Y, 200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			if (maps[Y][X] == 2) a = new Mono  (this, Actor::Mono, 100.0f * X, 100.0f * Y, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			if (maps[Y][X] == 3) a = new Enemy (this, Actor::Enemy, 100.0f * X, 100.0f * Y, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			if (maps[Y][X] == 4) a = new Player(this, Actor::Player, 100.0f * X, 100.0f * Y, PLAYER_HEIGHT, PLAYER_WIDTH, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
			if (maps[Y][X] == 5) a = new Block (this, Actor::Block, 100.0f * X, 100.0f * Y, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
		}
	}

}


void Game::gameUninit(void) {

	delete mActors.back();

}

void Game::gameRunloop(void)
{
	// バックバッファクリア
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//描画実施
	gameProcessInput();
	gameDraw();
	gameUpdate();

	//バックバッファ、
	SwapBuffers();
}

void Game::gameUpdate(void) {
	////=======デバッグ用========//
	//for (auto enemy : mEnemies) {
	//	state = enemy->GetState();
	//	hit = enemy->hit;
	//	count = enemy->count;
	//}
	//========================//
	//Actor* a;
	

	switch (mScene)
	{
	case OPENING:
		for (auto actor : mActors)
		{
			if(actor->GetTag() == Actor::OPENING)
			//if (actor->GetTag() == Actor::Background)
			{
				actor->UpdateActor();
			}
		}
		break;
	case STAGE:
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
		break;
	case ENDING:
		for (auto actor : mActors)
		{
			if (actor->GetTag() == Actor::ENDING)
			{
				actor->UpdateActor();
			}
		}
		break;
	}


}


//描画は別に用意する
void Game::gameDraw(void)
{
	switch (mScene)
	{
	case OPENING:
		for (auto component : mSprites)
		{
			if (component->getOwner()->GetTag() == Actor::OPENING)
			{
				component->StaticDraw();
			}
		}

		break;
	case STAGE:
		for (auto component : mSprites)
		{
				//アニメーションを伴うActorの描画処理
				component->UpdateDraw();
				//アニメーションが無いActorの描画処理
				component->StaticDraw();
		}
		break;
	case ENDING:
		for (auto component : mSprites)
		{
			if (component->getOwner()->GetTag() == Actor::ENDING)
			{
				component->StaticDraw();
			}
		}
		break;
	}
};

void Game::RemoveActor(class Actor* actor) 
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}


void Game::gameProcessInput(void) {
	UpdateInput();//入力処理の更新処理　input.cpp
	mPlayer->ProcessInput();//プレイヤの入力の更新
	//消去の確認用
	//Life* life;
	//if (GetKeyboardPress(DIK_SPACE))
	//{
	//	/*if (!mEnemies.empty()) {
	//		delete mEnemies.back();

	//	}*/
	//    //delete mPlayer;
	//	life = GetLives();
	//	life->Actor::SetState(Actor::EDead);
	//}

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

void Game::RemoveBlock(class Block* block)
{
	// swapしてpop_backできない。swapしてしまうと順番が崩れるため
	auto iter = std::find(mBlocks.begin(), mBlocks.end(), block);
	mBlocks.erase(iter);
}

//衝突判定用に、敵とブロックを分けて、それぞれ判定する。
void Game::AddEnemy(class Enemy* enemy) 
{
	mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(class Enemy* enemy)
{
	// swapしてpop_backできない。swapしてしまうと順番が崩れるため
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	mEnemies.erase(iter);
}


void Game::AddLife(class Life* life) 
{
	mLives.emplace_back(life);
}
void Game::RemoveLife(class Life* life)
{
	// swapしてpop_backできない。swapしてしまうと順番が崩れるため
	auto iter = std::find(mLives.begin(), mLives.end(), life);
	mLives.erase(iter);
}




void Game::AddSprites(SpriteComponent* sprite) 
{
	int curDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();//Sprite配列の先頭アドレスを代入
	//自分より描画優先度が大きいspriteを探し、その手前にInsertする。
	for (; iter < mSprites.end(); iter++) 
	{
		if (curDrawOrder < (*iter)->GetDrawOrder()) 
		{
			break;
		}
	}
	//自分より大きい描画優先度を見つけた時点でSprite配列にInsertする。
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// swapしてpop_backできない。swapしてしまうと順番が崩れるため
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}


//ゲームクリアかを判定
void Game::checkGameClear() 
{
	if (mPlayer->GetPos().x > 400) 
	{
		Actor* a;
		a = new GameOver(this, Actor::Background);
		a->SetACTOR(1000.0f, 500.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	}
}

Grid* Game::getGrid(int posX, int posY) 
{
	int column = posX / Grid::GridWidth;
	int row = posY / Grid::GridHeight;
	//xutilityにて例外が発生、おそらく用意したGridの範囲を逸脱しているために発生すると推察、
	//応急的にrow（行）に+２（数字は適当、ただし負数にすると直ぐに同様の例外処理が発生する。）して対処する。
	return mGrids[row + 2][column];
}