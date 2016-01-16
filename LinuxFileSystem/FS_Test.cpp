//#include "FS_Test.h"
//
//User a_user;
//Group a_group;
//Directory a_directory;
//
//
//inline FileSystem::FileSystem() : name("File_System"), root_directory(a_directory), current_directory(a_directory), current_group(a_group), current_user(a_user){
//	init();
//}
//
//inline FileSystem::FileSystem(const std::string& name) : name(name) , root_directory(a_directory), current_directory(a_directory), current_group(a_group), current_user(a_user) {
//	init();
//}
//
//inline void FileSystem::init() {
//	// 初始化系统拥有的Block， 200个，每个512B
//	for (auto i = 0; i < BLOCK_COUNT; ++i) {
//		auto block_tmp = std::make_shared<Block>(i);
//		block_set.insert(block_tmp);
//	}
//	// 创建root组
//	Group group(0, "root_group");
//	group_set.insert(group);
//	// 创建root用户
//	User user("root", "root", 0);
//	user_set.insert(user);
//
//	// 分配root文件夹所需的inode
//	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
//	// 初次分配，所以分配第一个空块
//	directory_inode->get_file_address_array()[0] = *block_set.begin();
//	inode_set.insert(directory_inode);
//
//	// 生成root文件夹, root文件夹的父目录是其自身
//	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
//	directory_tmp->set_parent_directory(directory_tmp.get());
//	directory_set.insert(directory_tmp);
//	// 切换root目录和current目录
//	root_directory = *directory_tmp;
//	current_directory = root_directory;
//
//	// 设置当前组和当前用户
//	current_group = group;
//	current_user = user;
//	std::cout << "current_user = " << user.get_username() << std::endl;
//	std::cout << "current_group = " << group.get_group_id() << "  " << group.get_group_name() << std::endl;
//}
//
//inline bool FileSystem::check_username(std::string username)
//{
//	auto flag = std::find_if(user_set.begin(), user_set.end(), [username](const User &user_tmp) {return user_tmp.get_username() == username; });
//	if (flag != user_set.end()) {
//		current_user = *flag;
//		return true;
//	}
//	return false;
//}
//
//inline bool FileSystem::check_password(std::string password) const {
//	return current_user.get_password() == password;
//}
//
//inline bool FileSystem::check_file_exist(std::string filename) const {
//	// 查找当前目录下的子文件
//	auto files = current_directory.get_children_files();
//	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file_tmp) {return file_tmp->get_file_name() == filename; });
//	if (flag != files.end()) {
//		return true;
//	}
//	return false;
//}
//
//inline bool FileSystem::check_directory_exist(std::string directory_name) const {
//	// 查找当前目录下的子目录
//	auto directories = current_directory.get_children_directories();
//	auto flag = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> & dr) {return dr->get_name() == directory_name; });
//	if (flag == directories.end()) {
//		return false;
//	}
//	return true;
//}
//
//inline std::vector<std::string> FileSystem::split_path(const std::string& path) {
//	std::vector<std::string> result;
//	std::string c = "/";
//	std::string::size_type pos1, pos2;
//	pos2 = path.find(c);
//	pos1 = 0;
//	while (std::string::npos != pos2)
//	{
//		result.push_back(path.substr(pos1, pos2 - pos1));
//
//		pos1 = pos2 + c.size();
//		pos2 = path.find(c, pos1);
//	}
//	if (pos1 != path.length())
//		result.push_back(path.substr(pos1));
//
//	std::vector<std::string> result2;
//	for (const auto &tmp : result) {
//		if (tmp != "") {
//			result2.push_back(tmp);
//		}
//	}
//	return result2;
//}
//
//inline const Group& FileSystem::load_group_by_id(const short id) {
//	auto flag = std::find_if(group_set.begin(), group_set.end(), [id](const Group &gp) {return gp.get_group_id() == id; });
//	return *flag;
//}
//
//inline File& FileSystem::load_file_by_filename(const std::string& filename) const {
//	auto files = current_directory.get_children_files();
//	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {return file->get_file_name() == filename; });
//	return *flag->get();
//}
//
//inline INode& FileSystem::load_inode_by_id(const short id) {
//	auto flag = std::find_if(inode_set.begin(), inode_set.end(), [id](const std::shared_ptr<INode> &inode) {return inode->get_id() == id; });
//	return *flag->get();
//}
//
//inline std::string FileSystem::login(std::string username, std::string password)
//{
//	if (!check_username(username)) {
//		return "user_not_exist";
//	}
//	if (!check_password(password)) {
//		return "password_not_right";
//	}
//	short group_id = current_user.get_group_id();
//	current_group = load_group_by_id(group_id);
//	return "success";
//}
//
//inline std::string FileSystem::user_register(std::string username, std::string password) {
//	// 找到了就提示用户已存在
//	if (check_username(username)) {
//		return "user_already_exist";
//	}
//	// 检测用户名合法性（只能为英文大小写字母和数字，必须以英文开头， 用户名只能在30位之间）
//	std::regex pattern("[A-Za-z]\\w{3,29}");
//	// 不匹配就返回用户名非法
//	if (!std::regex_match(username, pattern)) {
//		return "username_error";
//	}
//	//检测密码合法性
//	std::regex password_pattern("[A-Za-z0-9]{6,30}");
//	if (!std::regex_match(password, password_pattern)) {
//		return "password_error";
//	}
//	// 如果用户名合法就创建用户,组为当前组
//	auto registed_user = std::make_shared<User>(username, password, current_group.get_group_id());
//	//	User registed_user(username, password, current_group.get_group_id());
//	user_set.insert(*registed_user);
//
//	current_user = *registed_user;
//
//	// 生成一个用户目录
//	auto inode_id = static_cast<short>(inode_set.size() + 1);
//	auto directory_inode = std::make_shared<INode>(inode_id, 100, current_group.get_group_id(), current_user.get_username());
//	auto user_directory = std::make_shared<Directory>(username, &root_directory, directory_inode->get_id());
//	current_directory = *user_directory;
//
//	return "success";
//}