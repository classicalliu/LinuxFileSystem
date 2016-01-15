#pragma once
// ¿ÕÏĞ¿é½á¹¹
class Block {
	int address = 0;
public:
	static const int SIZE = 512;

	Block(const int address)
		: address(address) {
	}


	const int& get_address() const {
		return address;
	}

	void set_address(const int address) {
		this->address = address;
	}

	friend bool operator<(const Block &block1, const Block &block2);
};

inline bool operator<(const Block& block1, const Block& block2) {
	return block1.address < block2.address;
}
