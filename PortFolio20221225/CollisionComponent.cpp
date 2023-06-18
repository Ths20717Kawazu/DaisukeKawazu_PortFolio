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

	//接触判定を基底クラスであるActorをダウンキャストして継承先クラス毎に接触判定を変えようと思ったがうまくいかなかったため、
	//引数のBlockクラスをActorクラスに変更した。それに伴い、BlockクラスのBlockWidthとBlockHeightはActor.hに移した。
	bool HitCheckBLK(D3DXVECTOR2 tempPos, class Actor* Block, class Player* Player)
	{
		//　プレイヤの各頂点座標の取得及び代入
		D3DXVECTOR2 P_UpperLeft;
		D3DXVECTOR2 P_UpperRight;
		D3DXVECTOR2 P_BottomLeft;
		D3DXVECTOR2 P_BottomRight;
		float P_Bottom;
		float P_Upper;
		float P_Left;
		float P_Right;

		P_Upper = tempPos.y - Player->PlayerHeight / 2;
		P_Bottom = tempPos.y + Player->PlayerHeight / 2;
		P_Left = tempPos.x - Player->PlayerWidth / 2;
		P_Right = tempPos.x + Player->PlayerWidth / 2;


		//　ブロックの各頂点座標の取得及び代入

		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;
		float B_Upper;
		float B_Bottom;
		float B_Right;
		float B_Left;

		B_Upper = Block->GetPos().y - Block->BlockHeight / 2;
		B_Bottom = Block->GetPos().y + Block->BlockHeight / 2;
		B_Right = Block->GetPos().x + Block->BlockWidth / 2;
		B_Left = Block->GetPos().x - Block->BlockWidth / 2;


		if (P_Right > B_Left && P_Left < B_Right && P_Bottom > B_Upper && P_Upper < B_Bottom )
		{
			return true;
		}
		return false;

	}


	bool HitGroundCheck(D3DXVECTOR2 tempPos, class Actor* Block, class Player* Player)
	{
		//　プレイヤの各頂点座標の取得及び代入
		D3DXVECTOR2 P_UpperLeft;
		D3DXVECTOR2 P_UpperRight;
		D3DXVECTOR2 P_BottomLeft;
		D3DXVECTOR2 P_BottomRight;
		float P_Bottom;
		float P_Upper;
		float P_Left;
		float P_Right;

		P_Upper = tempPos.y - Player->PlayerHeight / 2;
		P_Bottom = tempPos.y + Player->PlayerHeight / 2;
		P_Left = tempPos.x - Player->PlayerWidth / 2;
		P_Right = tempPos.x + Player->PlayerWidth / 2;


		//　ブロックの各頂点座標の取得及び代入

		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;
		float B_Upper;
		float B_Bottom;
		float B_Right;
		float B_Left;

		B_Upper = Block->GetPos().y - Block->BlockHeight / 2;
		B_Bottom = Block->GetPos().y + Block->BlockHeight / 2;
		B_Right = Block->GetPos().x + Block->BlockWidth / 2;
		B_Left = Block->GetPos().x - Block->BlockWidth / 2;
		
		if ( P_Bottom > B_Upper && P_Upper < B_Bottom)
		{
			return true;
		}
		return false;
	}

	//Enemy用のブロックとの衝突判定用※こちらも上のHitcheckBLKと同様の理由で同じ箇所を変更している。
	bool HitCheckBLK(D3DXVECTOR2 tempPos, class Actor* Block, class Enemy* enemy)
	{
		//　プレイヤの各頂点座標の取得及び代入
		D3DXVECTOR2 P_UpperLeft;
		D3DXVECTOR2 P_UpperRight;
		D3DXVECTOR2 P_BottomLeft;
		D3DXVECTOR2 P_BottomRight;

		P_UpperLeft.x = tempPos.x - enemy->getWidth() / 2;
		P_UpperLeft.y = tempPos.y - enemy->getHeight() / 2;

		P_UpperRight.x = tempPos.x + enemy->getWidth() / 2;
		P_UpperRight.y = tempPos.y - enemy->getHeight() / 2;

		P_BottomLeft.x = tempPos.x - enemy->getWidth() / 2;
		P_BottomLeft.y = tempPos.y + enemy->getHeight() / 2;

		P_BottomRight.x = tempPos.x + enemy->getWidth() / 2;
		P_BottomRight.y = tempPos.y + enemy->getHeight() / 2;

		//　ブロックの各頂点座標の取得及び代入
		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;

		B_UpperLeft.x = Block->GetPos().x - Block->BlockWidth / 2;
		B_UpperLeft.y = Block->GetPos().y - Block->BlockHeight / 2;

		B_UpperRight.x = Block->GetPos().x + Block->BlockWidth / 2;
		B_UpperRight.y = Block->GetPos().y - Block->BlockHeight / 2;

		B_BottomLeft.x = Block->GetPos().x - Block->BlockWidth / 2;
		B_BottomLeft.y = Block->GetPos().y + Block->BlockHeight / 2;

		B_BottomRight.x = Block->GetPos().x + Block->BlockWidth / 2;
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






		/*P_UpperLeft.x   = tempPos.x - Player->PlayerWidth / 2;
		P_UpperLeft.y   = tempPos.y - Player->PlayerHeight/ 2;

		P_UpperRight.x  = tempPos.x + Player->PlayerWidth/2;
		P_UpperRight.y  = tempPos.y - Player->PlayerHeight/2;

		P_BottomLeft.x  = tempPos.x - Player->PlayerWidth / 2;
		P_BottomLeft.y  = tempPos.y + Player->PlayerHeight / 2;

		P_BottomRight.x = tempPos.x + Player->PlayerWidth/2;
		P_BottomRight.y = tempPos.y + Player->PlayerHeight/2;*/

		//B_UpperLeft.x   = Block->GetPos().x - Block->BlockWidth  / 2;
		//B_UpperLeft.y   = Block->GetPos().y - Block->BlockHeight / 2;			      

		//B_UpperRight.x  = Block->GetPos().x + Block->BlockWidth  / 2;
		//B_UpperRight.y  = Block->GetPos().y - Block->BlockHeight / 2;

		//B_BottomLeft.x  = Block->GetPos().x - Block->BlockWidth  / 2;
		//B_BottomLeft.y  = Block->GetPos().y + Block->BlockHeight / 2;

		//B_BottomRight.x = Block->GetPos().x + Block->BlockWidth  / 2;
		//B_BottomRight.y = Block->GetPos().y + Block->BlockHeight / 2;
		



		////着地しているかの判定
		////ブロックの左上端X座標より右に位置、且つ、ブロックの右上端X座標より左に位置するか
		//if (P_BottomRight.x > B_UpperLeft.x && P_BottomLeft.x < B_UpperRight.x ) 
		//{
		//	//ブロックの上端のY座標より下にくるか？
		//	if (P_BottomLeft.y >= B_UpperRight.y && P_BottomRight.y >= B_UpperLeft.y) 
		//		//&& P_BottomLeft.y < B_BottomRight.y && P_BottomRight.y < B_BottomLeft.y )
		//	{
		//		return true;
		//	}
		//	
		//}
		////先に当該ブロックの下であることを判定しないと、直上でない横に設置される他のブロックの影響を受けてしまう。
		////else if (P_Upper > B_Bottom)
		//else if (P_UpperLeft.x < B_BottomRight.x && P_UpperRight.x > B_BottomLeft.x)
		//{
		//    //Playerの上端のいずれかがブロック下端より上かつ、ブロック上端より下である。場合
		//	if (P_UpperLeft.y <= B_BottomRight.y && P_UpperRight.y <= B_BottomLeft.y) 
		//		//|| P_UpperLeft.y > B_UpperRight.y && P_UpperRight.y > B_UpperLeft.y)
		//	{
		//		return true;
		//	}
		//     //ブロックの下端よりプレイヤの上端が上である

		//}

		////Playerの上端がブロックの上端から下端の間に位置する、もしくは、Playerの下端がブロックの下端から上端の間に位置する
		//
		//else if (P_UpperRight.x > B_UpperLeft.x && P_BottomRight.x > B_BottomLeft.x)
		//{
		//	if (P_Upper >= B_Upper && P_Upper <= B_Bottom || P_Bottom >= B_Upper && P_Bottom <= B_Bottom) 
		//		(P_UpperLeft.y <= B_BottomRight.y && P_UpperRight.y <= B_BottomLeft.y || P_UpperLeft.y > B_UpperRight.y && P_UpperRight.y > B_UpperLeft.y)
		//		{
		//			return true;

		//		}
		//}
		
		//else if (P_Upper >= B_Upper && P_Upper <= B_Bottom || P_Bottom >= B_Upper && P_Bottom <= B_Bottom)
		//	//|| P_UpperLeft.y > B_UpperRight.y && P_UpperRight.y > B_UpperLeft.y)
		//{
		//	//プレイヤの右端がブロックの左端より右にある
		//	if (P_UpperRight.x > B_UpperLeft.x && P_BottomRight.x > B_BottomLeft.x)
		//	{
		//		return true;
		//	}
		//	//プレイヤの左端がブロックの右端より左にある
		//	else if (P_UpperLeft.x < B_UpperRight.x && P_BottomLeft.x < B_BottomRight.x)
		//	{
		//		return true;
		//	}