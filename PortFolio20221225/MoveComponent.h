#pragma once
#include "Actor.h"
#include "Player.h"
#include "Component.h"


class MoveComponent :
    public Component
{
public: 	
    MoveComponent(class Actor* mOwner);
    //virtual void ProcessInput(void);���R�����g�A�E�g���Ȃ���
    /*�d��x���x��	�R�[�h	����	�v���W�F�N�g	�t�@�C��	�s	�}�����
    �G���[	LNK2001	�O���V���{�� "public: virtual void __cdecl MoveComponent::ProcessInput(void)" (? ProcessInput@MoveComponent@@UEAAXXZ) �͖������ł�	PortFolio20221225	C : \Users\akaho\source\repos\PortFolio1225\PortFolio20221225\MoveComponent.obj	1*/
    //�d��x���x��	�R�[�h	����	�v���W�F�N�g	�t�@�C��	�s	�}�����
    //�G���[	LNK1120	1 ���̖������̊O���Q��	PortFolio20221225	C : \Users\akaho\source\repos\PortFolio1225\x64\Debug\PortFolio20221225.exe	1

   // virtual void ProcessInput(void);

private:
    

};

