#include "FileSystem.h"

#include <sstream>


FileSystem::FileSystem() : name("File_System") {
	init();
}

FileSystem::FileSystem(const std::string& name) : name(name) {
	init();
}

void FileSystem::init() {
	// 初始化系统拥有的Block， 200个，每个512B
	for (auto i = 0; i < init_file::BLOCK_COUNT; ++i) {
		auto block_tmp = std::make_shared<Block>(i);
		block_set.insert(block_tmp);
	}
	// 创建root组
	auto group = std::make_shared<Group>(0, "root_group");
	group_set.insert(group);
	// 创建root用户
	auto user = std::make_shared<User>("root", "root", 0);
	user_set.insert(user);

	// 分配root文件夹所需的inode
	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
	// 初次分配，所以分配第一个空块
	directory_inode->get_file_address_array()[0] = *block_set.begin();
	inode_set.insert(directory_inode);

	// 生成root文件夹, root文件夹的父目录是其自身
	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
	directory_tmp->set_parent_directory(directory_tmp);
	//	directory_set.insert(directory_tmp);
	// 切换root目录和current目录
	root_directory = directory_tmp;
	current_directory = root_directory;

	// 设置当前组和当前用户
	current_group = group;
	current_user = user;
	//	std::cout << "current_user = " << user.get_username() << std::endl;
	//	std::cout << "current_group = " << group.get_group_id() << "  " << group.get_group_name() << std::endl;

	//	std::cout << "init root directory name = " << root_directory->get_name() << std::endl;
	//	system("pause");
}

bool FileSystem::check_username(const std::string& username) {
	auto flag = std::find_if(user_set.begin(), user_set.end(), [username](const std::shared_ptr<User>& user_tmp) {
		                         return user_tmp->get_username() == username;
	                         });
	if (flag != user_set.end()) {
		current_user = *flag;
		return true;
	}
	return false;
}

bool FileSystem::check_password(const std::string& password) const {
	return current_user->get_password() == password;
}

bool FileSystem::check_file_exist(const std::string& filename) const {
	// 查找当前目录下的子文件
	auto files = current_directory->get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file_tmp) {
		                         return file_tmp->get_file_name() == filename;
	                         });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

bool FileSystem::check_directory_exist(const std::string& directory_name) const {
	// 查找当前目录下的子目录
	auto directories = current_directory->get_children_directories();
	auto flag = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory>& dr) {
		                         return dr->get_name() == directory_name;
	                         });
	if (flag == directories.end()) {
		return false;
	}
	return true;
}

std::vector<std::string> FileSystem::split_path(const std::string& path) {
	std::vector<std::string> result;
	std::string c = "/";
	std::string::size_type pos1, pos2;
	pos2 = path.find(c);
	pos1 = 0;
	while (std::string::npos != pos2) {
		result.push_back(path.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = path.find(c, pos1);
	}
	if (pos1 != path.length())
		result.push_back(path.substr(pos1));

	std::vector<std::string> result2;
	for (const auto& tmp : result) {
		if (tmp != "") {
			result2.push_back(tmp);
		}
	}
	return result2;
}

std::string FileSystem::int_to_string(const int num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}

std::shared_ptr<Group> FileSystem::load_group_by_id(const short id) {
	auto flag = std::find_if(group_set.begin(), group_set.end(), [id](const std::shared_ptr<Group>& gp) {
		                         return gp->get_group_id() == id;
	                         });
	return *flag;
}

std::shared_ptr<File> FileSystem::load_file_by_filename(const std::string& filename) const {
	auto files = current_directory->get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                         return file->get_file_name() == filename;
	                         });
	return *flag;
}

std::shared_ptr<INode> FileSystem::load_inode_by_id(const short id) {
	auto flag = std::find_if(inode_set.begin(), inode_set.end(), [id](const std::shared_ptr<INode>& inode) {
		                         return inode->get_id() == id;
	                         });
	return *flag;
}

std::string FileSystem::login(const std::string& username, const std::string& password) {
	if (!check_username(username)) {
		return "user_not_exist";
	}
	if (!check_password(password)) {
		return "password_not_right";
	}
	short group_id = current_user->get_group_id();
	current_group = load_group_by_id(group_id);

	if (username != "root") {
		auto directories = root_directory->get_children_directories();
		auto user_directory = std::find_if(directories.begin(), directories.end(), [username](const std::shared_ptr<Directory> dir) {
			                                   return dir->get_name() == username;
		                                   });
		current_directory = *user_directory;
	}
	else {
		current_directory = root_directory;
	}

	return "success";
}

std::string FileSystem::user_register(const std::string& username, const std::string& password) {
	// 找到了就提示用户已存在
	if (check_username(username)) {
		return "user_already_exist";
	}
	// 检测用户名合法性（只能为英文大小写字母和数字，必须以英文开头， 用户名只能在30位之间）
	std::regex pattern("[A-Za-z]\\w{3,29}");
	// 不匹配就返回用户名非法
	if (!std::regex_match(username, pattern)) {
		return "username_error";
	}
	//检测密码合法性
	std::regex password_pattern("[A-Za-z0-9]{4,30}");
	if (!std::regex_match(password, password_pattern)) {
		return "password_error";
	}

	// 如果用户名合法就创建用户,组为当前组
	auto registed_user = std::make_shared<User>(username, password, current_group->get_group_id());

	//	User registed_user(username, password, current_group.get_group_id());
	user_set.insert(registed_user);

	current_user = registed_user;

	// 生成一个用户目录
	auto inode_id = static_cast<short>(inode_set.size() + 1);
	auto directory_inode = std::make_shared<INode>(inode_id, 100, current_group->get_group_id(), username);

	inode_set.insert(directory_inode);

	auto user_directory = std::make_shared<Directory>(username, root_directory, inode_id);

	//	directory_set.insert(user_directory);

	root_directory->get_children_directories().insert(user_directory);

	current_directory = user_directory;

	return "success";
}

std::string FileSystem::display_current_directory() const {
	std::vector<std::string> dir;
	// 获取当前目录的指针
	for (auto index = current_directory; index != root_directory; index = index->get_parent_directory()) {
		dir.push_back(index->get_name());
	}
	std::string result = "/";
	for (auto i = dir.rbegin(); i != dir.rend(); ++i) {
		result += *i;
		result += "/";
	}
	return result;
}

std::string FileSystem::new_file(const std::string& filename) {
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
	if (block_set.empty()) {
		return "no_space";
	}
	// 创建文件
	// 创建inode
	auto id_new = static_cast<short>(inode_set.size() + 1);
	auto inode_new = std::make_shared<INode>();
	//	INode inode_new;
	inode_new->set_id(id_new);

	// 获取下一个空闲块
	auto next_free_block = *block_set.begin();
	// 从空闲块列表中删除这个块
	block_set.erase(block_set.begin());
	// 数组指向这个块
	inode_new->get_file_address_array()[0] = next_free_block;

	// 设置用户组
	inode_new->set_group_id(current_group->get_group_id());
	// 设置最后修改时间
	inode_new->set_last_modify_time(time(nullptr));
	inode_new->set_size(100 + next_free_block->get_content().size());
	// 链接到文件
	auto file = std::make_shared<File>(filename, id_new);

	// 插入inode
	inode_set.insert(inode_new);
	//	file_set.insert(file);
	// 插入到当前目录下的文件列表中
	current_directory->get_children_files().insert(file);

	return "success";
}

std::string FileSystem::new_file_with_content(const std::string& filename, const std::string& content) {
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
	if (block_set.empty()) {
		return "no_space";
	}
	// 创建文件
	// 创建inode
	auto id_new = static_cast<short>(inode_set.size() + 1);
	auto inode_new = std::make_shared<INode>();
	//	INode inode_new;
	inode_new->set_id(id_new);

	// 获取下一个空闲块
	auto next_free_block = *block_set.begin();
	next_free_block->set_content(content);
	// 从空闲块列表中删除这个块
	block_set.erase(block_set.begin());
	// 数组指向这个块
	inode_new->get_file_address_array()[0] = next_free_block;

	// 设置用户组
	inode_new->set_group_id(current_group->get_group_id());
	inode_new->set_size(100 + content.size());
	// 设置最后修改时间
	inode_new->set_last_modify_time(time(nullptr));
	// 链接到文件
	auto file = std::make_shared<File>(filename, id_new);

	// 插入inode
	inode_set.insert(inode_new);
	//	file_set.insert(file);
	// 插入到当前目录下的文件列表中
	current_directory->get_children_files().insert(file);

	return "success";
}

std::string FileSystem::new_directory(const std::string& directory_name) {
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
	if (block_set.empty()) {
		return "no_space";
	}
	auto inode_id = static_cast<short>(inode_set.size() + 1);

	auto next_free_block = *block_set.begin();
	block_set.erase(block_set.begin());

	// 设置用户组
	auto inode_new = std::make_shared<INode>(inode_id, 100, current_group->get_group_id(), current_user->get_username());
	// 数组指向这个块
	inode_new->get_file_address_array()[0] = next_free_block;
	// 链接到文件夹
	//	auto directory_new = Directory(directory_name, &current_directory, inode_id);
	auto directory_new = std::make_shared<Directory>(directory_name, current_directory, inode_id);
	// 加入文件夹
	//	directory_set.insert(directory_new);

	inode_set.insert(inode_new);
	current_directory->get_children_directories().insert(directory_new);

	return "success";
}

std::pair<std::vector<std::string>, std::vector<std::string>> FileSystem::list_names() const {
	std::vector<std::string> files;
	std::vector<std::string> directories;
	for (auto c : current_directory->get_children_files()) {
		files.push_back(c->get_file_name());
	}
	for (auto c : current_directory->get_children_directories()) {
		directories.push_back(c->get_name());
	}
	return std::make_pair(files, directories);
}

bool FileSystem::change_current_directory(const std::string& dir) {
	// 得到路径的一个vec
	auto directories = split_path(dir);
	// 上一个函数未解析的绝对地址的开头
	if (dir[0] == '/') {
		current_directory = root_directory;
	}
	// 递归处理
	change_dir(directories, 0, directories.size());
	return true;
}

void FileSystem::change_dir(const std::vector<std::string>& dir, const int count, const int count_size) {
	if (count == count_size) {
		return;
	}
	// dir的每个元素
	// 如果是上一个目录
	if (dir[count] == "..") {
		current_directory = current_directory->get_parent_directory();
	}
	else {
		// load directory by name
		auto directory_name = dir[count];
		auto directorys = current_directory->get_children_directories();
		auto dir_exits = std::find_if(directorys.begin(), directorys.end(), [directory_name](const std::shared_ptr<Directory> ddd) {
			                              return ddd->get_name() == directory_name;
		                              });
		if (dir_exits == directorys.end()) {
			return;
		}
		current_directory = *dir_exits;
	}
	change_dir(dir, count + 1, count_size);
}

bool FileSystem::change_password(const std::string& password) const {
	//检测密码合法性
	std::regex password_pattern("[A-Za-z0-9]{4,30}");
	if (!std::regex_match(password, password_pattern)) {
		return false;
	}
	// 设置密码
	current_user->set_password(password);
	return true;
}

bool FileSystem::change_mode(const std::string& filename, const std::string& authority) {
	if (!check_file_exist(filename)) {
		return false;
	}
	auto file = load_file_by_filename(filename);
	auto inode_id = file->get_inode_id();
	auto inode = load_inode_by_id(inode_id);
	inode->set_authority(authority);
	return true;
}

std::string FileSystem::change_file_user(const std::string& filename, const std::string& username) {
	// 不是root 用户无权操作
	if (current_user->get_username() != "root") {
		return "not_root";
	}

	// 查找用户是否存在
	auto user_exist = std::find_if(user_set.begin(), user_set.end(), [username](const std::shared_ptr<User>& user) {
		                               return user->get_username() == username;
	                               });
	if (user_exist == user_set.end()) {
		return "user_not_exist";
	}

	// 查找文件是否存在
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// 获取要更改的用户和文件
	auto user = *user_exist;
	auto file = *file_exist->get();

	auto file_inode = load_inode_by_id(file.get_inode_id());
	file_inode->set_username(user->get_username());
	return "success";
}

std::string FileSystem::change_file_group(const std::string& filename, const std::string& group_name) {
	// 不是root 用户无权操作
	if (current_user->get_username() != "root") {
		return "not_root";
	}

	// 查找文件是否存在
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// 查找组是否存在
	auto group_exist = std::find_if(group_set.begin(), group_set.end(), [group_name](const std::shared_ptr<Group>& group) {
		                                return group->get_group_name() == group_name;
	                                });
	if (group_exist == group_set.end()) {
		return "group_not_exist";
	}

	auto file = *file_exist->get();
	auto group = *group_exist;

	auto file_inode = load_inode_by_id(file.get_inode_id());
	file_inode->set_group_id(group->get_group_id());
	return "success";
}

std::string FileSystem::rename_file(const std::string& filename_old, const std::string& filename_new) const {
	// 找到文件
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename_old](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename_old;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// 检查新文件名字合法性
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件,14位
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// 如果文件名不合法
	if (!std::regex_match(filename_old, filename_pattern)) {
		return "filename_error";
	}

	auto file = *file_exist;
	file->set_file_name(filename_new);
	return "success";
}

std::string FileSystem::copy_file(const std::string& filename, const std::string& filename_newfile) {
	// 检查新文件名字合法性
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件,14位
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// 如果文件名不合法
	if (!std::regex_match(filename_newfile, filename_pattern)) {
		return "filename_error";
	}

	// 找到文件
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// 获取文件指针
	auto file = *file_exist;

	// TODO 假设生成的inode还是直接地址的

	// 获取inode并生成新inode
	auto inode = load_inode_by_id(file->get_inode_id());
	auto inode_new = std::make_shared<INode>(*inode);

	// 拷贝inode中的块
	for (auto i = 0; i < inode->get_file_address_array().size(); ++i) {
		auto block_tmp = inode->get_file_address_array()[i];

		// 如果捕获的array里面有内容的话，就从block_set的头部擦除空块来放入inode
		if (block_tmp != nullptr) {
			auto flag = block_set.begin();
			auto address = flag->get()->get_address();
			block_set.erase(flag);
			block_tmp->set_address(address);
			inode_new->get_file_address_array()[i] = block_tmp;
		}
	}

	// 设置新inode的id
	inode_new->set_id(static_cast<short>(inode_set.size() + 1));
	inode_set.insert(inode_new);

	auto file_new = std::make_shared<File>(*file);
	file_new->set_file_name(filename_newfile);
	current_directory->get_children_files().insert(file_new);
	return "success";
}

std::string FileSystem::remove_file(const std::string& filename) {
	// 先找到文件
	auto& files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	auto inode = load_inode_by_id((*file_exist)->get_inode_id());

	// 验证当前用户是否有权限
	// root用户拥有所有的权限
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}

	// 删除文件链接
	//	file_set.erase(*file_exist);
	files.erase(file_exist);
	// 删除文件

	std::vector<int> vec;
	for (auto c : inode->get_file_address_array()) {
		if (c != nullptr) {
			vec.push_back(c->get_address());
		}
	}
	for (auto c : vec) {
		block_set.insert(std::make_shared<Block>(c));
	}
	return "success";
}

// TODO rm -r command 递归删除
std::string FileSystem::remove_directory(const std::string& directory_name) {
	auto& directories = current_directory->get_children_directories();
	auto directory_exist = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> directory) {
		                                    return directory->get_name() == directory_name;
	                                    });
	// 如果文件夹不存在
	if (directory_exist == directories.end()) {
		return "directory_not_exist";
	}

	auto inode = load_inode_by_id((*directory_exist)->get_inode_id());

	// 验证当前用户是否有权限
	// root用户拥有所有的权限
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}

	return "success";
}

// 正儿八经的删除文件夹的递归函数
void FileSystem::delete_directory(const std::shared_ptr<Directory>& dir_pointer) {
	// 删除文件夹下的文件
	auto files = dir_pointer->get_children_files();
	for (auto i = files.begin(); i != files.end(); ++i) {
		auto name = (*i)->get_file_name();


	}
	//
	if (dir_pointer->get_children_directories().empty()) {

	}
}

std::string FileSystem::remove_empty_directory(const std::string& directory_name) {
	auto& directories = current_directory->get_children_directories();
	auto directory_exist = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> directory) {
		                                    return directory->get_name() == directory_name;
	                                    });
	// 如果文件夹不存在
	if (directory_exist == directories.end()) {
		return "directory_not_exist";
	}

	// 判断文件夹是否为空
	auto dir = *directory_exist;
	if (!dir->get_children_files().empty() || !dir->get_children_directories().empty()) {
		return "not_empty";
	}

	auto inode = load_inode_by_id(directory_exist->get()->get_inode_id());

	// 验证当前用户是否有权限
	// root用户拥有所有的权限
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}
	// 删除文件
	//	directory_set.erase(*directory_exist);
	//	directory_set.erase(*directory_exist);
	directories.erase(directory_exist);


	//	current_directory->get_children_directories().erase(directory_exist);

	std::vector<int> vec;
	for (auto c : inode->get_file_address_array()) {
		if (c != nullptr) {
			vec.push_back(c->get_address());
		}
	}
	for (auto c : vec) {
		block_set.insert(std::make_shared<Block>(c));
	}

	return "success";
}

std::string FileSystem::link_file(const std::string& filename, const std::string& link_name) {
	// 检查链接名字合法性
	// 文件名为14位的英文或数字或下划线或点，数字不能开头，点开头为隐藏文件,14位
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// 如果链接不合法
	if (!std::regex_match(link_name, filename_pattern)) {
		return "filename_error";
	}

	// 找到文件
	auto& files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// 获取文件引用
	auto file = *file_exist;
	// 获取文件的inode信息
	auto inode = load_inode_by_id(file->get_inode_id());
	// 增加inode的引用计数
	inode->add_count();
	auto link_file = std::make_shared<File>(*file);
	link_file->set_file_name(link_name);
	//	file_set.insert(link_file);
	current_directory->get_children_files().insert(link_file);

	return "success";
}

std::string FileSystem::display_file_context(const std::string& filename) {
	auto& files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}
	auto file = *file_exist;
	auto inode = load_inode_by_id(file->get_inode_id());
	auto blocks = inode->get_file_address_array();
	std::string result = "";

	for (const auto& c : blocks) {
		if (c != nullptr) {
			result += c->get_content();
		}
	}

	return result;
}

bool FileSystem::umask_command(const std::string& authority) {
	inode_authority = authority;
	return true;
}

std::string FileSystem::get_username() const {
	return current_user->get_username();
}

std::string FileSystem::list_file_details(const std::string& filename) {
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	auto directories = current_directory->get_children_directories();
	auto directory_exist = std::find_if(directories.begin(), directories.end(), [filename](const std::shared_ptr<Directory>& dir) {
		                                    return dir->get_name() == filename;
	                                    });
	std::shared_ptr<INode> inode = nullptr;
	std::string result;
	if (file_exist != files.end()) {
		auto file = *file_exist;
		inode = load_inode_by_id(file->get_inode_id());
		result = file->get_file_name();
	}
	else {
		if (directory_exist == directories.end()) {
			return "not_found";
		}
		else {
			// 
			auto directory = *directory_exist;
			inode = load_inode_by_id(directory->get_inode_id());
			result = directory->get_name();
		}
	}

	auto authority = inode->get_authority();
	std::array<std::string, 3> arr;
	arr[0] = authority.substr(0, 3);
	arr[1] = authority.substr(3, 3);
	arr[2] = authority.substr(6, 3);
	result += " ";
	for (const auto& c : arr) {
		if (c[0] == '1') {
			result += "r";
		}
		else {
			result += "-";
		}
		if (c[1] == '1') {
			result += "w";
		}
		else {
			result += "-";
		}
		if (c[2] == '1') {
			result += "x";
		}
		else {
			result += "-";
		}
	}

	result += " ";
	result += int_to_string(inode->get_count());
	result += " ";
	result += inode->get_username();
	result += " ";
	auto group = load_group_by_id(inode->get_group_id());
	result += group->get_group_name();
	result += " ";
	result += int_to_string(inode->get_size());
	result += " ";
	result += ctime(&(inode->get_last_modify_time()));

	return result;
}

std::vector<std::string> FileSystem::list_all_file_details() {
	auto files = current_directory->get_children_files();
	std::vector<std::string> result;
	for (auto i = files.begin(); i != files.end(); ++i) {
		auto str = list_file_details((*i)->get_file_name());
		result.push_back(str);
	}
	return result;
}

