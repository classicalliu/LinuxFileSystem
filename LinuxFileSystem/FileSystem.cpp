#include "FileSystem.h"

#include <sstream>


FileSystem::FileSystem() : name("File_System") {
	init();
}

FileSystem::FileSystem(const std::string& name) : name(name) {
	init();
}

void FileSystem::init() {
	// ��ʼ��ϵͳӵ�е�Block�� 200����ÿ��512B
	for (auto i = 0; i < init_file::BLOCK_COUNT; ++i) {
		auto block_tmp = std::make_shared<Block>(i);
		block_set.insert(block_tmp);
	}
	// ����root��
	auto group = std::make_shared<Group>(0, "root_group");
	group_set.insert(group);
	// ����root�û�
	auto user = std::make_shared<User>("root", "root", 0);
	user_set.insert(user);

	// ����root�ļ��������inode
	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
	// ���η��䣬���Է����һ���տ�
	directory_inode->get_file_address_array()[0] = *block_set.begin();
	inode_set.insert(directory_inode);

	// ����root�ļ���, root�ļ��еĸ�Ŀ¼��������
	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
	directory_tmp->set_parent_directory(directory_tmp);
	//	directory_set.insert(directory_tmp);
	// �л�rootĿ¼��currentĿ¼
	root_directory = directory_tmp;
	current_directory = root_directory;

	// ���õ�ǰ��͵�ǰ�û�
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
	// ���ҵ�ǰĿ¼�µ����ļ�
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
	// ���ҵ�ǰĿ¼�µ���Ŀ¼
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
	// �ҵ��˾���ʾ�û��Ѵ���
	if (check_username(username)) {
		return "user_already_exist";
	}
	// ����û����Ϸ��ԣ�ֻ��ΪӢ�Ĵ�Сд��ĸ�����֣�������Ӣ�Ŀ�ͷ�� �û���ֻ����30λ֮�䣩
	std::regex pattern("[A-Za-z]\\w{3,29}");
	// ��ƥ��ͷ����û����Ƿ�
	if (!std::regex_match(username, pattern)) {
		return "username_error";
	}
	//�������Ϸ���
	std::regex password_pattern("[A-Za-z0-9]{4,30}");
	if (!std::regex_match(password, password_pattern)) {
		return "password_error";
	}

	// ����û����Ϸ��ʹ����û�,��Ϊ��ǰ��
	auto registed_user = std::make_shared<User>(username, password, current_group->get_group_id());

	//	User registed_user(username, password, current_group.get_group_id());
	user_set.insert(registed_user);

	current_user = registed_user;

	// ����һ���û�Ŀ¼
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
	// ��ȡ��ǰĿ¼��ָ��
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
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// ����Ƿ��п��п�
	if (block_set.empty()) {
		return "no_space";
	}
	// �����ļ�
	// ����inode
	auto id_new = static_cast<short>(inode_set.size() + 1);
	auto inode_new = std::make_shared<INode>();
	//	INode inode_new;
	inode_new->set_id(id_new);

	// ��ȡ��һ�����п�
	auto next_free_block = *block_set.begin();
	// �ӿ��п��б���ɾ�������
	block_set.erase(block_set.begin());
	// ����ָ�������
	inode_new->get_file_address_array()[0] = next_free_block;

	// �����û���
	inode_new->set_group_id(current_group->get_group_id());
	// ��������޸�ʱ��
	inode_new->set_last_modify_time(time(nullptr));
	inode_new->set_size(100 + next_free_block->get_content().size());
	// ���ӵ��ļ�
	auto file = std::make_shared<File>(filename, id_new);

	// ����inode
	inode_set.insert(inode_new);
	//	file_set.insert(file);
	// ���뵽��ǰĿ¼�µ��ļ��б���
	current_directory->get_children_files().insert(file);

	return "success";
}

std::string FileSystem::new_file_with_content(const std::string& filename, const std::string& content) {
	if (check_file_exist(filename)) {
		return "file_already_exist";
	}
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// ����Ƿ��п��п�
	if (block_set.empty()) {
		return "no_space";
	}
	// �����ļ�
	// ����inode
	auto id_new = static_cast<short>(inode_set.size() + 1);
	auto inode_new = std::make_shared<INode>();
	//	INode inode_new;
	inode_new->set_id(id_new);

	// ��ȡ��һ�����п�
	auto next_free_block = *block_set.begin();
	next_free_block->set_content(content);
	// �ӿ��п��б���ɾ�������
	block_set.erase(block_set.begin());
	// ����ָ�������
	inode_new->get_file_address_array()[0] = next_free_block;

	// �����û���
	inode_new->set_group_id(current_group->get_group_id());
	inode_new->set_size(100 + content.size());
	// ��������޸�ʱ��
	inode_new->set_last_modify_time(time(nullptr));
	// ���ӵ��ļ�
	auto file = std::make_shared<File>(filename, id_new);

	// ����inode
	inode_set.insert(inode_new);
	//	file_set.insert(file);
	// ���뵽��ǰĿ¼�µ��ļ��б���
	current_directory->get_children_files().insert(file);

	return "success";
}

std::string FileSystem::new_directory(const std::string& directory_name) {
	// ����ļ����Ƿ��Ѵ���
	if (check_directory_exist(directory_name)) {
		return "directory_already_exist";
	}
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ���,14λ
	std::regex directory_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ��������Ϸ�
	if (!std::regex_match(directory_name, directory_pattern)) {
		return "directory_error";
	}
	// ����Ƿ��п��п�
	if (block_set.empty()) {
		return "no_space";
	}
	auto inode_id = static_cast<short>(inode_set.size() + 1);

	auto next_free_block = *block_set.begin();
	block_set.erase(block_set.begin());

	// �����û���
	auto inode_new = std::make_shared<INode>(inode_id, 100, current_group->get_group_id(), current_user->get_username());
	// ����ָ�������
	inode_new->get_file_address_array()[0] = next_free_block;
	// ���ӵ��ļ���
	//	auto directory_new = Directory(directory_name, &current_directory, inode_id);
	auto directory_new = std::make_shared<Directory>(directory_name, current_directory, inode_id);
	// �����ļ���
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
	// �õ�·����һ��vec
	auto directories = split_path(dir);
	// ��һ������δ�����ľ��Ե�ַ�Ŀ�ͷ
	if (dir[0] == '/') {
		current_directory = root_directory;
	}
	// �ݹ鴦��
	change_dir(directories, 0, directories.size());
	return true;
}

void FileSystem::change_dir(const std::vector<std::string>& dir, const int count, const int count_size) {
	if (count == count_size) {
		return;
	}
	// dir��ÿ��Ԫ��
	// �������һ��Ŀ¼
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
	//�������Ϸ���
	std::regex password_pattern("[A-Za-z0-9]{4,30}");
	if (!std::regex_match(password, password_pattern)) {
		return false;
	}
	// ��������
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
	// ����root �û���Ȩ����
	if (current_user->get_username() != "root") {
		return "not_root";
	}

	// �����û��Ƿ����
	auto user_exist = std::find_if(user_set.begin(), user_set.end(), [username](const std::shared_ptr<User>& user) {
		                               return user->get_username() == username;
	                               });
	if (user_exist == user_set.end()) {
		return "user_not_exist";
	}

	// �����ļ��Ƿ����
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// ��ȡҪ���ĵ��û����ļ�
	auto user = *user_exist;
	auto file = *file_exist->get();

	auto file_inode = load_inode_by_id(file.get_inode_id());
	file_inode->set_username(user->get_username());
	return "success";
}

std::string FileSystem::change_file_group(const std::string& filename, const std::string& group_name) {
	// ����root �û���Ȩ����
	if (current_user->get_username() != "root") {
		return "not_root";
	}

	// �����ļ��Ƿ����
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// �������Ƿ����
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
	// �ҵ��ļ�
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename_old](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename_old;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// ������ļ����ֺϷ���
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename_old, filename_pattern)) {
		return "filename_error";
	}

	auto file = *file_exist;
	file->set_file_name(filename_new);
	return "success";
}

std::string FileSystem::copy_file(const std::string& filename, const std::string& filename_newfile) {
	// ������ļ����ֺϷ���
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename_newfile, filename_pattern)) {
		return "filename_error";
	}

	// �ҵ��ļ�
	auto files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// ��ȡ�ļ�ָ��
	auto file = *file_exist;

	// TODO �������ɵ�inode����ֱ�ӵ�ַ��

	// ��ȡinode��������inode
	auto inode = load_inode_by_id(file->get_inode_id());
	auto inode_new = std::make_shared<INode>(*inode);

	// ����inode�еĿ�
	for (auto i = 0; i < inode->get_file_address_array().size(); ++i) {
		auto block_tmp = inode->get_file_address_array()[i];

		// ��������array���������ݵĻ����ʹ�block_set��ͷ�������տ�������inode
		if (block_tmp != nullptr) {
			auto flag = block_set.begin();
			auto address = flag->get()->get_address();
			block_set.erase(flag);
			block_tmp->set_address(address);
			inode_new->get_file_address_array()[i] = block_tmp;
		}
	}

	// ������inode��id
	inode_new->set_id(static_cast<short>(inode_set.size() + 1));
	inode_set.insert(inode_new);

	auto file_new = std::make_shared<File>(*file);
	file_new->set_file_name(filename_newfile);
	current_directory->get_children_files().insert(file_new);
	return "success";
}

std::string FileSystem::remove_file(const std::string& filename) {
	// ���ҵ��ļ�
	auto& files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	auto inode = load_inode_by_id((*file_exist)->get_inode_id());

	// ��֤��ǰ�û��Ƿ���Ȩ��
	// root�û�ӵ�����е�Ȩ��
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}

	// ɾ���ļ�����
	//	file_set.erase(*file_exist);
	files.erase(file_exist);
	// ɾ���ļ�

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

// TODO rm -r command �ݹ�ɾ��
std::string FileSystem::remove_directory(const std::string& directory_name) {
	auto& directories = current_directory->get_children_directories();
	auto directory_exist = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> directory) {
		                                    return directory->get_name() == directory_name;
	                                    });
	// ����ļ��в�����
	if (directory_exist == directories.end()) {
		return "directory_not_exist";
	}

	auto inode = load_inode_by_id((*directory_exist)->get_inode_id());

	// ��֤��ǰ�û��Ƿ���Ȩ��
	// root�û�ӵ�����е�Ȩ��
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}

	return "success";
}

// �����˾���ɾ���ļ��еĵݹ麯��
void FileSystem::delete_directory(const std::shared_ptr<Directory>& dir_pointer) {
	// ɾ���ļ����µ��ļ�
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
	// ����ļ��в�����
	if (directory_exist == directories.end()) {
		return "directory_not_exist";
	}

	// �ж��ļ����Ƿ�Ϊ��
	auto dir = *directory_exist;
	if (!dir->get_children_files().empty() || !dir->get_children_directories().empty()) {
		return "not_empty";
	}

	auto inode = load_inode_by_id(directory_exist->get()->get_inode_id());

	// ��֤��ǰ�û��Ƿ���Ȩ��
	// root�û�ӵ�����е�Ȩ��
	if (current_user->get_username() != "root") {
		auto authority = inode->get_authority();
		if (authority[1] == '0') {
			return "no_authority";
		}
	}
	// ɾ���ļ�
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
	// ����������ֺϷ���
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ������Ӳ��Ϸ�
	if (!std::regex_match(link_name, filename_pattern)) {
		return "filename_error";
	}

	// �ҵ��ļ�
	auto& files = current_directory->get_children_files();
	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {
		                               return file->get_file_name() == filename;
	                               });
	if (file_exist == files.end()) {
		return "file_not_exist";
	}

	// ��ȡ�ļ�����
	auto file = *file_exist;
	// ��ȡ�ļ���inode��Ϣ
	auto inode = load_inode_by_id(file->get_inode_id());
	// ����inode�����ü���
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

