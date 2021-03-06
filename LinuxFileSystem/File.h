#pragma once
#ifndef FILE_H
#define FILE_H
#include <string>

/**
* 文件结构
* 包含文件名， inode， 文件大小，文件内容
*/
class File {
	// 文件内容
	std::string file_name;
	short inode_id = 0;
public:
	static const int SIZE = 512;

	File(const std::string& file_name, const short inode_id);

	File(const File& file);


	const std::string& get_file_name() const;

	void set_file_name(const std::string& file_name);

	const short& get_inode_id() const;

	void set_inode_id(const short inode_id);

	friend bool operator<(const File& file1, const File& file2);
};

bool operator<(const File& file1, const File& file2);

#endif

