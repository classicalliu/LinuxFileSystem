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
//	// ��ʼ��ϵͳӵ�е�Block�� 200����ÿ��512B
//	for (auto i = 0; i < BLOCK_COUNT; ++i) {
//		auto block_tmp = std::make_shared<Block>(i);
//		block_set.insert(block_tmp);
//	}
//	// ����root��
//	Group group(0, "root_group");
//	group_set.insert(group);
//	// ����root�û�
//	User user("root", "root", 0);
//	user_set.insert(user);
//
//	// ����root�ļ��������inode
//	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
//	// ���η��䣬���Է����һ���տ�
//	directory_inode->get_file_address_array()[0] = *block_set.begin();
//	inode_set.insert(directory_inode);
//
//	// ����root�ļ���, root�ļ��еĸ�Ŀ¼��������
//	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
//	directory_tmp->set_parent_directory(directory_tmp.get());
//	directory_set.insert(directory_tmp);
//	// �л�rootĿ¼��currentĿ¼
//	root_directory = *directory_tmp;
//	current_directory = root_directory;
//
//	// ���õ�ǰ��͵�ǰ�û�
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
//	// ���ҵ�ǰĿ¼�µ����ļ�
//	auto files = current_directory.get_children_files();
//	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file_tmp) {return file_tmp->get_file_name() == filename; });
//	if (flag != files.end()) {
//		return true;
//	}
//	return false;
//}
//
//inline bool FileSystem::check_directory_exist(std::string directory_name) const {
//	// ���ҵ�ǰĿ¼�µ���Ŀ¼
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
//	// �ҵ��˾���ʾ�û��Ѵ���
//	if (check_username(username)) {
//		return "user_already_exist";
//	}
//	// ����û����Ϸ��ԣ�ֻ��ΪӢ�Ĵ�Сд��ĸ�����֣�������Ӣ�Ŀ�ͷ�� �û���ֻ����30λ֮�䣩
//	std::regex pattern("[A-Za-z]\\w{3,29}");
//	// ��ƥ��ͷ����û����Ƿ�
//	if (!std::regex_match(username, pattern)) {
//		return "username_error";
//	}
//	//�������Ϸ���
//	std::regex password_pattern("[A-Za-z0-9]{6,30}");
//	if (!std::regex_match(password, password_pattern)) {
//		return "password_error";
//	}
//	// ����û����Ϸ��ʹ����û�,��Ϊ��ǰ��
//	auto registed_user = std::make_shared<User>(username, password, current_group.get_group_id());
//	//	User registed_user(username, password, current_group.get_group_id());
//	user_set.insert(*registed_user);
//
//	current_user = *registed_user;
//
//	// ����һ���û�Ŀ¼
//	auto inode_id = static_cast<short>(inode_set.size() + 1);
//	auto directory_inode = std::make_shared<INode>(inode_id, 100, current_group.get_group_id(), current_user.get_username());
//	auto user_directory = std::make_shared<Directory>(username, &root_directory, directory_inode->get_id());
//	current_directory = *user_directory;
//
//	return "success";
//}