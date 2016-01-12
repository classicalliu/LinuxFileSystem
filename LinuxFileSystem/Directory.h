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
