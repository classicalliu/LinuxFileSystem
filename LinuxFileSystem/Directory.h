#pragma once
#include <string>
#include "File.h"

/**
* �ļ��У��и�����
* ��ָ���丸�ļ��е�ָ��
* �������ļ��е�set
* �����ļ���set
*/
class Directory {
	std::string name;
	Directory *parent_directory = nullptr;
	std::set<std::shared_ptr<Directory>> children_directories;
	std::set<File> children_files;
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

	std::set<File>& get_children_files() {
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
};
