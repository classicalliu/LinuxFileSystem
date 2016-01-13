#pragma once
#include <string>
#include <set>
#include "User.h"
#include "Block.h"
#include <regex>
#include "Group.h"
#include "Directory.h"

class FileSystem {

	// �ļ�ϵͳ������
	std::string name;
	// �ļ�ϵͳ��С, Ĭ��200���飬ÿ��512B
	int size = 200 * 512;
	//��¼������
	std::set<Group> group_set;
	// ��¼�û�
	std::set<User> user_set;
	// ��¼���п�
	std::list<Block> block_list;
	// ��¼���е�inode
	std::set<INode> inode_set;
	// ��Ŀ¼
	Directory &root_directory;
	// ��ǰĿ¼
	// ���Դӵ�ǰĿ¼�ж�ȡFile��Ϣ����File�ж�ȡinode��Ϣ
	Directory &current_directory;
	// ��ǰ��
	Group &current_group;
	// ��ǰ�û�
	User &current_user;
public:

	// ����û��Ƿ����
	bool check_username(std::string username);
	// ���û��Ѿ����ڵ�ǰ���¼�������Ƿ���ȷ
	bool check_password(std::string password) const;
	// ����ļ��Ƿ��Ѿ�����
	bool check_file_exist(std::string filename) const;
	// ����ļ����Ƿ��Ѿ�����
	bool check_directory_exist(std::string directory_name);

	/**
	* �û���¼����
	* ���ȼ���û��Ƿ���ڣ������ھͷ��ش�����Ϣ
	* Ȼ�����û������Ƿ�ƥ�䣬��ƥ��ͷ��ش�����Ϣ
	* ���ͨ���򷵻سɹ���Ϣ
	*/
	std::string&& login(std::string username, std::string password);

	/**
	* �û�ע��
	* ����û����Ƿ���ڣ����ھͷ��ش�����Ϣ
	* ����û����Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* ��������Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* �����û���Ϣ����Ϊ��ǰ��
	* ����ע��ɹ���Ϣ
	*/
	std::string&& user_register(std::string username, std::string password);

	/**
	* ���ݵ�ǰ�û���id�ҳ��û�
	*/
	const Group& load_group_by_id(const short id);
	const File& load_file_by_filename(const std::string& filename) const;
	const INode& load_inode_by_id(const short id);

	/**
	* �������ļ�
	*/
	bool new_file(std::string filename);

	// �������ļ���
	bool new_directory(std::string directory_name);

	// ls������ʾ��ǰ���ļ����ļ��е�����
	std::pair<std::vector<std::string>, std::vector<std::string>> ls_names();

	// �޸�����
	bool change_password(std::string password) const;

	// �޸��û�Ȩ�ޣ�����string ����777��ʾ�û����飬�����û�
	// ȷ���������һ����λ������
	// ��⹤������һ�����
	bool change_mode(std::string filename, std::string authority);

	// �޸��ļ��û�
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
	// ���ҵ�ǰĿ¼�µ����ļ�
	auto files = current_directory.get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const File & file_tmp) {return file_tmp.get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_directory_exist(std::string directory_name) {
	// ���ҵ�ǰĿ¼�µ���Ŀ¼
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
	// �ҵ��˾���ʾ�û��Ѵ���
	if(check_username(username)) {
		return "user_already_exist";
	}
	// ����û����Ϸ��ԣ�ֻ��ΪӢ�Ĵ�Сд��ĸ�����֣�������Ӣ�Ŀ�ͷ�� �û���ֻ����30λ֮�䣩
	std::regex pattern("[A-Za-z]\\w{3,29}");
	// ��ƥ��ͷ����û����Ƿ�
	if (!std::regex_match(username, pattern)) {
		return "username_error";
	}
	//�������Ϸ���
	std::regex password_pattern("[A-Za-z0-9]{6,30}");
	if(!std::regex_match(password, password_pattern)) {
		return "password_error";
	}
	// ����û����Ϸ��ʹ����û�,��Ϊ��ǰ��
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
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0,14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// ����Ƿ��п��п�
	if (block_list.empty()) {
		return false;
	}
	// �����ļ�
	// ����inode
	auto id_new = inode_set.size() + 1;
	auto inode_new = std::make_shared<INode>();
//	INode inode_new;
	inode_new->set_id(id_new);

	// ��ȡ��һ�����п�
	auto next_free_block = block_list.front();
	// �ӿ��п��б���ɾ�������
	block_list.erase(block_list.begin());
	// ����ָ�������
	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
	// �����û���
	inode_new->set_id(current_group.get_group_id());
	// ��������޸�ʱ��
	inode_new->set_last_modify_time(time(nullptr));
	// ���ӵ��ļ�
	auto file = std::make_shared<File>(filename, id_new);

	// ����inode
	inode_set.insert(*inode_new);
	// ���뵽��ǰĿ¼�µ��ļ��б���
	current_directory.get_children_files().insert(*file);

	return true;
}

inline bool FileSystem::new_directory(std::string directory_name) {
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
	if (block_list.empty()) {
		return false;
	}
	auto inode_id = inode_set.size() + 1;
	auto inode_new = std::make_shared<INode>();
	inode_new->set_id(inode_id);
	auto next_free_block = block_list.front();
	block_list.erase(block_list.begin());
	// ����ָ�������
	inode_new->get_file_address_array()[0] = std::make_shared<Block>(next_free_block);
	// �����û���
	inode_new->set_id(current_group.get_group_id());
	// ��������޸�ʱ��
	inode_new->set_last_modify_time(time(nullptr));
	// ���ӵ��ļ���
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
	//�������Ϸ���
	std::regex password_pattern("[A-Za-z0-9]{6,30}");
	if (!std::regex_match(password, password_pattern)) {
		return false;
	}
	// ��������
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
