#pragma once
#include <string>
#include <list>
#include "INode.h"
#include <memory>
#include "File.h"
#include "Directory.h"

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
	// ��������û����ļ��б�
//	std::set<std::shared_ptr<File>> user_file_set;
	// ��������û����ļ����б�
//	std::set<std::shared_ptr<Directory>> user_directory_set;
public:


	User() {
	}

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


//	std::set<std::shared_ptr<File>>& get_user_file_set() {
//		return user_file_set;
//	}
//
//	void set_user_file_set(const std::set<std::shared_ptr<File>>& user_file_set) {
//		this->user_file_set = user_file_set;
//	}
//
//	std::set<std::shared_ptr<Directory>>& get_user_directory_set() {
//		return user_directory_set;
//	}
//
//	void set_user_directory_set(const std::set<std::shared_ptr<Directory>>& user_directory_set) {
//		this->user_directory_set = user_directory_set;
//	}
};
