#pragma once


class Grid 
{
	public:
		//Grid関連ファイル grid.cpp,game.cpp
		//Gridの幅と高さを中途半端な数字にすると、接触判定の際に誤差がうまれ、対象をすり抜けた後に判定される事象が発生する
		//キリの良い値に設定すること
		static const int GridWidth = 1000;
		static const int GridHeight = 1000;

		Grid() {};
		~Grid() {};

		void addMembersIngrid(class Actor* actor);
		void removeMembersIngrid(Actor* actor);
		std::vector<class Actor*>& GetGridMembers() { return mGridMembers; }

private:
		std::vector<Actor*>mGridMembers;
		
};