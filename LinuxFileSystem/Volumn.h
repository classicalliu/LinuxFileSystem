#pragma once
#include <array>
#include "INode.h"

class Volumn {
	// inode���飬���20��inode
	std::array<INode&, 20> inodeArray;
	// size�� һ�������Ϊ512B;
	static const int size = 512;
	// ���̿���
	std::array<int, 150> block_count;
};
