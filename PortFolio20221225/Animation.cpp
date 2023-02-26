#include "Animation.h"



Animation::Animation() 
{

}


void Animation::AddImage(int img) {

	mImages.emplace_back(img);
}

void Animation::Update() {
	mTimer +=  Game()->delta;



}