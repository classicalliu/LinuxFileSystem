#pragma once
#include <array>
#include "INode.h"
/**
* ���ò���
*/
class Volumn {
public:
	// inode���飬���20��inode
	std::array<std::shared_ptr<INode>, 20> inode_array;
	// size�� һ�������Ϊ512B;
	static const int size = 512;
	// ���̿���
	std::array<Block, 200> block_count;
};
