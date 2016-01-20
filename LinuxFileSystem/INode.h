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


	INode(const short id, const int size, const int group_id, const std::string& username);

	// �������캯�������ڿ����ļ�����ʱ�ȿ���id���ɺ��������޸ġ�
	INode(const INode& other);

	// �ƶ����캯��
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
