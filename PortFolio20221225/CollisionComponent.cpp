#include "CollisionComponent.h"
#include "game.h"

CollisionComponent::CollisionComponent(class Actor* Owner) :Component(Owner)
{


}


CollisionComponent::CollisionComponent(class Actor* Owner, class Player* Player):Component(Owner, Player)
{
		
	
}

void CollisionComponent::Update() 
{

	//全てのActorを呼び出して、総当たりできるように変更

	//for(auto actor : )
	//HitCheckBC(mOwner->GetACTOR().pos, 50, m )
}


//境界円（バウンディングサークル）の当たり判定
	bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
	{
		D3DXVECTOR2 vDist;//2つの円の距離を保存する変数
			vDist.x = posB.x - posA.x;
			vDist.y = posB.y - posA.y;

			//２つの円を繋ぐベクトルを作る
		    vDist = posB - posA;
		//作成したベクトルの大きさ（２つの円の距離）を計算する
			float length = D3DXVec2Length(&vDist);
		//２つの円の半径を足した値を作る
			float r = rA + rB;

		//距離と半径を比較し、距離のほうが大きければ当たっていない
		if (length > r)
			return false;
		else
			return true;
	}

//移動先の障害物、床との衝突判定　→　衝突判定を総当たりする負荷を低減するために別で用意する。
//InputComponent での使用を想定する。
	//bool CheckObstacles(D3DXVECTOR2 posA);