#pragma once
#include <vector>
#include "main.h"


//**********************************//
//�^�OID
//�v���C���[�@�F�P
//���D�F�P�O�O�ԑ�
//�G�F�P�O�O�O�ԑ�
//�u���b�N�F�P�O�O�O�O�ԑ�
//*********************************//


class Actor
{
	public:
		struct ACTOR
		{
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
		enum Tag 
		{
			Player,
			Enemy,
			Block,
			Balloon,
			Obstacle
		};

		Actor(class Game* game, enum Tag tag);
		virtual ~Actor();
		virtual void Damage(int damage) {};
		virtual void UpdateActor() {};
		virtual void AddImage() {};


		void AddComponent(class Component*);
		void ProcessInput(void);
		
		void SetTag(enum Tag tag) { mTag = tag; }
		enum Tag GetTag() { return mTag; }

		void SetState(enum STATE state) { mState = state; }
		enum STATE GetState() { return mState; }

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

		//virtual std::vector<int> GetAnimImages() {};

		std::vector<int> GetActorAnimImages() { return AnimImages; }
		std::vector<int> GetActorAnimOrders(){ return AnimOrders; }

		bool getAnimate() { return animate;  }

	private:
		ACTOR mActor;

		int TextureID;
		//Game�N���X��Public�ȃ����o�ւ̃A�N�Z�X�̂��߂̃|�C���^
		class Game* mGame;
		class Player* mPlayer;
		std::vector<class Component*> mComponents;
		
protected:
		enum Tag mTag;
		enum STATE mState;
		float mGravity = 2.0f;
		int mHP;
		bool animate;
		D3DXVECTOR2 mPos;

		std::vector<int>AnimImages;//�e�h���N���X���ʂ̉摜�ˊe�N���X��State���؂�ւ��x�ɂ��̔z��ɓ��͂����B
		std::vector<int>AnimOrders;//�e�h���N���X���ʂ̕\�������ˊe�N���X��State���؂�ւ��x�ɂ��̔z��ɓ��͂����B
};

