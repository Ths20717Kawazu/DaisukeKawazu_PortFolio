#pragma once


class Grid 
{
	public:
		//Grid�֘A�t�@�C�� grid.cpp,game.cpp
		//Grid�̕��ƍ����𒆓r���[�Ȑ����ɂ���ƁA�ڐG����̍ۂɌ덷�����܂�A�Ώۂ����蔲������ɔ��肳��鎖�ۂ���������
		//�L���̗ǂ��l�ɐݒ肷�邱��
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