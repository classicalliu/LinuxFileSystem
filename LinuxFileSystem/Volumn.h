#pragma once
#include <array>
#include "INode.h"
/**
* 作用不明
*/
class Volumn {
public:
	// inode数组，最多20个inode
	std::array<std::shared_ptr<INode>, 20> inode_array;
	// size， 一个块最多为512B;
	static const int size = 512;
	// 卷盘块数
	std::array<Block, 200> block_count;
};
