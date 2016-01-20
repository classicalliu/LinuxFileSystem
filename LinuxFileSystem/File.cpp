#include "File.h"

File::File(const std::string& file_name, const short inode_id): file_name(file_name),
                                                                inode_id(inode_id) {
}

File::File(const File& file): file_name(file.file_name),
                              inode_id(file.inode_id) {
}

const std::string& File::get_file_name() const {
	return file_name;
}

void File::set_file_name(const std::string& file_name) {
	this->file_name = file_name;
}

const short& File::get_inode_id() const {
	return inode_id;
}

void File::set_inode_id(const short inode_id) {
	this->inode_id = inode_id;
}

