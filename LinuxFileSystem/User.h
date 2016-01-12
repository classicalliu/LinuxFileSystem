#pragma once
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

	User(const std::string& username, const std::string& password, int groud_id)
		: username(username),
		  password(password),
		  group_id(groud_id) {
	}

	const std::string& get_username() const {
		return username;
	}

	void set_username(const std::string& username) {
		this->username = username;
	}

	const std::string& get_password() const {
		return password;
	}

	void set_password(const std::string& password) {
		this->password = password;
	}

	const int& get_group_id() const {
		return group_id;
	}

	void set_group_id(const int group_id) {
		this->group_id = group_id;
	}


};
