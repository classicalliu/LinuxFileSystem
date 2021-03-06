#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <list>
#include "INode.h"
#include <memory>

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
public:
	User();

	User(const std::string& username, const std::string& password, int groud_id);

	const std::string& get_username() const;

	void set_username(const std::string& username);

	const std::string& get_password() const;

	void set_password(const std::string& password);

	const int& get_group_id() const;

	void set_group_id(const int group_id);

	friend bool operator<(const User& user1, const User& user2);
};

bool operator<(const User& user1, const User& user2);


#endif

