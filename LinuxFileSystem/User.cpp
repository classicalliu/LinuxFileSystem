#include "User.h"



User::User(const std::string& username, const std::string& password, int groud_id) : username(username),
password(password),
group_id(groud_id) {
}

const std::string& User::get_username() const {
	return username;
}

void User::set_username(const std::string& username) {
	this->username = username;
}

const std::string& User::get_password() const {
	return password;
}

void User::set_password(const std::string& password) {
	this->password = password;
}

const int& User::get_group_id() const {
	return group_id;
}

void User::set_group_id(const int group_id) {
	this->group_id = group_id;
}

bool operator<(const User& user1, const User& user2) {
	return user1.username < user2.username;
}
