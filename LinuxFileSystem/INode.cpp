#include "INode.h"


INode::INode(const short id, const int size, const int group_id, const std::string& username) : id(id),
size(size),
group_id(group_id),
username(username) {
	// last_modify_time 设置为当前时间
	auto time_now = time(nullptr);
	last_modify_time = time_now;
	// 根据size的大小设置file_address_array 这一步由file system分配
}

INode::INode(const INode& other): id(other.id), size(other.size), count(1), file_address_array(other.file_address_array), group_id(other.group_id), username(other.username), authority(other.authority) {
	auto time_now = time(nullptr);
	last_modify_time = time_now;
}

INode::INode(INode&& other): id(other.id), size(other.size), count(1), file_address_array(other.file_address_array), group_id(other.group_id), username(other.username), authority(other.authority) {
	auto time_now = time(nullptr);
	last_modify_time = time_now;
}

void INode::add_count() {
	++count;
}

const short& INode::get_id() const {
	return id;
}

void INode::set_id(const short id) {
	this->id = id;
}

const int& INode::get_size() const {
	return size;
}

void INode::set_size(const int size) {
	this->size = size;
}

const int& INode::get_count() const {
	return count;
}

void INode::set_count(const int count) {
	this->count = count;
}

const int& INode::get_group_id() const {
	return group_id;
}

void INode::set_group_id(const int group_id) {
	this->group_id = group_id;
}

const std::string& INode::get_authority() const {
	return authority;
}

void INode::set_authority(const std::string& authority) {
	this->authority = authority;
}

const time_t& INode::get_last_modify_time() const {
	return this->last_modify_time;
}

void INode::set_last_modify_time(const time_t last_modify_time) {
	this->last_modify_time = last_modify_time;
}

std::array<std::shared_ptr<Block>, 6>& INode::get_file_address_array() {
	return file_address_array;
}

void INode::set_file_address_array(const std::array<std::shared_ptr<Block>, 6>& file_address_array) {
	this->file_address_array = file_address_array;
}

const std::string& INode::get_username() const {
	return username;
}

void INode::set_username(const std::string& username) {
	this->username = username;
}

bool operator<(const INode& inode1, const INode& inode2) {
	return inode1.id < inode2.id;
}
