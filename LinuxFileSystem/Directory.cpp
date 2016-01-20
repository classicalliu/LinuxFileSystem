#include "Directory.h"

Directory::Directory() {
}

Directory::Directory(const std::string& name, const std::shared_ptr<Directory>& parent_directory, const short inode_id): name(name),
                                                                                                                         parent_directory(parent_directory),
                                                                                                                         inode_id(inode_id) {
}

std::set<std::shared_ptr<Directory>>& Directory::get_children_directories() {
	return children_directories;
}

std::set<std::shared_ptr<File>>& Directory::get_children_files() {
	return children_files;
}

const std::string& Directory::get_name() const {
	return name;
}

void Directory::set_name(const std::string& name) {
	this->name = name;
}

std::shared_ptr<Directory>& Directory::get_parent_directory() {
	return parent_directory;
}

void Directory::set_parent_directory(const std::shared_ptr<Directory>& parent_directory) {
	this->parent_directory = parent_directory;
}

const short& Directory::get_inode_id() const {
	return inode_id;
}

void Directory::set_inode_id(const short inode_id) {
	this->inode_id = inode_id;
}

bool operator==(const Directory& directory1, const Directory& directory2) {
	return (directory1.name == directory2.name && directory1.inode_id == directory2.inode_id);
}

bool operator!=(const Directory& directory1, const Directory& directory2) {
	return !(directory1 == directory2);
}

bool operator<(const Directory& directory1, const Directory& directory2) {
	return directory1.name < directory2.name;
}

