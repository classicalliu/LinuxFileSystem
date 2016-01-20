#pragma once
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <string>
#include <set>
#include "User.h"
#include "Block.h"
#include <regex>
#include "Group.h"
#include "Directory.h"

namespace init_file {
	const int BLOCK_COUNT = 200;
	const int BLOCK_SIZE = 512;
}

// 测试使用的
class FileSystem {
	// 文件系统的名字
	std::string name;
	// 文件系统大小, 默认200个块，每个512B
	int size = init_file::BLOCK_COUNT * init_file::BLOCK_SIZE;
	//记录所有组
	std::set<std::shared_ptr<Group>> group_set;
	// 记录用户
	std::set<std::shared_ptr<User>> user_set;
	// 记录空闲块
	std::set<std::shared_ptr<Block>> block_set;
	// 记录所有的inode
	std::set<std::shared_ptr<INode>> inode_set;
	// 根目录
	std::shared_ptr<Directory> root_directory;
	//	std::shared_ptr<Directory> root_directory;
	// 当前目录
	// 可以从当前目录中读取File信息，从File中读取inode信息
	std::shared_ptr<Directory> current_directory;
	//	std::shared_ptr<Directory> current_directory;
	// 当前组
	std::shared_ptr<Group> current_group;
	// 当前用户
	std::shared_ptr<User> current_user;
public:

	// 初始化系统名字

	FileSystem();

	FileSystem(const std::string& name);

	// 初始化所有的条件
	// 创建root目录
	// 分配所有的空块， 200个，每个512B
	void init();

	// 检测用户是否存在
	bool check_username(const std::string& username);
	// 在用户已经存在的前提下检测密码是否正确
	bool check_password(const std::string& password) const;
	// 检测文件是否已经存在
	bool check_file_exist(const std::string& filename) const;
	// 检测文件夹是否已经存在
	bool check_directory_exist(const std::string& directory_name) const;

//	bool check_authority(const std::string& authority);

	static std::vector<std::string> split_path(const std::string &path);

	// int to string
	static std::string int_to_string(const int num);

	/**
	* 用户登录函数
	* 首先检测用户是否存在，不存在就返回错误信息
	* 然后检测用户密码是否匹配，不匹配就返回错误信息
	* 检测通过则返回成功信息
	*/
	std::string login(const std::string& username, const std::string& password);

	/**
	* 用户注册
	* 检测用户名是否存在，存在就返回错误信息
	* 检测用户名是否合法，不合法就返回错误信息
	* 检测密码是否合法，不合法就返回错误信息
	* 设置用户信息，组为当前组
	* 返回注册成功信息
	*/
	std::string user_register(const std::string& username, const std::string& password);

	/**
	* 根据当前用户组id找出用户
	*/
	std::shared_ptr<Group> load_group_by_id(const short id);
	std::shared_ptr<File> load_file_by_filename(const std::string& filename) const;
	std::shared_ptr<INode> load_inode_by_id(const short id);

	/**
	* 创建新文件
	*/
	std::string new_file(const std::string& filename);
	// vi command
	std::string new_file_with_content(const std::string& filename, const std::string& content);

	// 创建新文件夹
	std::string new_directory(const std::string& directory_name);

	// ls命令显示当前的文件和文件夹的名字
	std::pair<std::vector<std::string>, std::vector<std::string>> list_names() const;

	// 修改密码
	bool change_password(const std::string& password) const;

	// 修改用户权限，输入string 例如777表示用户，组，其他用户
	// 确保输入的是一个三位的数字
	// 检测工作在上一层完成
	bool change_mode(const std::string& filename, const std::string& authority);

	// 修改文件用户
	std::string change_file_user(const std::string& filename, const std::string& username);

	// 修改文件组
	std::string change_file_group(const std::string& filename, const std::string& group);
	// 显示当前目录
	std::string display_current_directory() const;
	// 改变当前目录
	bool change_current_directory(const std::string& dir);
	void change_dir(const std::vector<std::string>& dir, const int count, const int count_size);

	// 删除文件
	std::string remove_file(const std::string& filename);

	// 删除文件夹rm -r
	std::string remove_directory(const std::string& dirctory_name);
	void delete_directory(const std::shared_ptr<Directory>& dir_pointer);
	// 删除空文件夹 rmdir
	std::string remove_empty_directory(const std::string& directory_name);

	// mv命令，重命名文件
	std::string rename_file(const std::string& filename_old, const std::string& filename_new) const;

	// cp 命令，拷贝文件,旧文件，新文件名，只要名字，不要路径，简单实现
	std::string copy_file(const std::string& filename, const std::string& filename_newfile);

	// ln命令，建立文件链接
	std::string link_file(const std::string& filename, const std::string& link_name);

	//cat 命令
	std::string display_file_context(const std::string& filename);

	static bool umask_command(const std::string& authority);

	std::string get_username() const;

	std::string list_file_details(const std::string &filename);
	std::vector<std::string> list_all_file_details();

};


#endif
