#pragma once
#include <vector>
//#include "Component.h"

class Actor
{
	public:
		Actor(class Game* game);
		virtual ~Actor();

		//GameクラスのPublicにアクセスするためのポインタを取得する	
		void AddComponent(class Component*);

		void ProcessInput(void);

		enum STATE
		{
			EActive, EPause, EDead
		};

		//画像の表示番号
		int  GetTextureID() { return TextureID; }
		void SetTextureID(int tID) { TextureID = tID; }

		//描画するために必用な情報の取得及び代入
		float GetPositionX() { return mPositionX; }
		void SetPositionX(float positionX) { mPositionX = positionX; }
		
		float GetPositionY() { return mPositionY; }
		void SetPositionY(float positionY) { mPositionY = positionY; }

		float GetBoxWidth() { return mBoxWidth; }
		void SetBoxWidth(float boxwidth) { mBoxWidth = boxwidth; }

		float GetBoxHeight() { return mBoxHeight; }
		void SetBoxHeight(float boxheight) { mBoxHeight = boxheight; }
		
		float GetUvpositonU() { return mUvpositonU; }
		void SetUvpositonU(float uvpositionU) { mUvpositonU = uvpositionU; }

		float GetUvpositonV() { return mUvpositonV; }
		void SetUvpositonV(float uvpositionV) { mUvpositonV = uvpositionV; }

		float GetUWidth() { return mUWidth; }
		void SetUWidth(float uwidth) { mUWidth = uwidth; }

		float GetVHeight() { return mVHeight; }
		void SetVHeight(float vheight) { mVHeight = vheight; }

		float GetRotation() { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; }

		//Gameクラスの公開メンバへのアクセス
		class Game* GetGame() { return mGame; }
	private:
		float mPositionX;
		float mPositionY;
		float mBoxWidth;
		float mBoxHeight;
		float mUvpositonU;
		float mUvpositonV;
		float mUWidth;
		float mVHeight;
		float mRotation;

		int TextureID;
		//GameクラスのPublicなメンバへのアクセスのためのポインタ
		class Game* mGame;
		std::vector<class Component*> mComponents;
};

