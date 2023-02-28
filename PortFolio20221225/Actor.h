#pragma once
#include <vector>
#include "main.h"


//**********************************//
//タグID
//プレイヤー　：１
//風船：１００番台
//敵：１０００番台
//ブロック：１００００番台
//*********************************//


class Actor
{
	public:
		Actor(class Game* game, int tagID);
		virtual ~Actor();
		virtual void Damage(int damage) {};
		virtual void UpdateActor() {};
			
		void AddComponent(class Component*);
		void ProcessInput(void);
		
		struct ACTOR {
				D3DXVECTOR2 pos;	//座標
				float height;
				float width;
				float mBoxHeight;
				float mBoxWidth;
				float mUvpositionU;
				float mUvpositionV;
				float mVHeight;
				float mUWidth;
				float mRotation;
		};
		enum STATE
		{
			EActive,
			EPause, 
			EDead
		};
		void SetState(enum STATE state) { mState = state; }
		enum STATE GetState() { return mState; }
		//画像の表示番号
		int  GetTextureID() { return TextureID; }
		void SetTextureID(int tID) { TextureID = tID; }
		//描画するために必用な情報の取得及び代入
		ACTOR GetACTOR() { return mActor; }
		void SetACTOR(float posx, float posy, float BoxH, float BoxW, float UvU, float UvV, float VH, float VW, float Rot) 
		{
			mActor.pos.x = posx, 
			mActor.pos.y = posy, 
			mActor.mBoxHeight = BoxH,
			mActor.mBoxWidth = BoxW,
			mActor.mUvpositionU = UvU,
			mActor.mUvpositionV = UvV,
			mActor.mVHeight = VH,
			mActor.mUWidth = VW,
			mActor.mRotation = Rot; 
		}
		//動的に変化するPosに関して
		void SetPos(float posx, float posy) { mActor.pos.x = posx, mActor.pos.y = posy; }	
		D3DXVECTOR2 GetPos() { return mActor.pos; }
		//Gameクラスの公開メンバへのアクセス
		class Game* GetGame() { return mGame; }
		class Player* GetPlayer() { return mPlayer;  }
		//Actor自身の更新　→　衝突判定用他　継承先で具体化する。
		

		void SetTag(int tag) { mTagID = tag; }
		int GetTag() { return mTagID; }

	private:
		ACTOR mActor;

		enum STATE mState;
		int TextureID;
		//GameクラスのPublicなメンバへのアクセスのためのポインタ
		class Game* mGame;
		class Player* mPlayer;
		std::vector<class Component*> mComponents;
		
protected:
		float mGravity = 2.0f;
		int mHP;
		int mTagID;
		D3DXVECTOR2 mPos;
		

};

