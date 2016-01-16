#pragma once
#ifndef BLOCK_H
#define BLOCK_H
// 块结构
// 空闲块或者文件块
class Block {
	int address = 0;
	std::string content;
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
