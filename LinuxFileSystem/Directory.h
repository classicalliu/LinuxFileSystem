#pragma once
#include <string>
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
	std::set<File> children_files;

public:

	std::set<std::shared_ptr<Directory>>& get_children_directories() {
		return children_directories;
	}

	std::set<File>& get_children_files() {
		return children_files;
	}

	const std::string& name1() const {
		return name;
	}

	void set_name(const std::string& name) {
		this->name = name;
	}

	Directory* const& parent_directory1() const {
		return parent_directory;
	}

	void set_parent_directory(Directory* const parent_directory) {
		this->parent_directory = parent_directory;
	}
};
