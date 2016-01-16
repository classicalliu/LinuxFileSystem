#pragma once
#ifndef INODE_H
#define INODE_H
#include <array>
#include <memory>
#include "Block.h"
#include <ctime>

class INode {
	// id��
	short id = 0;
	// �ļ���С
	int size = 0;
	// �ļ����Ӽ���
	int count = 1;
	// �ļ���ַ������,4��ֱ�ӿ�
		std::array<std::shared_ptr<Block>, 6> file_address_array;
		// TODO ����������ӵ�ַ
//	std::tuple<std::shared_ptr<Block>, std::shared_ptr<Block>, std::shared_ptr<Block>, std::shared_ptr<Block>, 
//		std::shared_ptr<std::shared_ptr<Block>>, 
//		std::shared_ptr<std::shared_ptr<std::shared_ptr<Block>>>> file_address_tuple;
	// �ļ������û���
	int group_id = 0;
	// �ļ������û�
	std::string username;
	// �ļ�Ȩ�� "111111111" 1��ʾ��0��ʾû��
	std::string authority = "111111111";
	// �ļ�����޸�ʱ��
	time_t last_modify_time = 0;

public:

	INode() {
	}


	INode(const short id, const int size, const int group_id, const std::string &username)
		: id(id),
		  size(size),
		  group_id(group_id),
		  username(username){
		// last_modify_time ����Ϊ��ǰʱ��
		auto time_now = time(nullptr);
		last_modify_time = time_now;
		// ����size�Ĵ�С����file_address_array ��һ����file system����
	}

	// �������캯�������ڿ����ļ�����ʱ�ȿ���id���ɺ��������޸ġ�
	INode(const INode& other) : id(other.id), size(other.size), count(1), file_address_array(other.file_address_array), group_id(other.group_id), username(other.username), authority(other.authority) {
		auto time_now = time(nullptr);
		last_modify_time = time_now;
	}

	// �ƶ����캯��
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
