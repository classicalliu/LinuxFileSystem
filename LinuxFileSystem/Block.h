#pragma once
#ifndef BLOCK_H
#define BLOCK_H
// 块结构
// 空闲块或者文件块


//namespace init_block {
//	std::string content = "the file init";
//}

namespace init_block {
	static std::string content = "the file init";
}

class Block {
	int address = 0;
//	std::string content = "the file init";
	std::string content = init_block::content;
public:
	static const int SIZE = 512;

	Block(const int address)
		: address(address) {
	}

	Block(const Block &block)
		: address(address),
		content(content) {
	}

	const int& get_address() const {
		return address;
	}

	void set_address(const int address) {
		this->address = address;
	}


	const std::string& get_content() const {
		return content;
	}

	void set_content(const std::string& content) {
		this->content = content;
	}

	Block& operator=(const Block &block);

	friend bool operator<(const Block &block1, const Block &block2);
};

inline Block& Block::operator=(const Block& block) {
	address = block.address;
	content = block.content;
	return *this;
}

inline bool operator<(const Block& block1, const Block& block2) {
	return block1.address < block2.address;
}

#endif
