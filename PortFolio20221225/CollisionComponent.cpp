#include "CollisionComponent.h"
#include "game.h"

CollisionComponent::CollisionComponent(class Actor* Owner) :Component(Owner)
{


}


CollisionComponent::CollisionComponent(class Actor* Owner, class Player* Player):Component(Owner, Player)
{
		
	
}

void CollisionComponent::Update() 
{

	//�S�Ă�Actor���Ăяo���āA��������ł���悤�ɕύX

	//for(auto actor : )
	//HitCheckBC(mOwner->GetACTOR().pos, 50, m )
}


//���E�~�i�o�E���f�B���O�T�[�N���j�̓����蔻��
	bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
	{
		D3DXVECTOR2 vDist;//2�̉~�̋�����ۑ�����ϐ�
			vDist.x = posB.x - posA.x;
			vDist.y = posB.y - posA.y;

			//�Q�̉~���q���x�N�g�������
		    vDist = posB - posA;
		//�쐬�����x�N�g���̑傫���i�Q�̉~�̋����j���v�Z����
			float length = D3DXVec2Length(&vDist);
		//�Q�̉~�̔��a�𑫂����l�����
			float r = rA + rB;

		//�����Ɣ��a���r���A�����̂ق����傫����Γ������Ă��Ȃ�
		if (length > r)
			return false;
		else
			return true;
	}

//�ړ���̏�Q���A���Ƃ̏Փ˔���@���@�Փ˔���𑍓����肷�镉�ׂ�ጸ���邽�߂ɕʂŗp�ӂ���B
//InputComponent �ł̎g�p��z�肷��B
	//bool CheckObstacles(D3DXVECTOR2 posA);