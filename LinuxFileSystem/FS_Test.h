#pragma once
#ifndef FS_TEST_H
#define FS_TEST_H
#include <string>
#include <set>
#include "User.h"
#include "Block.h"
#include <regex>
#include "Group.h"
#include "Directory.h"
#include <iostream>

const int BLOCK_COUNT = 200;

namespace init_file {
	User user;
	Group group;
	Directory directory;
}
// 测试使用的
class FileSystem {
public:
	// 文件系统的名字
	std::string name;
	// 文件系统大小, 默认200个块，每个512B
	int size = BLOCK_COUNT * 512;
	//记录所有组
	std::set<Group> group_set;
	// 记录用户
	std::set<User> user_set;
	// 记录空闲块
	std::set<std::shared_ptr<Block>> block_set;
	// 记录所有的inode
	std::set<std::shared_ptr<INode>> inode_set;
	// 记录所有的目录的实体
	std::set<std::shared_ptr<Directory>> directory_set;
	//记录所有文件的实体
	std::set<std::shared_ptr<File>> file_set;
	// 根目录
	Directory &root_directory = init_file::directory;
	//	std::shared_ptr<Directory> root_directory;
	// 当前目录
	// 可以从当前目录中读取File信息，从File中读取inode信息
	Directory &current_directory = init_file::directory;
	//	std::shared_ptr<Directory> current_directory;
	// 当前组
	Group &current_group = init_file::group;
	// 当前用户
	User &current_user = init_file::user;
public:

	// 初始化系统名字

	FileSystem();


	FileSystem(const std::string& name);

	// 初始化所有的条件
	// 创建root目录
	// 分配所有的空块， 200个，每个512B
	void init();

	// 检测用户是否存在
	bool check_username(std::string username);
	// 在用户已经存在的前提下检测密码是否正确
	bool check_password(std::string password) const;
	// 检测文件是否已经存在
	bool check_file_exist(std::string filename) const;
	// 检测文件夹是否已经存在
	bool check_directory_exist(std::string directory_name) const;

	static std::vector<std::string> split_path(const std::string &path);

	/**
	* 用户登录函数
	* 首先检测用户是否存在，不存在就返回错误信息
	* 然后检测用户密码是否匹配，不匹配就返回错误信息
	* 检测通过则返回成功信息
	*/
	std::string login(std::string username, std::string password);

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
	* 根据当前用户组id找出用户
	*/
	const Group& load_group_by_id(const short id);
	File& load_file_by_filename(const std::string& filename) const;
	INode& load_inode_by_id(const short id);

	/**
	* 创建新文件
	*/
	std::string new_file(std::string filename);

	// 创建新文件夹
	std::string new_directory(std::string directory_name);

	// ls命令显示当前的文件和文件夹的名字
	std::pair<std::vector<std::string>, std::vector<std::string>> ls_names() const;

	// 修改密码
	bool change_password(std::string password) const;

	// 修改用户权限，输入string 例如777表示用户，组，其他用户
	// 确保输入的是一个三位的数字
	// 检测工作在上一层完成
	bool change_mode(std::string filename, std::string authority);

	// 修改文件用户
	std::string change_file_user(std::string filename, std::string username);

	// 修改文件组
	std::string change_file_group(std::string filename, std::string group);
	// 显示当前目录
	std::string display_current_directory() const;
	// 改变当前目录
	bool change_current_directory(std::string dir);
	void change_dir(std::vector<std::string> dir, int count, int count_size);

	// 删除文件
	std::string remove_file(std::string filename);

	// 删除文件夹rm -rf
	std::string remove_directory(std::string dirctory_name);
	// 删除空文件夹 rmdir
	std::string remove_empty_directory(std::string directory_name);

	// mv命令，重命名文件
	std::string rename_file(std::string filename_old, std::string filename_new) const;

	// cp 命令，拷贝文件,旧文件，新文件名，只要名字，不要路径，简单实现
	std::string copy_file(std::string filename, std::string filename_newfile);

	// ln命令，建立文件链接
	std::string link_file(std::string filename, std::string link_name);

};

inline FileSystem::FileSystem() : name("File_System") {
	init();
}

inline FileSystem::FileSystem(const std::string& name) : name(name) {
	init();
}

inline void FileSystem::init() {
	// 初始化系统拥有的Block， 200个，每个512B
	for (auto i = 0; i < BLOCK_COUNT; ++i) {
		auto block_tmp = std::make_shared<Block>(i);
		block_set.insert(block_tmp);
	}
	// 创建root组
	Group group(0, "root_group");
	group_set.insert(group);
	// 创建root用户
	User user("root", "root", 0);
	user_set.insert(user);

	// 分配root文件夹所需的inode
	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
	// 初次分配，所以分配第一个空块
	directory_inode->get_file_address_array()[0] = *block_set.begin();
	inode_set.insert(directory_inode);

	// 生成root文件夹, root文件夹的父目录是其自身
	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
	directory_tmp->set_parent_directory(directory_tmp.get());
	directory_set.insert(directory_tmp);
	// 切换root目录和current目录
	root_directory = *directory_tmp;
	current_directory = root_directory;

	// 设置当前组和当前用户
	current_group = group;
	current_user = user;
	std::cout << "current_user = " << user.get_username() << std::endl;
	std::cout << "current_group = " << group.get_group_id() << "  " << group.get_group_name() << std::endl;
}

inline bool FileSystem::check_username(std::string username)
{
	auto flag = std::find_if(user_set.begin(), user_set.end(), [username](const User &user_tmp) {return user_tmp.get_username() == username; });
	current_user = *flag;
	if (flag != user_set.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_password(std::string password) const {
	return current_user.get_password() == password;
}

inline bool FileSystem::check_file_exist(std::string filename) const {
	// 查找当前目录下的子文件
	auto files = current_directory.get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file_tmp) {return file_tmp->get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_directory_exist(std::string directory_name) const {
	// 查找当前目录下的子目录
	auto directories = current_directory.get_children_directories();
	auto flag = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> & dr) {return dr->get_name() == directory_name; });
	if (flag == directories.end()) {
		return false;
	}
	return true;
}

inline std::vector<std::string> FileSystem::split_path(const std::string& path) {
	std::vector<std::string> result;
	std::string c = "/";
	std::string::size_type pos1, pos2;
	pos2 = path.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		result.push_back(path.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = path.find(c, pos1);
	}
	if (pos1 != path.length())
		result.push_back(path.substr(pos1));

	std::vector<std::string> result2;
	for (const auto &tmp : result) {
		if (tmp != "") {
			result2.push_back(tmp);
		}
	}
	return result2;
}

inline const Group& FileSystem::load_group_by_id(const short id) {
	auto flag = std::find_if(group_set.begin(), group_set.end(), [id](const Group &gp) {return gp.get_group_id() == id; });
	return *flag;
}

inline File& FileSystem::load_file_by_filename(const std::string& filename) const {
	auto files = current_directory.get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {return file->get_file_name() == filename; });
	return *flag->get();
}

inline INode& FileSystem::load_inode_by_id(const short id) {
	auto flag = std::find_if(inode_set.begin(), inode_set.end(), [id](const std::shared_ptr<INode> &inode) {return inode->get_id() == id; });
	return *flag->get();
}

inline std::string FileSystem::login(std::string username, std::string password)
{
	if (!check_username(username)) {
		return "user_not_exit";
	}
	if (!check_password(password)) {
		return "password_not_right";
	}
	short group_id = current_user.get_group_id();
	current_group = load_group_by_id(group_id);
	return "success";
}




#endif
