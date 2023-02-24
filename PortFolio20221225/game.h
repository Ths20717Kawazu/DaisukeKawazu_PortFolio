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


	void SetPlayer(class Player* player) { mPlayer = player;  }
	void addPlayer(class Player* player) { mPlayer = player; }
	Player* GetPlayer() { return mPlayer; }
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//ブロック専用の配列
	void AddBlock(class Block* block);
	//敵専用の配列
	void AddEnemy(class Enemy* enemy);

	void AddSprites(class SpriteComponent* sprite);

	std::vector<class Actor*>& GetActors() { return mActors; }
	std::vector<class Block*>& GetBlocks() { return mBlocks; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }


private:
	std::vector<class Actor*>mActors;
	std::vector<class Block*>mBlocks;
	std::vector<class Enemy*>mEnemies;
	std::vector<class SpriteComponent*>mSprites;
	Player* mPlayer;
};

