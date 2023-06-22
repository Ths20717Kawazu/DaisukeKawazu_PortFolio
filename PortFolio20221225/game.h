#pragma once
#include "main.h"
#include <vector>

class CameraComponent;//	

class Game
{
public:
	const int MapWidth = 5000;
	const int MapHeight = 2500;

	const int GridRow = 15;
	const int GridColumn = 30;

	/*bool HitCheckBB
	(
		D3DXVECTOR2 boxApos,
		float boxAwidth,
		float boxAheight,
		D3DXVECTOR2 boxBpos,
		float boxBwidth,
		float boxBheight
	);*/

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

	//ブロック専用の配列
	void AddBlock(class Block* block);
	void RemoveBlock(class Block* block);

	//敵専用の配列
	void AddEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);

	//ライフの配列
	void AddLife(class Life* life);
	void RemoveLife(class Life* life);

	void AddSprites(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void checkGameClear();

	Player* GetPlayer() { return mPlayer; }
	Balloon* GetBalloon() { return mBalloon; }
	Obstacle* GetObstacle() { return mObstacle; }
	CameraComponent* GetCamera() { return mCameraComponent; }


	std::vector<class Life*>& GetLives() { return mLives;}
	std::vector<class Actor*>& GetActors() { return mActors; }
	std::vector<class Block*>& GetBlocks() { return mBlocks; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	std::vector<class Obstacle*>& GetObstacles() { return mObstacles; }	
  	
	class Grid* getGrid(int posX, int posY);


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
	CameraComponent* mCameraComponent;
	SpriteComponent* mOPSprite;

	enum Scene 
	{
		OPENING,
		STAGE,
		ENDING
	};

	Scene scene = Scene::ENDING;
	


	bool GameClear = false;
	Grid* mGrids[15][30];


	int maps[10][100]
	{
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,3,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,0,0,0,0,0, 1,0,1,0,0,0,0,5,5,5, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,4,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,5,5,5, 5,5,5,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,3,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,2,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 1,0,1,0,1,0,1,0,1,0, 1,0,1,0,1,0,1,0,1,0, 1,0,1,0,1,0,1,0,1,0, 1,0,1,0,1,0,1,0,1,0, 1,0,1,0,1,0,1,0,1,0  }
	};
};

