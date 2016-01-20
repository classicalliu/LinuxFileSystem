#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <string>

// 块结构
// 空闲块或者文件块

namespace init_block {
	static std::string content = "the file init";
}

class Block {
	int address = 0;
//	std::string content = "the file init";
	std::string content = init_block::content;
public:
	static const int SIZE = 512;

	Block(const int address);

	Block(const Block& block);

	const int& get_address() const;

	void set_address(const int address);

	const std::string& get_content() const;

	void set_content(const std::string& content);

	Block& operator=(const Block &block);

	friend bool operator<(const Block &block1, const Block &block2);
};

bool operator<(const Block &block1, const Block &block2);


#endif
