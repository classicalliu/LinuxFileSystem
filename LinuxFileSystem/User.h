#pragma once
#include <string>
#include <list>
#include "INode.h"
#include <memory>
#include "File.h"
#include "Directory.h"

/**
* 用户类
* 用户名， 密码， 组别， 用户打开的文件的列表
*/
class User {
	// 用户名
	std::string username;
	// 密码
	std::string password;
	// 所属的用户组
	int group_id = 0;
	// 用户打开的文件列表的指针
	std::list<std::shared_ptr<INode>> user_open_file_list;
	// 属于这个用户的文件列表
//	std::set<std::shared_ptr<File>> user_file_set;
	// 属于这个用户的文件夹列表
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
