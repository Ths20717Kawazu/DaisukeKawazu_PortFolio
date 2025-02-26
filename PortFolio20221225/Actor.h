#pragma once
#include <vector>
#include "main.h"
#include "Grid.h"

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
		struct ACTOR
		{
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
		enum Tag 
		{
			Player,
			Enemy,
			Block,
			Balloon,
			Mono,
			Background,
			UI,
			OPENING,
			ENDING
		};

		Actor(class Game* game, enum Tag tag);
		virtual ~Actor();//継承先のデストラクタを機能させるためにVirtualは忘れないこと

		virtual void Damage(int damage) {};
		virtual void UpdateActor() {};
		virtual void AddImage() {};


		void AddComponent(class Component*);
		void RemoveComponent(Component*);
		void ProcessInput(void);
		
		void SetTag(enum Tag tag) { mTag = tag; }
		enum Tag GetTag() { return mTag; }

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

		//virtual std::vector<int> GetAnimImages() {};

		std::vector<int> GetActorAnimImages() { return AnimImages; }
		std::vector<int> GetActorAnimOrders(){ return AnimOrders; }

		bool getAnimate() { return animate;  }
		float BlockWidth = 100.0f;
		float BlockHeight = 100.0f;

		void setLift(float lift) { M_mlift = lift; }

	private:

		int TextureID;
		//GameクラスのPublicなメンバへのアクセスのためのポインタ
		class Player* mPlayer;
		
protected:
		class Game* mGame;
		ACTOR mActor;
		std::vector<class Component*> mComponents;
		enum Tag mTag;
		enum STATE mState;
		float mGravity = 1.0f;
		int mHP;
		Grid* mMygrid;
		bool animate;
		D3DXVECTOR2 mPos;
		float M_mlift = 0.0f;


		std::vector<int>AnimImages;//各派生クラス共通の画像⇒各クラスのStateが切り替わる度にこの配列に入力される。
		std::vector<int>AnimOrders;//各派生クラス共通の表示順序⇒各クラスのStateが切り替わる度にこの配列に入力される。
};

