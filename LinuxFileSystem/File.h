#pragma once
#include <string>
#include "INode.h"

/**
* �ļ��ṹ
* �����ļ����� inode�� �ļ���С���ļ�����
*/
class File {
	// �ļ�����
	std::string file_content;
	std::string file_name;
	short inode_id = 0;
public:	
	// �ļ����СΪ512B
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