#pragma once
#ifndef INODE_H
#define INODE_H
#include <array>
#include <memory>
#include "Block.h"
#include <ctime>

class INode {
	// id号
	short id = 0;
	// 文件大小
	int size = 0;
	// 文件链接计数
	int count = 1;
	// 文件地址块数组,4个直接块
		std::array<std::shared_ptr<Block>, 6> file_address_array;
		// TODO 设置两个间接地址
//	std::tuple<std::shared_ptr<Block>, std::shared_ptr<Block>, std::shared_ptr<Block>, std::shared_ptr<Block>, 
//		std::shared_ptr<std::shared_ptr<Block>>, 
//		std::shared_ptr<std::shared_ptr<std::shared_ptr<Block>>>> file_address_tuple;
	// 文件所属用户组
	int group_id = 0;
	// 文件所属用户
	std::string username;
	// 文件权限 "111111111" 1表示有0表示没有
	std::string authority = "111111111";
	// 文件最后修改时间
	time_t last_modify_time = 0;

public:

	INode() {
	}


	INode(const short id, const int size, const int group_id, const std::string &username)
		: id(id),
		  size(size),
		  group_id(group_id),
		  username(username){
		// last_modify_time 设置为当前时间
		auto time_now = time(nullptr);
		last_modify_time = time_now;
		// 根据size的大小设置file_address_array 这一步由file system分配
	}

	// 拷贝构造函数，用于拷贝文件，暂时先拷贝id，由后续操作修改。
	INode(const INode& other) : id(other.id), size(other.size), count(1), file_address_array(other.file_address_array), group_id(other.group_id), username(other.username), authority(other.authority) {
		auto time_now = time(nullptr);
		last_modify_time = time_now;
	}

	// 移动构造函数
	INode(const INode&& other) noexcept : id(other.id), size(other.size), count(1), file_address_array(other.file_address_array), group_id(other.group_id), username(other.username), authority(other.authority) {
		auto time_now = time(nullptr);
		last_modify_time = time_now;
	}

	void add_count();

	const short& get_id() const {
		return id;
	}

	void set_id(const short id) {
		this->id = id;
	}

	const int& get_size() const {
		return size;
	}

	void set_size(const int size) {
		this->size = size;
	}

	const int& get_count() const {
		return count;
	}

	void set_count(const int count) {
		this->count = count;
	}

	const int& get_group_id() const {
		return group_id;
	}

	void set_group_id(const int group_id) {
		this->group_id = group_id;
	}

	const std::string& get_authority() const {
		return authority;
	}

	void set_authority(const std::string& authority) {
		this->authority = authority;
	}

	const time_t& get_last_modify_time() const {
		return this->last_modify_time;
	}

	void set_last_modify_time(const time_t last_modify_time) {
		this->last_modify_time = last_modify_time;
	}

	std::array<std::shared_ptr<Block>, 6>& get_file_address_array() {
		return file_address_array;
	}

	void set_file_address_array(const std::array<std::shared_ptr<Block>, 6>& file_address_array) {
		this->file_address_array = file_address_array;
	}


	const std::string& get_username() const {
		return username;
	}

	void set_username(const std::string& username) {
		this->username = username;
	}

	friend bool operator<(const INode& inode1, const INode& inode2);
};

inline void INode::add_count() {
	++count;
}

inline bool operator<(const INode& inode1, const INode& inode2) {
	return inode1.id < inode2.id;
}



#endif
