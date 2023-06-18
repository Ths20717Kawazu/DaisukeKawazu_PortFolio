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
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mGridMembers.end() - 1);
		mGridMembers.pop_back();
	}
};