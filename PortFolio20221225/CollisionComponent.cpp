#include "CollisionComponent.h"


CollisionComponent::CollisionComponent(class Actor* owner) :Component(owner)
{
		
	
}

void CollisionComponent::Update() 
{
	//HitCheckBC(mOwner->GetPositionX(),  )
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