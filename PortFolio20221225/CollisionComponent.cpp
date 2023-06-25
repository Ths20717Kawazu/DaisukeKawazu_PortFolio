#include "CollisionComponent.h"
#include "game.h"

CollisionComponent::CollisionComponent(class Actor* Owner) :Component(Owner){mOwner = Owner;}

CollisionComponent::~CollisionComponent() {};

void CollisionComponent::Update() {}

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

	//�ڐG��������N���X�ł���Actor���_�E���L���X�g���Čp����N���X���ɐڐG�����ς��悤�Ǝv���������܂������Ȃ��������߁A
	//������Block�N���X��Actor�N���X�ɕύX�����B����ɔ����ABlock�N���X��BlockWidth��BlockHeight��Actor.h�Ɉڂ����B
	bool HitCheckBLK(D3DXVECTOR2* futurepos, class Actor* Block, class Player* Player)
	{
		//�v���C���̏������W�̑��
		float FP_Bottom;
		float FP_Top;
		float FP_Left;
		float FP_Right;

		FP_Top = futurepos->y - Player->PlayerHeight / 2;
		FP_Bottom = futurepos->y + Player->PlayerHeight / 2;
		//�v���C���̐ڐG���������߁AX�����ւ̖߂�̔�����}������B
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

		

		//�u���b�N�Ə������W���ڐG���Ă���ꍇ
		if (FP_Right > B_Left && FP_Left < B_Right && FP_Bottom > B_Upper && FP_Top < B_Bottom )
		{
			float OverLapX = 0.0f;
			float OverLapY = 0.0f;
			//���K��Y���̌v�Z��X������Ɏ��{���邱�ƁA�����łȂ��ꍇ�A�󒆂ɂ�����̂Ɣ��肵�A�ڒn�����u�ԁAX�����̉����߂����������� 
			// Y�������̂߂荞�ݗʂ��v�Z
			if (FP_Bottom > B_Bottom)//�v���C���̓u���b�N�̉�����ڐG
			{
				OverLapY = FP_Top - B_Bottom;
			}

			if (FP_Top < B_Upper)
			{
				OverLapY = FP_Bottom - B_Upper;
				Player->setIsInAir(false);//�����I�ɐڒn�v�Z��������˂Ă���
				//��
			}

			if (Player->getIsInAir()) 
			{
				//// X�������̂߂荞�ݗʂ��v�Z
				if (FP_Right > B_Right) //�v���C���̓u���b�N�̉E������ڐG
				{
					OverLapX = FP_Left - B_Right;//ϲŽ�l
				}
				else if (FP_Left < B_Left)//�v���C���̓u���b�N�̍�������ڐG
				{
					OverLapX = FP_Right - B_Left;
				}
			}

			// �߂荞�݂����������i�K�̃v���C���̂���ׂ����W
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
		//�v���C���̐ڐG���������߁AX�����ւ̖߂�̔�����}������B
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
				
		if ( P_Bottom > B_Top && P_Top < B_Bottom) //�v���C���̉��ӂƐ��ݓI�ɐڐG���Ă���\������u���b�N
		{
			if (P_Right > B_Left && P_Left < B_Right)//B�̏�ӂ��P�̉��ӂ����ɂ���iY�l��P�̕�����)
			{
					return true;
			}
			else 
			{
				return false;
			}
			//return true;
		}
		//�@�v���C���̊e���_���W�̎擾�y�ё��
		//���ӂƉE�ӂɂ��Ă͑��̕ӂ����������ݒ�i�ڒn�̌v�Z�̎��̂݁j
		//�@�u���b�N�̊e���_���W�̎擾�y�ё��
		//��`B�̂ق�����ɍl���āA�e�ӂŋ��E��������A
		//��`A�̔��Α��̕ӂ����E�����傫�������������𔻒肷��
	}

	int PushBack(Actor* Block, Player* Player)
	{
		//���݂̃v���C���̈ʒu
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
	
		//�@�u���b�N�̊e���_���W�̎擾�y�ё��

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

		//�ڐG����̂̂��A�v���C���̌��݈ʒu�ƃu���b�N�̍����i�߂荞��ł���ʁj�����߉����Ԃ��ʂ�Ԃ��B
		int Y_DIfferenceOne = CP_Bottom - B_Left;
		return Y_DIfferenceOne;


	}



	//=================================================================================
	bool HitCheckBLK2(class Actor* Block, class Player* Player)
	{
		//�@�v���C���̊e���_���W�̎擾�y�ё��

		int P_Left	= Player->GetPos().x - (Player->PlayerWidth / 2);//����
		int P_Right	= Player->GetPos().x + (Player->PlayerWidth / 2);//�E��
		int P_Top   = Player->GetPos().y - (Player->PlayerHeight/ 2);//���
		int P_Bottom  = Player->GetPos().y + (Player->PlayerHeight/ 2);//����

		//�@�u���b�N�̊e���_���W�̎擾�y�ё��
		int B_Left   = Block->GetPos().x - (Block->BlockWidth / 2);//����
		int B_Right  = Block->GetPos().x + (Block->BlockWidth / 2);//�E��
		int B_Top    = Block->GetPos().y - (Block->BlockHeight / 2);//���
		int B_Bottom = Block->GetPos().y + (Block->BlockHeight / 2);//����

		//��`B�̂ق�����ɍl���āA�e�ӂŋ��E��������A
        //��`A�̔��Α��̕ӂ����E�����傫�������������𔻒肷��
		if (B_Left < P_Right)//B�̍��ӂ��P�̉E�ӂ��E�ɂ���
		{
			if (B_Right > P_Left)//B�̉E�ӂ��P�̍��ӂ����ɂ���
			{
				//Player->SetPos(P_Left - 50, Player->GetPos().y);
				if (B_Bottom > P_Top)//B�̉��ӂ��P�̏�ӂ���ɂ���iY�l��P�̕�����)
				{
					//4�ӂ̔��肪�^�ł���΃q�b�g���Ă���
					return true;
				}
			}
		}
		return false;
	}
				//if (B_Top < P_Bottom)//B�̏�ӂ��P�̉��ӂ����ɂ���iY�l��P�̕�����)
				//{
				//}

	//���E���i�o�E���f�B���O�{�b�N�X�j�̓����蔻��
	bool HitCheckBB(D3DXVECTOR2 boxApos, float boxAwidth, float boxAheight,
		D3DXVECTOR2 boxBpos, float boxBwidth, float boxBheight)
	{
		//��`A�̊e�ӂ̍��W�����
		float boxAminX = boxApos.x - (boxAwidth / 2);//����
		float boxAmaxX = boxApos.x + (boxAwidth / 2);//�E��
		float boxAminY = boxApos.y - (boxAheight / 2);//���
		float boxAmaxY = boxApos.y + (boxAheight / 2);//����
		//��`B�̊e�ӂ̍��W�����
		float boxBminX = boxBpos.x - (boxBwidth / 2);//����
		float boxBmaxX = boxBpos.x + (boxBwidth / 2);//�E��
		float boxBminY = boxBpos.y - (boxBheight / 2);//���
		float boxBmaxY = boxBpos.y + (boxBheight / 2);//����

		//��`B�̂ق�����ɍl���āA�e�ӂŋ��E��������A
		//��`A�̔��Α��̕ӂ����E�����傫�������������𔻒肷��
		if (boxBminX < boxAmaxX)
		{
			if (boxBmaxX > boxAminX)
			{
				if (boxBminY < boxAmaxY)
				{
					if (boxBmaxY > boxAminY)
					{
						//4�ӂ̔��肪�^�ł���΃q�b�g���Ă���
						return true;
					}
				}
			}
		}
		//�ǂ����̔���ŋU�ƂȂ�΃q�b�g���Ă��Ȃ�
		return false;
	}


	//Enemy�p�̃u���b�N�Ƃ̏Փ˔���p������������HitcheckBLK�Ɠ��l�̗��R�œ����ӏ���ύX���Ă���B
	bool HitCheckBLK(D3DXVECTOR2 tempPos, class Actor* Block, class Enemy* enemy)
	{
		//�@�v���C���̊e���_���W�̎擾�y�ё��
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

		//�@�u���b�N�̊e���_���W�̎擾�y�ё��
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
		



		////���n���Ă��邩�̔���
		////�u���b�N�̍���[X���W���E�Ɉʒu�A���A�u���b�N�̉E��[X���W��荶�Ɉʒu���邩
		//if (P_BottomRight.x > B_UpperLeft.x && P_BottomLeft.x < B_UpperRight.x ) 
		//{
		//	//�u���b�N�̏�[��Y���W��艺�ɂ��邩�H
		//	if (P_BottomLeft.y >= B_UpperRight.y && P_BottomRight.y >= B_UpperLeft.y) 
		//		//&& P_BottomLeft.y < B_BottomRight.y && P_BottomRight.y < B_BottomLeft.y )
		//	{
		//		return true;
		//	}
		//	
		//}
		////��ɓ��Y�u���b�N�̉��ł��邱�Ƃ𔻒肵�Ȃ��ƁA����łȂ����ɐݒu����鑼�̃u���b�N�̉e�����󂯂Ă��܂��B
		////else if (P_Upper > B_Bottom)
		//else if (P_UpperLeft.x < B_BottomRight.x && P_UpperRight.x > B_BottomLeft.x)
		//{
		//    //Player�̏�[�̂����ꂩ���u���b�N���[���ォ�A�u���b�N��[��艺�ł���B�ꍇ
		//	if (P_UpperLeft.y <= B_BottomRight.y && P_UpperRight.y <= B_BottomLeft.y) 
		//		//|| P_UpperLeft.y > B_UpperRight.y && P_UpperRight.y > B_UpperLeft.y)
		//	{
		//		return true;
		//	}
		//     //�u���b�N�̉��[���v���C���̏�[����ł���

		//}

		////Player�̏�[���u���b�N�̏�[���牺�[�̊ԂɈʒu����A�������́APlayer�̉��[���u���b�N�̉��[�����[�̊ԂɈʒu����
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
		//	//�v���C���̉E�[���u���b�N�̍��[���E�ɂ���
		//	if (P_UpperRight.x > B_UpperLeft.x && P_BottomRight.x > B_BottomLeft.x)
		//	{
		//		return true;
		//	}
		//	//�v���C���̍��[���u���b�N�̉E�[��荶�ɂ���
		//	else if (P_UpperLeft.x < B_UpperRight.x && P_BottomLeft.x < B_BottomRight.x)
		//	{
		//		return true;
		//	}