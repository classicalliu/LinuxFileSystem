#pragma once
#include <string>

class Directory {
	std::string name;
	short inode_id;

public:
	Directory(const std::string& name, short inode_id)
		: name(name),
		inode_id(inode_id) {
	}


};
