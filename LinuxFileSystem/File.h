#pragma once
#include <string>
#include "INode.h"

/**
* 文件结构
* 包含文件名， inode， 文件大小，文件内容
*/
class File {
	// 文件内容
	std::string file_content;
	std::string file_name;
	short inode_id = 0;
public:	
	// 文件块大小为512B
	static const int SIZE = 512;

	File(const std::string& file_name, const short inode_id)
		: file_name(file_name),
		inode_id(inode_id) {
	}


	const std::string& get_file_name() const {
		return file_name;
	}

	void set_file_name(const std::string& file_name) {
		this->file_name = file_name;
	}

	const short& get_inode_id() const {
		return inode_id;
	}

	void set_inode_id(const short inode_id) {
		this->inode_id = inode_id;
	}
};