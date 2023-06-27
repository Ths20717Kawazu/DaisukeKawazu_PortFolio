
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

//========================�ǉ�======================//

#define PLAYER_HEIGHT (200.0f)
#define PLAYER_WIDTH (200.0f)

//********�f�o�b�O�p***********************************************************
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
	//���A�j���[�V�������Ȃ��A�N�^�ɂ��ẮA�K��SetActor�ŏ����̕\���T�C�Y����ݒ肷�邱�ƁB

	a = new UserInterface(this, Actor::Background);
	a->SetACTOR(950.0f, 400.0f, 500.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	a = new BackGround(this, Actor::Background);
	a->SetACTOR(1000.0f, 1000.0f, 2000.0f, 2000.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);

	for (int i = 0; i < 5; i++)
	{
		a = new Life(this, Actor::Background, 950.0f + 50 * i, 870.0f, 50.0f, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, i);
	}

	for (int Y = 0; Y < 10; Y++) //�s
	{
		for (int X = 0; X < 100; X++)//�� 
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
	// �o�b�N�o�b�t�@�N���A
	ClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Clear();
	//�`����{
	gameProcessInput();
	gameDraw();
	gameUpdate();

	//�o�b�N�o�b�t�@�A
	SwapBuffers();
}

void Game::gameUpdate(void) {
	////=======�f�o�b�O�p========//
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


//�`��͕ʂɗp�ӂ���
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
				//�A�j���[�V�����𔺂�Actor�̕`�揈��
				component->UpdateDraw();
				//�A�j���[�V����������Actor�̕`�揈��
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
		//����Actor�ƃP�c��Actor�����ւ���(������R�s�[����������邽��)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}


void Game::gameProcessInput(void) {
	UpdateInput();//���͏����̍X�V�����@input.cpp
	mPlayer->ProcessInput();//�v���C���̓��͂̍X�V
	//�����̊m�F�p
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

//�Փ˔���p�ɁA�G�ƃu���b�N�𕪂��āA���ꂼ�ꔻ�肷��B
void Game::AddBlock(class Block* block) 
{
	mBlocks.emplace_back(block);
}

void Game::RemoveBlock(class Block* block)
{
	// swap����pop_back�ł��Ȃ��Bswap���Ă��܂��Ə��Ԃ�����邽��
	auto iter = std::find(mBlocks.begin(), mBlocks.end(), block);
	mBlocks.erase(iter);
}

//�Փ˔���p�ɁA�G�ƃu���b�N�𕪂��āA���ꂼ�ꔻ�肷��B
void Game::AddEnemy(class Enemy* enemy) 
{
	mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(class Enemy* enemy)
{
	// swap����pop_back�ł��Ȃ��Bswap���Ă��܂��Ə��Ԃ�����邽��
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	mEnemies.erase(iter);
}


void Game::AddLife(class Life* life) 
{
	mLives.emplace_back(life);
}
void Game::RemoveLife(class Life* life)
{
	// swap����pop_back�ł��Ȃ��Bswap���Ă��܂��Ə��Ԃ�����邽��
	auto iter = std::find(mLives.begin(), mLives.end(), life);
	mLives.erase(iter);
}




void Game::AddSprites(SpriteComponent* sprite) 
{
	int curDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();//Sprite�z��̐擪�A�h���X����
	//�������`��D��x���傫��sprite��T���A���̎�O��Insert����B
	for (; iter < mSprites.end(); iter++) 
	{
		if (curDrawOrder < (*iter)->GetDrawOrder()) 
		{
			break;
		}
	}
	//�������傫���`��D��x�����������_��Sprite�z���Insert����B
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// swap����pop_back�ł��Ȃ��Bswap���Ă��܂��Ə��Ԃ�����邽��
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}


//�Q�[���N���A���𔻒�
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
	//xutility�ɂė�O�������A�����炭�p�ӂ���Grid�͈̔͂���E���Ă��邽�߂ɔ�������Ɛ��@�A
	//���}�I��row�i�s�j��+�Q�i�����͓K���A�����������ɂ���ƒ����ɓ��l�̗�O��������������B�j���đΏ�����B
	return mGrids[row + 2][column];
}