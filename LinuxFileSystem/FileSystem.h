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

//const int BLOCK_COUNT = 200;
namespace init_file {
	const int BLOCK_COUNT = 200;
}
//namespace init_file {
//	User user;
//	Group group;
//	Directory directory;
//}

//User a_user;
//Group a_group;
//Directory a_directory;

// ����ʹ�õ�
class FileSystem {
	// �ļ�ϵͳ������
	std::string name;
	// �ļ�ϵͳ��С, Ĭ��200���飬ÿ��512B
	int size = init_file::BLOCK_COUNT * 512;
	//��¼������
	std::set<std::shared_ptr<Group>> group_set;
	// ��¼�û�
	std::set<std::shared_ptr<User>> user_set;
	// ��¼���п�
	std::set<std::shared_ptr<Block>> block_set;
	// ��¼���е�inode
	std::set<std::shared_ptr<INode>> inode_set;
	// ��¼���е�Ŀ¼��ʵ��
	std::set<std::shared_ptr<Directory>> directory_set;
	//��¼�����ļ���ʵ��
	std::set<std::shared_ptr<File>> file_set;
	// ��Ŀ¼
	std::shared_ptr<Directory> root_directory;
	//	std::shared_ptr<Directory> root_directory;
	// ��ǰĿ¼
	// ���Դӵ�ǰĿ¼�ж�ȡFile��Ϣ����File�ж�ȡinode��Ϣ
	std::shared_ptr<Directory> current_directory;
	//	std::shared_ptr<Directory> current_directory;
	// ��ǰ��
	std::shared_ptr<Group> current_group;
	// ��ǰ�û�
	std::shared_ptr<User> current_user;
public:

	// ��ʼ��ϵͳ����

	FileSystem();


	FileSystem(const std::string& name);

	// ��ʼ�����е�����
	// ����rootĿ¼
	// �������еĿտ飬 200����ÿ��512B
	void init();

	// ����û��Ƿ����
	bool check_username(std::string username);
	// ���û��Ѿ����ڵ�ǰ���¼�������Ƿ���ȷ
	bool check_password(std::string password) const;
	// ����ļ��Ƿ��Ѿ�����
	bool check_file_exist(std::string filename) const;
	// ����ļ����Ƿ��Ѿ�����
	bool check_directory_exist(std::string directory_name) const;

	bool check_authority(std::string authority);

	static std::vector<std::string> split_path(const std::string &path);

	/**
	* �û���¼����
	* ���ȼ���û��Ƿ���ڣ������ھͷ��ش�����Ϣ
	* Ȼ�����û������Ƿ�ƥ�䣬��ƥ��ͷ��ش�����Ϣ
	* ���ͨ���򷵻سɹ���Ϣ
	*/
	std::string login(std::string username, std::string password);

	/**
	* �û�ע��
	* ����û����Ƿ���ڣ����ھͷ��ش�����Ϣ
	* ����û����Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* ��������Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* �����û���Ϣ����Ϊ��ǰ��
	* ����ע��ɹ���Ϣ
	*/
	std::string user_register(std::string username, std::string password);

	/**
	* ���ݵ�ǰ�û���id�ҳ��û�
	*/
	std::shared_ptr<Group> load_group_by_id(const short id);
	std::shared_ptr<File> load_file_by_filename(const std::string& filename) const;
	std::shared_ptr<INode> load_inode_by_id(const short id);

	/**
	* �������ļ�
	*/
	std::string new_file(std::string filename);

	// �������ļ���
	std::string new_directory(std::string directory_name);

	// ls������ʾ��ǰ���ļ����ļ��е�����
	std::pair<std::vector<std::string>, std::vector<std::string>> list_names() const;

	// �޸�����
	bool change_password(std::string password) const;

	// �޸��û�Ȩ�ޣ�����string ����777��ʾ�û����飬�����û�
	// ȷ���������һ����λ������
	// ��⹤������һ�����
	bool change_mode(std::string filename, std::string authority);

	// �޸��ļ��û�
	std::string change_file_user(std::string filename, std::string username);

	// �޸��ļ���
	std::string change_file_group(std::string filename, std::string group);
	// ��ʾ��ǰĿ¼
	std::string display_current_directory() const;
	// �ı䵱ǰĿ¼
	bool change_current_directory(std::string dir);
	void change_dir(std::vector<std::string> dir, int count, int count_size);

	// ɾ���ļ�
	std::string remove_file(std::string filename);

	// ɾ���ļ���rm -rf
	std::string remove_directory(std::string dirctory_name);
	// ɾ�����ļ��� rmdir
	std::string remove_empty_directory(std::string directory_name);

	// mv����������ļ�
	std::string rename_file(std::string filename_old, std::string filename_new) const;

	// cp ��������ļ�,���ļ������ļ�����ֻҪ���֣���Ҫ·������ʵ��
	std::string copy_file(std::string filename, std::string filename_newfile);

	// ln��������ļ�����
	std::string link_file(std::string filename, std::string link_name);

	//cat ����
	std::string display_file_context(std::string filename);

	static bool umask_command(const std::string& authority);

};

//
//inline FileSystem::FileSystem() : name("File_System") {
//	init();
//}
//
//inline FileSystem::FileSystem(const std::string& name) : name(name) {
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
//	auto group = std::make_shared<Group>(0, "root_group");
//	group_set.insert(group);
//	// ����root�û�
//	auto user = std::make_shared<User>("root", "root", 0);
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
//	directory_tmp->set_parent_directory(directory_tmp);
//	directory_set.insert(directory_tmp);
//	// �л�rootĿ¼��currentĿ¼
//	root_directory = directory_tmp;
//	current_directory = root_directory;
//
//	// ���õ�ǰ��͵�ǰ�û�
//	current_group = group;
//	current_user = user;
//	//	std::cout << "current_user = " << user.get_username() << std::endl;
//	//	std::cout << "current_group = " << group.get_group_id() << "  " << group.get_group_name() << std::endl;
//
//	//	std::cout << "init root directory name = " << root_directory->get_name() << std::endl;
//	//	system("pause");
//}
//
//inline bool FileSystem::check_username(std::string username)
//{
//	auto flag = std::find_if(user_set.begin(), user_set.end(), [username](const std::shared_ptr<User> &user_tmp) {return user_tmp->get_username() == username; });
//	if (flag != user_set.end()) {
//		current_user = *flag;
//		return true;
//	}
//	return false;
//}
//
//inline bool FileSystem::check_password(std::string password) const {
//	return current_user->get_password() == password;
//}
//
//inline bool FileSystem::check_file_exist(std::string filename) const {
//	// ���ҵ�ǰĿ¼�µ����ļ�
//	auto files = current_directory->get_children_files();
//	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file_tmp) {return file_tmp->get_file_name() == filename; });
//	if (flag != files.end()) {
//		return true;
//	}
//	return false;
//}
//
//inline bool FileSystem::check_directory_exist(std::string directory_name) const {
//	// ���ҵ�ǰĿ¼�µ���Ŀ¼
//	auto directories = current_directory->get_children_directories();
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
//inline std::shared_ptr<Group> FileSystem::load_group_by_id(const short id) {
//	auto flag = std::find_if(group_set.begin(), group_set.end(), [id](const std::shared_ptr<Group> &gp) {return gp->get_group_id() == id; });
//	return *flag;
//}
//
//inline std::shared_ptr<File> FileSystem::load_file_by_filename(const std::string& filename) const {
//	auto files = current_directory->get_children_files();
//	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File>& file) {return file->get_file_name() == filename; });
//	return *flag;
//}
//
//inline std::shared_ptr<INode> FileSystem::load_inode_by_id(const short id) {
//	auto flag = std::find_if(inode_set.begin(), inode_set.end(), [id](const std::shared_ptr<INode> &inode) {return inode->get_id() == id; });
//	return *flag;
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
//	short group_id = current_user->get_group_id();
//	current_group = load_group_by_id(group_id);
//
//	if (username != "root") {
//		auto directories = root_directory->get_children_directories();
//		auto user_directory = std::find_if(directories.begin(), directories.end(), [username](const std::shared_ptr<Directory> dir) {return dir->get_name() == username; });
//		current_directory = *user_directory;
//	}
//	else {
//		current_directory = root_directory;
//	}
//
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
//	std::regex password_pattern("[A-Za-z0-9]{4,30}");
//	if (!std::regex_match(password, password_pattern)) {
//		return "password_error";
//	}
//
//	// ����û����Ϸ��ʹ����û�,��Ϊ��ǰ��
//	auto registed_user = std::make_shared<User>(username, password, current_group->get_group_id());
//
//	//	User registed_user(username, password, current_group.get_group_id());
//	user_set.insert(registed_user);
//
//	current_user = registed_user;
//
//	// ����һ���û�Ŀ¼
//	auto inode_id = static_cast<short>(inode_set.size() + 1);
//	auto directory_inode = std::make_shared<INode>(inode_id, 100, current_group->get_group_id(), username);
//
//	inode_set.insert(directory_inode);
//
//	auto user_directory = std::make_shared<Directory>(username, root_directory.get(), inode_id);
//
//	directory_set.insert(user_directory);
//
//	root_directory->get_children_directories().insert(user_directory);
//
//	current_directory = user_directory;
//
//	return "success";
//}
//
//inline std::string FileSystem::display_current_directory() const {
//	std::vector<std::string> dir;
//	// ��ȡ��ǰĿ¼��ָ��
//	for (auto index = current_directory; index != root_directory; index = index->get_parent_directory()) {
//		dir.push_back(index->get_name());
//	}
//	std::string result = "/";
//	for (auto i = dir.rbegin(); i != dir.rend(); ++i) {
//		result += *i;
//		result += "/";
//	}
//	return result;
//}
//
//inline std::string FileSystem::new_file(std::string filename) {
//	if (check_file_exist(filename)) {
//		return "file_already_exist";
//	}
//	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
//	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
//	// ����ļ������Ϸ�
//	if (!std::regex_match(filename, filename_pattern)) {
//		return "filename_error";
//	}
//	// ����Ƿ��п��п�
//	if (block_set.empty()) {
//		return "no_space";
//	}
//	// �����ļ�
//	// ����inode
//	auto id_new = static_cast<short>(inode_set.size() + 1);
//	auto inode_new = std::make_shared<INode>();
//	//	INode inode_new;
//	inode_new->set_id(id_new);
//
//	// ��ȡ��һ�����п�
//	auto next_free_block = **block_set.begin();
//	// �ӿ��п��б���ɾ�������
//	block_set.erase(block_set.begin());
//	// ����ָ�������
//	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
//
//	// �����û���
//	inode_new->set_group_id(current_group->get_group_id());
//	// ��������޸�ʱ��
//	inode_new->set_last_modify_time(time(nullptr));
//	// ���ӵ��ļ�
//	auto file = std::make_shared<File>(filename, id_new);
//
//	// ����inode
//	inode_set.insert(inode_new);
//	file_set.insert(file);
//	// ���뵽��ǰĿ¼�µ��ļ��б���
//	current_directory->get_children_files().insert(file);
//
//	return "success";
//}
//
//inline std::string FileSystem::new_directory(std::string directory_name) {
//	// ����ļ����Ƿ��Ѵ���
//	if (check_directory_exist(directory_name)) {
//		return "directory_already_exist";
//	}
//	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ���,14λ
//	std::regex directory_pattern("[A-Za-z_.]\\w{0,14}");
//	// ����ļ��������Ϸ�
//	if (!std::regex_match(directory_name, directory_pattern)) {
//		return "directory_error";
//	}
//	// ����Ƿ��п��п�
//	if (block_set.empty()) {
//		return "no_space";
//	}
//	auto inode_id = static_cast<short>(inode_set.size() + 1);
//
//	auto next_free_block = **block_set.begin();
//	block_set.erase(block_set.begin());
//
//	// �����û���
//	// ��������޸�ʱ��
//	auto inode_new = std::make_shared<INode>(inode_id, 100, current_group->get_group_id(), current_user->get_username());
//	// ����ָ�������
//	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
//	// ���ӵ��ļ���
//	//	auto directory_new = Directory(directory_name, &current_directory, inode_id);
//	auto directory_new = std::make_shared<Directory>(directory_name, current_directory.get(), inode_id);
//	// �����ļ���
//	directory_set.insert(directory_new);
//
//	inode_set.insert(inode_new);
//	current_directory->get_children_directories().insert(directory_new);
//
//	return "success";
//}
//
//inline std::pair<std::vector<std::string>, std::vector<std::string>> FileSystem::list_names() const {
//	std::vector<std::string> files;
//	std::vector<std::string> directories;
//	for (auto c : current_directory->get_children_files()) {
//		files.push_back(c->get_file_name());
//	}
//	for (auto c : current_directory->get_children_directories()) {
//		directories.push_back(c->get_name());
//	}
//	return std::make_pair(files, directories);
//}
//
//inline bool FileSystem::change_current_directory(std::string dir) {
//	// �õ�·����һ��vec
//	auto directories = split_path(dir);
//	// ��һ������δ�����ľ��Ե�ַ�Ŀ�ͷ
//	if (dir[0] == '/') {
//		current_directory = root_directory;
//	}
//	// �ݹ鴦��
//	change_dir(directories, 0, directories.size());
//	return true;
//}
//
//inline void FileSystem::change_dir(std::vector<std::string> dir, int count, int count_size) {
//	if (count == count_size) {
//		return;
//	}
//	// dir��ÿ��Ԫ��
//	// �������һ��Ŀ¼
//	if (dir[count] == "..") {
//		current_directory = current_directory->get_parent_directory();
//	}
//	else {
//		// load directory by name
//		auto directory_name = dir[count];
//		auto directorys = current_directory->get_children_directories();
//		auto dir_exits = std::find_if(directorys.begin(), directorys.end(), [directory_name](const std::shared_ptr<Directory> ddd) {return ddd->get_name() == directory_name; });
//		if (dir_exits == directorys.end()) {
//			return;
//		}
//		current_directory = *dir_exits;
//	}
//	change_dir(dir, count + 1, count_size);
//}
//
//inline bool FileSystem::change_password(std::string password) const {
//	//�������Ϸ���
//	std::regex password_pattern("[A-Za-z0-9]{4,30}");
//	if (!std::regex_match(password, password_pattern)) {
//		return false;
//	}
//	// ��������
//	current_user->set_password(password);
//	return true;
//}
//
//inline bool FileSystem::change_mode(std::string filename, std::string authority) {
//	if (!check_file_exist(filename)) {
//		return false;
//	}
//	auto file = load_file_by_filename(filename);
//	auto inode_id = file->get_inode_id();
//	auto inode = load_inode_by_id(inode_id);
//	inode->set_authority(authority);
//	return true;
//}
//
//inline std::string FileSystem::change_file_user(std::string filename, std::string username) {
//	// ����root �û���Ȩ����
//	if (current_user->get_username() != "root") {
//		return "not_root";
//	}
//
//	// �����û��Ƿ����
//	auto user_exist = std::find_if(user_set.begin(), user_set.end(), [username](const std::shared_ptr<User> &user) {return user->get_username() == username; });
//	if (user_exist == user_set.end()) {
//		return "user_not_exist";
//	}
//
//	// �����ļ��Ƿ����
//	auto files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file) {return file->get_file_name() == filename; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	// ��ȡҪ���ĵ��û����ļ�
//	auto user = *user_exist;
//	auto file = *file_exist->get();
//
//	auto file_inode = load_inode_by_id(file.get_inode_id());
//	file_inode->set_username(user->get_username());
//	return "success";
//}
//
//inline std::string FileSystem::change_file_group(std::string filename, std::string group_name) {
//	// ����root �û���Ȩ����
//	if (current_user->get_username() != "root") {
//		return "not_root";
//	}
//
//	// �����ļ��Ƿ����
//	auto files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file) {return file->get_file_name() == filename; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	// �������Ƿ����
//	auto group_exist = std::find_if(group_set.begin(), group_set.end(), [group_name](const std::shared_ptr<Group> &group) {return group->get_group_name() == group_name; });
//	if (group_exist == group_set.end()) {
//		return "group_not_exist";
//	}
//
//	auto file = *file_exist->get();
//	auto group = *group_exist;
//
//	auto file_inode = load_inode_by_id(file.get_inode_id());
//	file_inode->set_group_id(group->get_group_id());
//	return "success";
//}
//
//inline std::string FileSystem::rename_file(std::string filename_old, std::string filename_new) const {
//	// �ҵ��ļ�
//	auto files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename_old](const std::shared_ptr<File> file) {return file->get_file_name() == filename_old; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	// ������ļ����ֺϷ���
//	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
//	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
//	// ����ļ������Ϸ�
//	if (!std::regex_match(filename_old, filename_pattern)) {
//		return "filename_error";
//	}
//
//	auto file = *file_exist;
//	file->set_file_name(filename_new);
//	return "success";
//}
//inline std::string FileSystem::copy_file(std::string filename, std::string filename_newfile) {
//	// ������ļ����ֺϷ���
//	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
//	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
//	// ����ļ������Ϸ�
//	if (!std::regex_match(filename_newfile, filename_pattern)) {
//		return "filename_error";
//	}
//
//	// �ҵ��ļ�
//	auto files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {return file->get_file_name() == filename; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	// ��ȡ�ļ�ָ��
//	auto file = *file_exist;
//
//	// TODO �������ɵ�inode����ֱ�ӵ�ַ��
//
//	// ��ȡinode��������inode
//	auto inode = load_inode_by_id(file->get_inode_id());
//	auto inode_new = std::make_shared<INode>(*inode);
//
//	// ����inode�еĿ�
//	for (auto i = 0; i < inode->get_file_address_array().size(); ++i) {
//		auto block_tmp = inode->get_file_address_array()[i];
//
//		// ��������array���������ݵĻ����ʹ�block_set��ͷ�������տ�������inode
//		if (block_tmp != nullptr) {
//			auto flag = block_set.begin();
//			auto address = flag->get()->get_address();
//			block_set.erase(flag);
//			block_tmp->set_address(address);
//			inode_new->get_file_address_array()[i] = block_tmp;
//		}
//	}
//
//	// ������inode��id
//	inode_new->set_id(static_cast<short>(inode_set.size() + 1));
//	inode_set.insert(inode_new);
//
//	auto file_new = std::make_shared<File>(*file);
//	file_new->set_file_name(filename_newfile);
//	current_directory->get_children_files().insert(file_new);
//	return "success";
//}
//
//inline std::string FileSystem::remove_file(std::string filename) {
//	// ���ҵ��ļ�
//	auto &files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> &file) {return file->get_file_name() == filename; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	auto inode = load_inode_by_id(file_exist->get()->get_inode_id());
//
//	// ��֤��ǰ�û��Ƿ���Ȩ��
//	// root�û�ӵ�����е�Ȩ��
//	if (current_user->get_username() != "root") {
//		auto authority = inode->get_authority();
//		if (authority[1] == '0') {
//			return "no_authority";
//		}
//	}
//
//	// ɾ���ļ�����
//	file_set.erase(*file_exist);
//	files.erase(file_exist);
//	// ɾ���ļ�
//
//	std::vector<int> vec;
//	for (auto c : inode->get_file_address_array()) {
//		if (c != nullptr) {
//			vec.push_back(c->get_address());
//		}
//	}
//	for (auto c : vec) {
//		block_set.insert(std::make_shared<Block>(c));
//	}
//	return "success";
//}
//
//inline std::string FileSystem::remove_empty_directory(std::string directory_name) {
//	auto &directories = current_directory->get_children_directories();
//	auto directory_exist = std::find_if(directories.begin(), directories.end(), [directory_name](const std::shared_ptr<Directory> directory) {return directory->get_name() == directory_name; });
//	// ����ļ��в�����
//	if (directory_exist == directories.end()) {
//		return "directory_not_exist";
//	}
//
//	// �ж��ļ����Ƿ�Ϊ��
//	auto dir = *directory_exist;
//	if (!dir->get_children_files().empty() || !dir->get_children_directories().empty()) {
//		return "not_empty";
//	}
//
//	auto inode = load_inode_by_id(directory_exist->get()->get_inode_id());
//
//	// ��֤��ǰ�û��Ƿ���Ȩ��
//	// root�û�ӵ�����е�Ȩ��
//	if (current_user->get_username() != "root") {
//		auto authority = inode->get_authority();
//		if (authority[1] == '0') {
//			return "no_authority";
//		}
//	}
//	// ɾ���ļ�
//	//	directory_set.erase(*directory_exist);
//	// TODO �޸�һ���������bug
//	directory_set.erase(*directory_exist);
//	directories.erase(directory_exist);
//
//
//
//	//	current_directory->get_children_directories().erase(directory_exist);
//
//	std::vector<int> vec;
//	for (auto c : inode->get_file_address_array()) {
//		if (c != nullptr) {
//			vec.push_back(c->get_address());
//		}
//	}
//	for (auto c : vec) {
//		block_set.insert(std::make_shared<Block>(c));
//	}
//
//	return "success";
//}
//
//inline std::string FileSystem::link_file(std::string filename, std::string link_name) {
//	// ����������ֺϷ���
//	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
//	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
//	// ������Ӳ��Ϸ�
//	if (!std::regex_match(link_name, filename_pattern)) {
//		return "filename_error";
//	}
//
//	// �ҵ��ļ�
//	auto &files = current_directory->get_children_files();
//	auto file_exist = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> file) {return file->get_file_name() == filename; });
//	if (file_exist == files.end()) {
//		return "file_not_exist";
//	}
//
//	// ��ȡ�ļ�����
//	auto file = *file_exist;
//	// ��ȡ�ļ���inode��Ϣ
//	auto inode = load_inode_by_id(file->get_inode_id());
//	// ����inode�����ü���
//	inode->add_count();
//	auto link_file = std::make_shared<File>(*file);
//	link_file->set_file_name(link_name);
//	file_set.insert(link_file);
//	current_directory->get_children_files().insert(link_file);
//
//	return "success";
//}


#endif
