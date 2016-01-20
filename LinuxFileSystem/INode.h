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


	INode(const short id, const int size, const int group_id, const std::string& username);

	// 拷贝构造函数，用于拷贝文件，暂时先拷贝id，由后续操作修改。
	INode(const INode& other);

	// 移动构造函数
	INode(INode&& other);

	void add_count();

	const short& get_id() const;

	void set_id(const short id);

	const int& get_size() const;

	void set_size(const int size);

	const int& get_count() const;

	void set_count(const int count);

	const int& get_group_id() const;

	void set_group_id(const int group_id);

	const std::string& get_authority() const;

	void set_authority(const std::string& authority);

	const time_t& get_last_modify_time() const;

	void set_last_modify_time(const time_t last_modify_time);

	std::array<std::shared_ptr<Block>, 6>& get_file_address_array();

	void set_file_address_array(const std::array<std::shared_ptr<Block>, 6>& file_address_array);

	const std::string& get_username() const;

	void set_username(const std::string& username);

	friend bool operator<(const INode& inode1, const INode& inode2);
};

bool operator<(const INode& inode1, const INode& inode2);



#endif
