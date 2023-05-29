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
	void AddObstacle(class Obstacle* obstacle) { mObstacle = obstacle; }
	
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//�u���b�N��p�̔z��
	void AddBlock(class Block* block);
	void RemoveBlock(class Block* block);

	//�G��p�̔z��
	void AddEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);

	//���C�t�̔z��
	void AddLife(class Life* life);
	void RemoveLife(class Life* life);

	void AddSprites(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);


	Player* GetPlayer() { return mPlayer; }
	Balloon* GetBalloon() { return mBalloon; }
	Obstacle* GetObstacle() { return mObstacle; }

	std::vector<class Life*>& GetLives() { return mLives;}
	std::vector<class Actor*>& GetActors() { return mActors; }
	std::vector<class Block*>& GetBlocks() { return mBlocks; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	std::vector<class Obstacle*>& GetObstacles() { return mObstacles; }	
	

private:
	std::vector<class Actor*>mActors;
	std::vector<class Block*>mBlocks;
	std::vector<class Enemy*>mEnemies;
	std::vector<class Life*> mLives;
	std::vector<class Obstacle*>mObstacles;
	std::vector<class SpriteComponent*>mSprites;
	std::vector<class AnimationComponent*>mAnimComponents;
	Balloon* mBalloon;
	Player* mPlayer;
	Obstacle* mObstacle;
	
};

