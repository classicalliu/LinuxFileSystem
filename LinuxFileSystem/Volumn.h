#pragma once
#include <array>
#include "INode.h"

class Volumn {
	// inode数组，最多20个inode
	std::array<INode&, 20> inodeArray;
	// size， 一个块最多为512B;
	static const int size = 512;
	// 卷盘块数
	std::array<int, 150> block_count;
};
