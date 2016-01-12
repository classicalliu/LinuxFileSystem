#pragma once
#include <string>
#include <set>
#include "User.h"
#include "Block.h"
#include <regex>
#include "Group.h"
#include "Directory.h"

class FileSystem {
	// 文件系统的名字
	std::string name;
	// 文件系统大小, 默认200个块，每个512B
	int size = 200 * 512;
	// 记录用户
	std::set<User> user_set;
	// 记录空闲块
	std::list<Block> block_list;
	// 记录所有的inode
//	std::set<INode> inode_set;
	// 根目录
	Directory root_directory;
	// 当前目录
	// 可以从当前目录中读取File信息，从File中读取inode信息
	Directory current_directory;
	// 当前组
	Group current_group;
	// 当前用户
	User current_user;
public:
	// 检测用户是否存在
	bool check_username(std::string username);
	// 在用户已经存在的前提下检测密码是否正确
	bool check_password(std::string password) const;

	bool check_file_exist(std::string filename);

	/**
	* 用户登录函数
	* 首先检测用户是否存在，不存在就返回错误信息
	* 然后检测用户密码是否匹配，不匹配就返回错误信息
	* 检测通过则返回成功信息
	*/
	std::string&& login(std::string username, std::string password);

	/**
	* 用户注册
	* 检测用户名是否存在，存在就返回错误信息
	* 检测用户名是否合法，不合法就返回错误信息
	* 检测密码是否合法，不合法就返回错误信息
	* 设置用户信息，组为当前组
	* 返回注册成功信息
	*/
	std::string&& user_register(std::string username, std::string password);

	/**
	* 创建新文件
	*/
	bool new_file(std::string filename);
};

inline bool FileSystem::check_username(std::string username)
{
	auto flag = std::find(user_set.begin(), user_set.end(), [username](const User &user_tmp) {return user_tmp.get_username() == username; });
	current_user = *flag;
	if (flag != user_set.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_password(std::string password) const {
	return current_user.get_password() == password;
}

inline bool FileSystem::check_file_exist(std::string filename) {
	// 查找当前目录下的子文件
	auto files = current_directory.get_children_files();
	auto flag = std::find(files.begin(), files.end(), [filename](const File & file_tmp) {return file_tmp.get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline std::string&& FileSystem::login(std::string username, std::string password)
{
	if (!check_username(username)) {
		return "user_not_exit";
	}
	if (!check_password(password)) {
		return "password_not_right";
	}
	return "success";
}

inline std::string&& FileSystem::user_register(std::string username, std::string password) {
	// 找到了就提示用户已存在
	if(check_username(username)) {
		return "user_already_exist";
	}
	// 检测用户名合法性（只能为英文大小写字母和数字，必须以英文开头， 用户名只能在30位之间）
	std::regex pattern("[A-Za-z]\\w{5,29}");
	// 不匹配就返回用户名非法
	if (!std::regex_match(username, pattern)) {
		return "username_error";
	}
	//检测密码合法性
	std::regex password_pattern("[A-Za-z0-9]{6,30}");
	if(!std::regex_match(password, password_pattern)) {
		return "password_error";
	}
	// 如果用户名合法就创建用户,组为当前组
	User registed_user(username, password, current_group.get_group_id());
	user_set.insert(registed_user);
	return "success";
}

inline bool FileSystem::new_file(std::string filename) {
	if (check_file_exist(filename)) {
		return "file_already_exist";
	}
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件,14位
	std::regex filename_pattern("[A-Za-z_.]\\w{0.14}");
	// 如果文件名不合法
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// 创建文件
	
}
