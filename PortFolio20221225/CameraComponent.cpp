#pragma once

#include "CameraComponent.h"


CameraComponent::CameraComponent(class Actor* Owner): Component(Owner)
{
	mCameraOwner = Owner;
}


