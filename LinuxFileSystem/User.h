#pragma once
#include <string>
#include <list>
#include "INode.h"

class User {
	// �û���
	std::string username;
	// ����
	std::string password;
	// �������û���
	int group_id = 0;
	// �û��򿪵��ļ��б������
	std::list<INode &> user_open_file_list;

public:

	User(const std::string& username, const std::string& password, int groud_id)
		: username(username),
		  password(password),
		  group_id(groud_id) {
	}

};
