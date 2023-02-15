#pragma once
#include <vector>
#include "main.h"

class Actor
{
	public:
		Actor(class Game* game);
		//Actor(class Game* game, class Player* player);
		virtual ~Actor();
		//Game�N���X��Public�ɃA�N�Z�X���邽�߂̃|�C���^���擾����	
		void AddComponent(class Component*);
		void ProcessInput(void);
		
		struct ACTOR {
				D3DXVECTOR2 pos;	//���W
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

		//�摜�̕\���ԍ�
		int  GetTextureID() { return TextureID; }
		void SetTextureID(int tID) { TextureID = tID; }
		//�`�悷�邽�߂ɕK�p�ȏ��̎擾�y�ё��
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
		//���I�ɕω�����Pos�Ɋւ���
		void SetPos(float posx, float posy) { mActor.pos.x = posx, mActor.pos.y = posy; }	
		D3DXVECTOR2 GetPos() { return mActor.pos; }
		//Game�N���X�̌��J�����o�ւ̃A�N�Z�X
		class Game* GetGame() { return mGame; }
		class Player* GetPlayer() { return mPlayer;  }
		//Actor���g�̍X�V�@���@�Փ˔���p���@�p����ŋ�̉�����B
		virtual void UpdateActor() {};
		


	private:
		ACTOR mActor;
		int TextureID;
		//Game�N���X��Public�ȃ����o�ւ̃A�N�Z�X�̂��߂̃|�C���^
		class Game* mGame;
		class Player* mPlayer;
		std::vector<class Component*> mComponents;
		//D3DXVECTOR2 pos;

		

};

