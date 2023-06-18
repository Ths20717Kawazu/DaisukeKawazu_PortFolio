#include "game.h"
#include "Grid.h"

void Grid::addMembersIngrid(class Actor* actor) 
{
	mGridMembers.emplace_back(actor);

};

void Grid::removeMembersIngrid(class Actor* actor)
{
	auto iter = std::find(mGridMembers.begin(), mGridMembers.end(), actor);
	if (iter != mGridMembers.end())
	{
		//����Actor�ƃP�c��Actor�����ւ���(������R�s�[����������邽��)
		std::iter_swap(iter, mGridMembers.end() - 1);
		mGridMembers.pop_back();
	}
};