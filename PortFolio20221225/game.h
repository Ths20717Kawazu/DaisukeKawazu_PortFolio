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

	enum Scene 
	{
		OPENING,
		STAGE,
		ENDING
	};
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
	void AddMono(class Mono* Mono) { mMono = Mono; }
	
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

	void checkGameClear();

	Player* GetPlayer() { return mPlayer; }
	Balloon* GetBalloon() { return mBalloon; }
	Mono* GetMono() { return mMono; }
	CameraComponent* GetCamera() { return mCameraComponent; }


	std::vector<class Life*>& GetLives() { return mLives;}
	std::vector<class Actor*>& GetActors() { return mActors; }
	std::vector<class Block*>& GetBlocks() { return mBlocks; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	std::vector<class Mono*>& GetMonos() { return mMonos; }	
  	
	class Grid* getGrid(int posX, int posY);

	Scene GetScene() { return mScene; }
	void SetScene(Scene scene) { mScene = scene; }
	
private:
	std::vector<class Actor*>mActors;
	std::vector<class Block*>mBlocks;
	std::vector<class Enemy*>mEnemies;
	std::vector<class Life*> mLives;
	std::vector<class Mono*>mMonos;
	std::vector<class SpriteComponent*>mSprites;
	std::vector<class AnimationComponent*>mAnimComponents;
	Balloon* mBalloon;
	Player* mPlayer;
	Mono* mMono;
	CameraComponent* mCameraComponent;
	SpriteComponent* mOPSprite;

	Scene mScene = Scene::OPENING;
	
	bool GameClear = false;
	Grid* mGrids[15][30];


	int maps[10][100]
	{
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,6,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,5,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,4,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,5, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,3,0,0,0,0,0, 0,6,0,0,0,2,0,0,0,5, 0,0,3,0,0,3,0,0,3,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 5,5,5,5,5,5,5,5,5,5, 5,5,5,5,5,5,0,0,5,5, 5,5,5,5,5,5,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },

		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  },
		 { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0  }
	};
};

