#include "CollisionComponent.h"


CollisionComponent::CollisionComponent(class Actor* owner) :Component(owner)
{
		
	
}

void CollisionComponent::Update() 
{
	//HitCheckBC(mOwner->GetPositionX(),  )
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