#pragma once

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
#include <memory>
#include <set>
#include "File.h"

/**
* �ļ��У��и�����
* ��ָ���丸�ļ��е�ָ��
* �������ļ��е�set
* �����ļ���set
*/
class Directory {
	std::string name;
	std::shared_ptr<Directory> parent_directory;
	std::set<std::shared_ptr<Directory>> children_directories;
	std::set<std::shared_ptr<File>> children_files;
	short inode_id = 0;

public:
	Directory();

	Directory(const std::string& name, const std::shared_ptr<Directory>& parent_directory, const short inode_id);

	std::set<std::shared_ptr<Directory>>& get_children_directories();

	std::set<std::shared_ptr<File>>& get_children_files();

	const std::string& get_name() const;

	void set_name(const std::string& name);

	std::shared_ptr<Directory>& get_parent_directory();

	void set_parent_directory(const std::shared_ptr<Directory>& parent_directory);

	const short& get_inode_id() const;

	void set_inode_id(const short inode_id);

	friend bool operator==(const Directory& directory1, const Directory& directory2);
	friend bool operator!=(const Directory& directory1, const Directory& directory2);
	friend bool operator<(const Directory& directory1, const Directory& directory2);
};

bool operator==(const Directory& directory1, const Directory& directory2);
bool operator!=(const Directory& directory1, const Directory& directory2);
bool operator<(const Directory& directory1, const Directory& directory2);

#endif

