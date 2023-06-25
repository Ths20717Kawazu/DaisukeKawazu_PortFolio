#include "CollisionComponent.h"
#include "game.h"

CollisionComponent::CollisionComponent(class Actor* Owner) :Component(Owner){mOwner = Owner;}

CollisionComponent::~CollisionComponent() {};

void CollisionComponent::Update() {}

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
	bool HitCheckBLK(D3DXVECTOR2* futurepos, class Actor* Block, class Player* Player)
	{
		//プレイヤの将来座標の代入
		float FP_Bottom;
		float FP_Top;
		float FP_Left;
		float FP_Right;

		FP_Top = futurepos->y - Player->PlayerHeight / 2;
		FP_Bottom = futurepos->y + Player->PlayerHeight / 2;
		//プレイヤの接触部分を狭め、X方向への戻りの発生を抑制する。
		FP_Left = futurepos->x - Player->PlayerWidth / 4;
		FP_Right = futurepos->x + Player->PlayerWidth / 4;
		
		float B_Upper;
		float B_Bottom;
		float B_Right;
		float B_Left;

		B_Upper = Block->GetPos().y - Block->BlockHeight / 2;
		B_Bottom = Block->GetPos().y + Block->BlockHeight / 2;
		B_Right = Block->GetPos().x + Block->BlockWidth / 2;
		B_Left = Block->GetPos().x - Block->BlockWidth / 2;

		

		//ブロックと将来座標が接触している場合
		if (FP_Right > B_Left && FP_Left < B_Right && FP_Bottom > B_Upper && FP_Top < B_Bottom )
		{
			float OverLapX = 0.0f;
			float OverLapY = 0.0f;
			//※必ずY軸の計算をXよりも先に実施すること、そうでない場合、空中にいるものと判定し、接地した瞬間、X方向の押し戻しが発生する 
			// Y軸方向のめり込み量を計算
			if (FP_Bottom > B_Bottom)//プレイヤはブロックの下から接触
			{
				OverLapY = FP_Top - B_Bottom;
			}

			if (FP_Top < B_Upper)
			{
				OverLapY = FP_Bottom - B_Upper;
				Player->setIsInAir(false);//実質的に接地計算判定も兼ねている
				//※
			}

			if (Player->getIsInAir()) 
			{
				//// X軸方向のめり込み量を計算
				if (FP_Right > B_Right) //プレイヤはブロックの右側から接触
				{
					OverLapX = FP_Left - B_Right;//ﾏｲﾅｽ値
				}
				else if (FP_Left < B_Left)//プレイヤはブロックの左側から接触
				{
					OverLapX = FP_Right - B_Left;
				}
			}

			// めり込みを解消した段階のプレイヤのあるべき座標
			futurepos->x -= OverLapX;
			futurepos->y -= OverLapY;

			return true;
		}
		return false;
		
	}

	bool HitGroundCheck(class Actor* Block, class Player* Player)
	{
		float P_Bottom;
		float P_Top;
		float P_Left;
		float P_Right;

		P_Top = Player->GetPos().y - Player->PlayerHeight / 2;
		P_Bottom = Player->GetPos().y + Player->PlayerHeight / 2;
		//プレイヤの接触部分を狭め、X方向への戻りの発生を抑制する。
		P_Left = Player->GetPos().x - Player->PlayerWidth / 4;
		P_Right = Player->GetPos().x + Player->PlayerWidth / 4;
		
		float B_Top;
		float B_Bottom;
		float B_Right;
		float B_Left;

		B_Top = Block->GetPos().y - Block->BlockHeight / 2;
		B_Bottom = Block->GetPos().y + Block->BlockHeight / 2;
		B_Right = Block->GetPos().x + Block->BlockWidth / 2;
		B_Left = Block->GetPos().x - Block->BlockWidth / 2;
				
		if ( P_Bottom > B_Top && P_Top < B_Bottom) //プレイヤの下辺と潜在的に接触している可能性あるブロック
		{
			if (P_Right > B_Left && P_Left < B_Right)//Bの上辺よりPの下辺が下にある（Y値はPの方が上)
			{
					return true;
			}
			else 
			{
				return false;
			}
			//return true;
		}
		//　プレイヤの各頂点座標の取得及び代入
		//左辺と右辺については他の辺よりも小さく設定（接地の計算の時のみ）
		//　ブロックの各頂点座標の取得及び代入
		//矩形Bのほうを基準に考えて、各辺で境界線をつくり、
		//矩形Aの反対側の辺が境界線より大きいか小さいかを判定する
	}

	int PushBack(Actor* Block, Player* Player)
	{
		//現在のプレイヤの位置
		D3DXVECTOR2 CP_UpperLeft;
		D3DXVECTOR2 CP_UpperRight;
		D3DXVECTOR2 CP_BottomLeft;
		D3DXVECTOR2 CP_BottomRight;

		int CP_Bottom;
		int CP_Upper;
		int CP_Left;
		int CP_Right;

		CP_Upper = Player->GetPos().y - Player->PlayerHeight / 2;
		CP_Bottom = Player->GetPos().y + Player->PlayerHeight / 2;
		CP_Left = Player->GetPos().x - Player->PlayerWidth / 2;
		CP_Right = Player->GetPos().x + Player->PlayerWidth / 2;
	
		//　ブロックの各頂点座標の取得及び代入

		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;
		int B_Upper;
		int B_Bottom;
		int B_Right;
		int B_Left;

		B_Upper = Block->GetPos().y - Block->BlockHeight / 2;
		B_Bottom = Block->GetPos().y + Block->BlockHeight / 2;
		B_Right = Block->GetPos().x + Block->BlockWidth / 2;
		B_Left = Block->GetPos().x - Block->BlockWidth / 2;

		//接触判定ののち、プレイヤの現在位置とブロックの差分（めり込んでいる量）を求め押し返す量を返す。
		int Y_DIfferenceOne = CP_Bottom - B_Left;
		return Y_DIfferenceOne;


	}



	//=================================================================================
	bool HitCheckBLK2(class Actor* Block, class Player* Player)
	{
		//　プレイヤの各頂点座標の取得及び代入

		int P_Left	= Player->GetPos().x - (Player->PlayerWidth / 2);//左辺
		int P_Right	= Player->GetPos().x + (Player->PlayerWidth / 2);//右辺
		int P_Top   = Player->GetPos().y - (Player->PlayerHeight/ 2);//上辺
		int P_Bottom  = Player->GetPos().y + (Player->PlayerHeight/ 2);//下辺

		//　ブロックの各頂点座標の取得及び代入
		int B_Left   = Block->GetPos().x - (Block->BlockWidth / 2);//左辺
		int B_Right  = Block->GetPos().x + (Block->BlockWidth / 2);//右辺
		int B_Top    = Block->GetPos().y - (Block->BlockHeight / 2);//上辺
		int B_Bottom = Block->GetPos().y + (Block->BlockHeight / 2);//下辺

		//矩形Bのほうを基準に考えて、各辺で境界線をつくり、
        //矩形Aの反対側の辺が境界線より大きいか小さいかを判定する
		if (B_Left < P_Right)//Bの左辺よりPの右辺が右にある
		{
			if (B_Right > P_Left)//Bの右辺よりPの左辺が左にある
			{
				//Player->SetPos(P_Left - 50, Player->GetPos().y);
				if (B_Bottom > P_Top)//Bの下辺よりPの上辺が上にある（Y値はPの方が下)
				{
					//4辺の判定が真であればヒットしている
					return true;
				}
			}
		}
		return false;
	}
				//if (B_Top < P_Bottom)//Bの上辺よりPの下辺が下にある（Y値はPの方が上)
				//{
				//}

	//境界箱（バウンディングボックス）の当たり判定
	bool HitCheckBB(D3DXVECTOR2 boxApos, float boxAwidth, float boxAheight,
		D3DXVECTOR2 boxBpos, float boxBwidth, float boxBheight)
	{
		//矩形Aの各辺の座標を作る
		float boxAminX = boxApos.x - (boxAwidth / 2);//左辺
		float boxAmaxX = boxApos.x + (boxAwidth / 2);//右辺
		float boxAminY = boxApos.y - (boxAheight / 2);//上辺
		float boxAmaxY = boxApos.y + (boxAheight / 2);//下辺
		//矩形Bの各辺の座標を作る
		float boxBminX = boxBpos.x - (boxBwidth / 2);//左辺
		float boxBmaxX = boxBpos.x + (boxBwidth / 2);//右辺
		float boxBminY = boxBpos.y - (boxBheight / 2);//上辺
		float boxBmaxY = boxBpos.y + (boxBheight / 2);//下辺

		//矩形Bのほうを基準に考えて、各辺で境界線をつくり、
		//矩形Aの反対側の辺が境界線より大きいか小さいかを判定する
		if (boxBminX < boxAmaxX)
		{
			if (boxBmaxX > boxAminX)
			{
				if (boxBminY < boxAmaxY)
				{
					if (boxBmaxY > boxAminY)
					{
						//4辺の判定が真であればヒットしている
						return true;
					}
				}
			}
		}
		//どこかの判定で偽となればヒットしていない
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
		D3DXVECTOR2 B_Center;


		B_UpperLeft.x = Block->GetPos().x - Block->BlockWidth / 2;
		B_UpperLeft.y = Block->GetPos().y - Block->BlockHeight / 2;

		B_UpperRight.x = Block->GetPos().x + Block->BlockWidth / 2;
		B_UpperRight.y = Block->GetPos().y - Block->BlockHeight / 2;

		B_BottomLeft.x = Block->GetPos().x - Block->BlockWidth / 2;
		B_BottomLeft.y = Block->GetPos().y + Block->BlockHeight / 2;

		B_BottomRight.x = Block->GetPos().x + Block->BlockWidth / 2;
		B_BottomRight.y = Block->GetPos().y + Block->BlockHeight / 2;


		B_Center.x = Block->GetPos().x;
		B_Center.y = Block->GetPos().y;

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