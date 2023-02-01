#pragma once
#include "Actor.h"
#include "Player.h"
#include "Component.h"


class MoveComponent :
    public Component
{
public: 	
    MoveComponent(class Actor* mOwner);
    //virtual void ProcessInput(void);←コメントアウトしないと
    /*重大度レベル	コード	説明	プロジェクト	ファイル	行	抑制状態
    エラー	LNK2001	外部シンボル "public: virtual void __cdecl MoveComponent::ProcessInput(void)" (? ProcessInput@MoveComponent@@UEAAXXZ) は未解決です	PortFolio20221225	C : \Users\akaho\source\repos\PortFolio1225\PortFolio20221225\MoveComponent.obj	1*/
    //重大度レベル	コード	説明	プロジェクト	ファイル	行	抑制状態
    //エラー	LNK1120	1 件の未解決の外部参照	PortFolio20221225	C : \Users\akaho\source\repos\PortFolio1225\x64\Debug\PortFolio20221225.exe	1

   // virtual void ProcessInput(void);

private:
    

};

