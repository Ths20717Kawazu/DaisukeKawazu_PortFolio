#pragma once
#include <vector>
//#include "Component.h"

class Actor
{
	public:
		Actor(class Game* game);
		virtual ~Actor();

		//Game�N���X��Public�ɃA�N�Z�X���邽�߂̃|�C���^���擾����	
		void AddComponent(class Component*);

		void ProcessInput(void);

		enum STATE
		{
			EActive, EPause, EDead
		};

		//�摜�̕\���ԍ�
		int  GetTextureID() { return TextureID; }
		void SetTextureID(int tID) { TextureID = tID; }

		//�`�悷�邽�߂ɕK�p�ȏ��̎擾�y�ё��
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

		//Game�N���X�̌��J�����o�ւ̃A�N�Z�X
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
		//Game�N���X��Public�ȃ����o�ւ̃A�N�Z�X�̂��߂̃|�C���^
		class Game* mGame;
		std::vector<class Component*> mComponents;
};

