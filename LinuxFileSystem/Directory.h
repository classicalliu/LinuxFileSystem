#pragma once

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
#include <memory>
#include <set>
#include "File.h"

/**
* 文件夹，有个名字
* 有指向其父文件夹的指针
* 其中子文件夹的set
* 其中文件的set
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

