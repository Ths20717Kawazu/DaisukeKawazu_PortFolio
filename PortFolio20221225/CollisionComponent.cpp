#include "CollisionComponent.h"


CollisionComponent::CollisionComponent(class Actor* owner) :Component(owner)
{
		
	
}

void CollisionComponent::Update() 
{
	//HitCheckBC(mOwner->GetPositionX(),  )
}


//‹«ŠE‰~iƒoƒEƒ“ƒfƒBƒ“ƒOƒT[ƒNƒ‹j‚Ì“–‚½‚è”»’è
	bool HitCheckBC(D3DXVECTOR2 posA, float rA, D3DXVECTOR2 posB, float rB)
	{
		D3DXVECTOR2 vDist;//2‚Â‚Ì‰~‚Ì‹——£‚ğ•Û‘¶‚·‚é•Ï”
			vDist.x = posB.x - posA.x;
			vDist.y = posB.y - posA.y;

			//‚Q‚Â‚Ì‰~‚ğŒq‚®ƒxƒNƒgƒ‹‚ğì‚é
		    vDist = posB - posA;
		//ì¬‚µ‚½ƒxƒNƒgƒ‹‚Ì‘å‚«‚³i‚Q‚Â‚Ì‰~‚Ì‹——£j‚ğŒvZ‚·‚é
			float length = D3DXVec2Length(&vDist);
		//‚Q‚Â‚Ì‰~‚Ì”¼Œa‚ğ‘«‚µ‚½’l‚ğì‚é
			float r = rA + rB;

		//‹——£‚Æ”¼Œa‚ğ”äŠr‚µA‹——£‚Ì‚Ù‚¤‚ª‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢
		if (length > r)
			return false;
		else
			return true;
	}