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
	//记录所有组
	std::set<Group> group_set;
	// 记录用户
	std::set<User> user_set;
	// 记录空闲块
	std::list<Block> block_list;
	// 记录所有的inode
	std::set<INode> inode_set;
	// 根目录
	Directory &root_directory;
	// 当前目录
	// 可以从当前目录中读取File信息，从File中读取inode信息
	Directory &current_directory;
	// 当前组
	Group &current_group;
	// 当前用户
	User &current_user;
public:

	// 检测用户是否存在
	bool check_username(std::string username);
	// 在用户已经存在的前提下检测密码是否正确
	bool check_password(std::string password) const;
	// 检测文件是否已经存在
	bool check_file_exist(std::string filename) const;
	// 检测文件夹是否已经存在
	bool check_directory_exist(std::string directory_name);

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
	* 根据当前用户组id找出用户
	*/
	const Group& load_group_by_id(const short id);
	const File& load_file_by_filename(const std::string& filename) const;
	const INode& load_inode_by_id(const short id);

	/**
	* 创建新文件
	*/
	bool new_file(std::string filename);

	// 创建新文件夹
	bool new_directory(std::string directory_name);

	// ls命令显示当前的文件和文件夹的名字
	std::pair<std::vector<std::string>, std::vector<std::string>> ls_names();

	// 修改密码
	bool change_password(std::string password) const;

	// 修改用户权限，输入string 例如777表示用户，组，其他用户
	// 确保输入的是一个三位的数字
	// 检测工作在上一层完成
	bool change_mode(std::string filename, std::string authority);

	// 修改文件用户
};

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
	auto flag = std::find_if(files.begin(), files.end(), [filename](const File & file_tmp) {return file_tmp.get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_directory_exist(std::string directory_name) {
	// 查找当前目录下的子目录
	auto directories = current_directory.get_children_directories();
	auto flag = std::find_if(directories.begin(), directories.end(), [directory_name](const Directory & dr) {return dr.get_name() == directory_name; });
	if (flag == directories.end()) {
		return false;
	}
	return true;
}

inline std::string&& FileSystem::login(std::string username, std::string password)
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

inline std::string&& FileSystem::user_register(std::string username, std::string password) {
	// 找到了就提示用户已存在
	if(check_username(username)) {
		return "user_already_exist";
	}
	// 检测用户名合法性（只能为英文大小写字母和数字，必须以英文开头， 用户名只能在30位之间）
	std::regex pattern("[A-Za-z]\\w{3,29}");
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
	auto registed_user = std::make_shared<User>(username, password, current_group.get_group_id());
//	User registed_user(username, password, current_group.get_group_id());
	user_set.insert(*registed_user);

	current_user = *registed_user;

	return "success";
}

inline const Group& FileSystem::load_group_by_id(const short id) {
	auto flag = std::find_if(group_set.begin(), group_set.end(), [id](const Group &gp) {return gp.get_group_id() == id; });
	return *flag;
}

inline const File& FileSystem::load_file_by_filename(const std::string& filename) const {
	auto files = current_directory.get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const File& file) {return file.get_file_name() == filename; });
	return *flag;
}

inline const INode& FileSystem::load_inode_by_id(const short id) {
	auto flag = std::find_if(inode_set.begin(), inode_set.end(), [id](const INode &inode) {return inode.get_id() == id; });
	return *flag;
}

inline bool FileSystem::new_file(std::string filename) {
	if (check_file_exist(filename)) {
		return "file_already_exist";
	}
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件,14位
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// 如果文件名不合法
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// 检查是否有空闲块
	if (block_list.empty()) {
		return false;
	}
	// 创建文件
	// 创建inode
	auto id_new = inode_set.size() + 1;
	auto inode_new = std::make_shared<INode>();
//	INode inode_new;
	inode_new->set_id(id_new);

	// 获取下一个空闲块
	auto next_free_block = block_list.front();
	// 从空闲块列表中删除这个块
	block_list.erase(block_list.begin());
	// 数组指向这个块
	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
	// 设置用户组
	inode_new->set_id(current_group.get_group_id());
	// 设置最后修改时间
	inode_new->set_last_modify_time(time(nullptr));
	// 链接到文件
	auto file = std::make_shared<File>(filename, id_new);

	// 插入inode
	inode_set.insert(*inode_new);
	// 插入到当前目录下的文件列表中
	current_directory.get_children_files().insert(*file);

	return true;
}

inline bool FileSystem::new_directory(std::string directory_name) {
	// 检测文件夹是否已存在
	if (check_directory_exist(directory_name)) {
		return "directory_already_exist";
	}
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件夹,14位
	std::regex directory_pattern("[A-Za-z_.]\\w{0,14}");
	// 如果文件夹名不合法
	if (!std::regex_match(directory_name, directory_pattern)) {
		return "directory_error";
	}
	// 检查是否有空闲块
	if (block_list.empty()) {
		return false;
	}
	auto inode_id = inode_set.size() + 1;
	auto inode_new = std::make_shared<INode>();
	inode_new->set_id(inode_id);
	auto next_free_block = block_list.front();
	block_list.erase(block_list.begin());
	// 数组指向这个块
	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
	// 设置用户组
	inode_new->set_id(current_group.get_group_id());
	// 设置最后修改时间
	inode_new->set_last_modify_time(time(nullptr));
	// 链接到文件夹
	auto directory_new = std::make_shared<Directory>(directory_name, &current_directory, inode_id);

	inode_set.insert(*inode_new);
	current_directory.get_children_directories().insert(directory_new);

	return true;
}

inline std::pair<std::vector<std::string>, std::vector<std::string>> FileSystem::ls_names() {
	std::vector<std::string> files;
	std::vector<std::string> directories;
	for (auto c : current_directory.get_children_files()) {
		files.push_back(c.get_file_name());
	}
	for (auto c : current_directory.get_children_directories()) {
		directories.push_back(c->get_name());
	}
	return std::make_pair(files, directories);
}

inline bool FileSystem::change_password(std::string password) const {
	//检测密码合法性
	std::regex password_pattern("[A-Za-z0-9]{6,30}");
	if (!std::regex_match(password, password_pattern)) {
		return false;
	}
	// 设置密码
	current_user.set_password(password);
	return true;
}

inline bool FileSystem::change_mode(std::string filename, std::string authority) {
	if(!check_file_exist(filename)) {
		return false;
	}
	auto file = load_file_by_filename(filename);
	auto inode_id = file.get_inode_id();
	auto inode = load_inode_by_id(inode_id);
	inode.set_authority(authority);
	return true;
}
