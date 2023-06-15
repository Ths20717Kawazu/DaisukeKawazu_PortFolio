#pragma once


class Grid 
{
	public:
		static const int GridWidth = 250;
		static const int GridHeight = 250;

		Grid() {};
		~Grid() {};

		void addMembersIngrid(class Actor* actor);
		void removeMembersIngrid(Actor* actor);
		std::vector<class Actor*>& GetGridMembers() { return mGridMembers; }

private:
		std::vector<Actor*>mGridMembers;
		
};