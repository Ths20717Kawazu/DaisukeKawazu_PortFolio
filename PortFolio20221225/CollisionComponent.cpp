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

	bool HitCheckBLK(D3DXVECTOR2 tempPos, class Block* Block, class Player* Player)
	{
		//�@�v���C���̊e���_���W�̎擾�y�ё��
		D3DXVECTOR2 P_UpperLeft;
		D3DXVECTOR2 P_UpperRight;
		D3DXVECTOR2 P_BottomLeft;
		D3DXVECTOR2 P_BottomRight;

		P_UpperLeft.x   = tempPos.x - Player->PlayerWidth / 2;
		P_UpperLeft.y   = tempPos.y - Player->PlayerHeight/ 2;

		P_UpperRight.x  = tempPos.x + Player->PlayerWidth/2;
		P_UpperRight.y  = tempPos.y - Player->PlayerHeight/2;

		P_BottomLeft.x  = tempPos.x - Player->PlayerWidth / 2;
		P_BottomLeft.y  = tempPos.y + Player->PlayerHeight / 2;

		P_BottomRight.x = tempPos.x + Player->PlayerWidth/2;
		P_BottomRight.y = tempPos.y + Player->PlayerHeight/2;

		//�@�u���b�N�̊e���_���W�̎擾�y�ё��
		D3DXVECTOR2 B_UpperLeft;
		D3DXVECTOR2 B_UpperRight;
		D3DXVECTOR2 B_BottomLeft;
		D3DXVECTOR2 B_BottomRight;

		B_UpperLeft.x   = Block->GetPos().x - Block->BlockWidth  / 2;
		B_UpperLeft.y   = Block->GetPos().y - Block->BlockHeight / 2;			      

		B_UpperRight.x  = Block->GetPos().x + Block->BlockWidth  / 2;
		B_UpperRight.y  = Block->GetPos().y - Block->BlockHeight / 2;

		B_BottomLeft.x  = Block->GetPos().x - Block->BlockWidth  / 2;
		B_BottomLeft.y  = Block->GetPos().y + Block->BlockHeight / 2;

		B_BottomRight.x = Block->GetPos().x + Block->BlockWidth  / 2;
		B_BottomRight.y = Block->GetPos().y + Block->BlockHeight / 2;


		//���n���Ă��邩�̔���
		//�u���b�N�̏�[��Y���W��艺�ɂ��邩�H
		if (P_BottomLeft.y > B_UpperRight.y || P_BottomRight.y > B_UpperLeft.y)
		{
			//�u���b�N�̍���[X���W���E�Ɉʒu�A���AOR�u���b�N�̉E��[X���W��荶�Ɉʒu���邩
			if (P_BottomRight.x > B_UpperLeft.x && P_BottomLeft.x < B_UpperRight.x) 
			{
				return true;
			}
			
		}
		////�u���b�N�̉��[��Y���W����ɂ��邩�H
		//else if (P_UpperLeft.y < B_BottomRight.y || P_UpperRight.y < B_BottomLeft.y)
		//{
		//	//�u���b�N�̍����[X���W���E�Ɉʒu�A���AOR�u���b�N�̉E��[X���W��荶�Ɉʒu���邩
		//	if (P_UpperRight.x > B_BottomLeft.x && P_UpperLeft.x < B_BottomRight.x)
		//	{
		//		return true;
		//	}
		//}


		//���̑��̐ڐG����





	}
