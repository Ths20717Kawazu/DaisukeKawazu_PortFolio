#pragma once


class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();

protected:
	class Actor* mOwner;

};

