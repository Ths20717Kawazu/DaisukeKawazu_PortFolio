#pragma once
#include "main.h"
#include <vector>

class Game
{
public:
	//float frand(void);
	bool HitCheckBB(
		D3DXVECTOR2 boxApos,
		float boxAwidth,
		float boxAheight,
		D3DXVECTOR2 boxBpos,
		float boxBwidth,
		float boxBheight
	);

	void gameProcessInput(void);
	void gameInit(void);
	void gameUninit(void);
	void gameUpdate(void);
	void gameDraw(void);
	void gameRunloop(void);


	//void SetPlayer(class Player* player) { mPlayer = player;  }
	void AddPlayer(class Player* player) { mPlayer = player; }
	void AddBalloon(class Balloon* balloon) { mBalloon = balloon; }
	
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//�u���b�N��p�̔z��
	void AddBlock(class Block* block);
	//�G��p�̔z��
	void AddEnemy(class Enemy* enemy);

	void AddSprites(class SpriteComponent* sprite);

	Player* GetPlayer() { return mPlayer; }
	Balloon* GetBalloon() { return mBalloon; }
	std::vector<class Actor*>& GetActors() { return mActors; }
	std::vector<class Block*>& GetBlocks() { return mBlocks; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }

	

private:
	std::vector<class Actor*>mActors;
	std::vector<class Block*>mBlocks;
	std::vector<class Enemy*>mEnemies;
	std::vector<class SpriteComponent*>mSprites;
	Balloon* mBalloon;
	Player* mPlayer;
};

