#pragma once

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
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
	Directory *parent_directory = nullptr;
	std::set<std::shared_ptr<Directory>> children_directories;
	std::set<std::shared_ptr<File>> children_files;
	short inode_id = 0;

public:


	Directory() {
	}

	Directory(const std::string& name, Directory* const parent_directory, const short inode_id)
		: name(name),
		  parent_directory(parent_directory),
		  inode_id(inode_id){
	}

	std::set<std::shared_ptr<Directory>>& get_children_directories() {
		return children_directories;
	}


	std::set<std::shared_ptr<File>>& get_children_files() {
		return children_files;
	}

	const std::string& get_name() const {
		return name;
	}

	void set_name(const std::string& name) {
		this->name = name;
	}

	Directory* const& get_parent_directory() const {
		return parent_directory;
	}

	void set_parent_directory(Directory* const parent_directory) {
		this->parent_directory = parent_directory;
	}


	const short& get_inode_id() const {
		return inode_id;
	}

	void set_inode_id(const short inode_id) {
		this->inode_id = inode_id;
	}

	friend bool operator==(const Directory &directory1, const Directory &directory2);
	friend bool operator!=(const Directory &directory1, const Directory &directory2);
};

inline bool operator==(const Directory& directory1, const Directory& directory2) {
	return (directory1.name == directory2.name && directory1.inode_id == directory2.inode_id);
}

inline bool operator!=(const Directory& directory1, const Directory& directory2) {
	return !(directory1 == directory2);
}

#endif
