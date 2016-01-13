#pragma once
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
	int count = 0;
	// 文件地址块数组
	std::array<std::shared_ptr<Block>, 6> file_address_array;
	// 文件所属用户组
	int group_id = 0;
	// 文件权限
	std::string authority;
	// 文件最后修改时间
	time_t last_modify_time = 0;

public:

	INode() {
	}


	INode(const short id, const int size, const int count, const std::array<std::shared_ptr<Block>, 6>& file_address_array, const int group_id, const std::string& authority)
		: id(id),
		  size(size),
		  count(count),
		  file_address_array(file_address_array),
		  group_id(group_id),
		  authority(authority) {
		auto time_now = time(nullptr);
		last_modify_time = time_now;
	}

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
};
