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
	//bool HitCheckBC(D3DXVECTOR2 posA, float rA,
	//	D3DXVECTOR2 posB, float rB);
	//bool HitCheckBCSq(D3DXVECTOR2 posA, float rA,
	//	D3DXVECTOR2 posB, float rB);
	void gameInit(void);
	//bool gameInitialize(void);
	void gameUninit(void);
	void gameUpdate(void);
	void gameDraw(void);
	void gameRunloop(void);


	void AddActor(class Actor* actor);
	void AddSprites(class SpriteComponent* sprite);


private:
	std::vector<class Actor*>mActors;
	std::vector<class SpriteComponent*>mSprites;
};
