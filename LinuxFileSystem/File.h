#pragma once
#ifndef FILE_H
#define FILE_H
#include <string>

/**
* �ļ��ṹ
* �����ļ����� inode�� �ļ���С���ļ�����
*/
class File {
	// �ļ�����
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
};

#endif

