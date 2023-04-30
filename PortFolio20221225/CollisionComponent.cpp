#include "CollisionComponent.h"
#include "game.h"

CollisionComponent::CollisionComponent(class Actor* Owner) :Component(Owner)
{


}


//CollisionComponent::CollisionComponent(class Actor* Owner, class Player* Player):Component(Owner, Player)
//{
//		
//	
//}

CollisionComponent::~CollisionComponent() {};

void CollisionComponent::Update() 
{
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

	bool HitCheckBLK(D3DXVECTOR2 tempPos, class Block* Block, class Player* Player)
	{
		//　プレイヤの各頂点座標の取得及び代入
		D3DXVECTOR2 P_UpperLeft;
		D3DXVECTOR2 P_UpperRight;
		D3DXVECTOR2 P_BottomLeft;
		D3DXVECTOR2 P_BottomRight;

		P_UpperLeft.x   = tempPos.x - Player->PlayerWidth / 2;
		P_UpperLeft.y   = tempPos.y - Player->PlayerHeight/ 2;

		P_UpperRight.x  = tempPos.x + Player->PlayerWidth/2;
		P_UpperRight.y  = tempPos.y - Player->PlayerHeight/2;

		P_BottomLeft.x  = tempPos.x - Player->PlayerWidth / 2;
		P_BottomLeft.y  = tempPos.y + Player->PlayerHeight / 2;

		P_BottomRight.x = tempPos.x + Player->PlayerWidth/2;
		P_BottomRight.y = tempPos.y + Player->PlayerHeight/2;

		//　ブロックの各頂点座標の取得及び代入
		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;

		B_UpperLeft.x   = Block->GetPos().x - Block->BlockWidth  / 2;
		B_UpperLeft.y   = Block->GetPos().y - Block->BlockHeight / 2;			      

		B_UpperRight.x  = Block->GetPos().x + Block->BlockWidth  / 2;
		B_UpperRight.y  = Block->GetPos().y - Block->BlockHeight / 2;

		B_BottomLeft.x  = Block->GetPos().x - Block->BlockWidth  / 2;
		B_BottomLeft.y  = Block->GetPos().y + Block->BlockHeight / 2;

		B_BottomRight.x = Block->GetPos().x + Block->BlockWidth  / 2;
		B_BottomRight.y = Block->GetPos().y + Block->BlockHeight / 2;


		//着地しているかの判定
		//ブロックの上端のY座標より下にくるか？
		if (P_BottomLeft.y > B_UpperRight.y || P_BottomRight.y > B_UpperLeft.y)
		{
			//ブロックの左上端X座標より右に位置、且つ、ORブロックの右上端X座標より左に位置するか
			if (P_BottomRight.x > B_UpperLeft.x && P_BottomLeft.x < B_UpperRight.x) 
			{
				return true;
			}
			
		}
		////ブロックの下端のY座標より上にくるか？
		//else if (P_UpperLeft.y < B_BottomRight.y || P_UpperRight.y < B_BottomLeft.y)
		//{
		//	//ブロックの左下端X座標より右に位置、且つ、ORブロックの右上端X座標より左に位置するか
		//	if (P_UpperRight.x > B_BottomLeft.x && P_UpperLeft.x < B_BottomRight.x)
		//	{
		//		return true;
		//	}
		//}


		//その他の接触判定





	}
