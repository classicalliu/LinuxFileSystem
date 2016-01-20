#include "Block.h"


Block::Block(const int address): address(address) {
}

Block::Block(const Block& block): address(address),
                                  content(content) {
}

const int& Block::get_address() const {
	return address;
}

void Block::set_address(const int address) {
	this->address = address;
}

const std::string& Block::get_content() const {
	return content;
}

void Block::set_content(const std::string& content) {
	this->content = content;
}

Block& Block::operator=(const Block& block) {
	address = block.address;
	content = block.content;
	return *this;
}

bool operator<(const Block& block1, const Block& block2) {
	return block1.address < block2.address;
}

