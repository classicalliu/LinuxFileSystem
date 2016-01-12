#pragma once
#include <string>
#include <list>
#include "INode.h"

class User {
	// 用户名
	std::string username;
	// 密码
	std::string password;
	// 所属的用户组
	int group_id = 0;
	// 用户打开的文件列表的引用
	std::list<INode &> user_open_file_list;

public:

	User(const std::string& username, const std::string& password, int groud_id)
		: username(username),
		  password(password),
		  group_id(groud_id) {
	}

};
