#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include "INode.h"
#include <memory>

/**
* �û���
* �û����� ���룬 ��� �û��򿪵��ļ����б�
*/
class User {
	// �û���
	std::string username;
	// ����
	std::string password;
	// �������û���
	int group_id = 0;
	// �û��򿪵��ļ��б��ָ��
	std::list<std::shared_ptr<INode>> user_open_file_list;
public:


	User() {
	}

	User(const std::string& username, const std::string& password, int groud_id);

	const std::string& get_username() const;

	void set_username(const std::string& username);

	const std::string& get_password() const;

	void set_password(const std::string& password);

	const int& get_group_id() const;

	void set_group_id(const int group_id);

	friend bool operator<(const User &user1, const User &user2);
};

bool operator<(const User &user1, const User &user2);


#endif
