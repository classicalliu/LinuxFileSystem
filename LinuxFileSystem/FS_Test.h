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
// ����ʹ�õ�
class FileSystem {
public:
	// �ļ�ϵͳ������
	std::string name;
	// �ļ�ϵͳ��С, Ĭ��200���飬ÿ��512B
	int size = BLOCK_COUNT * 512;
	//��¼������
	std::set<Group> group_set;
	// ��¼�û�
	std::set<User> user_set;
	// ��¼���п�
	std::set<std::shared_ptr<Block>> block_set;
	// ��¼���е�inode
	std::set<std::shared_ptr<INode>> inode_set;
	// ��¼���е�Ŀ¼��ʵ��
	std::set<std::shared_ptr<Directory>> directory_set;
	//��¼�����ļ���ʵ��
	std::set<std::shared_ptr<File>> file_set;
	// ��Ŀ¼
	Directory &root_directory = init_file::directory;
	//	std::shared_ptr<Directory> root_directory;
	// ��ǰĿ¼
	// ���Դӵ�ǰĿ¼�ж�ȡFile��Ϣ����File�ж�ȡinode��Ϣ
	Directory &current_directory = init_file::directory;
	//	std::shared_ptr<Directory> current_directory;
	// ��ǰ��
	Group &current_group = init_file::group;
	// ��ǰ�û�
	User &current_user = init_file::user;
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
	std::string&& user_register(std::string username, std::string password);

	/**
	* ���ݵ�ǰ�û���id�ҳ��û�
	*/
	const Group& load_group_by_id(const short id);
	File& load_file_by_filename(const std::string& filename) const;
	INode& load_inode_by_id(const short id);

	/**
	* �������ļ�
	*/
	std::string new_file(std::string filename);

	// �������ļ���
	std::string new_directory(std::string directory_name);

	// ls������ʾ��ǰ���ļ����ļ��е�����
	std::pair<std::vector<std::string>, std::vector<std::string>> ls_names() const;

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

};

inline FileSystem::FileSystem() : name("File_System") {
	init();
}

inline FileSystem::FileSystem(const std::string& name) : name(name) {
	init();
}

inline void FileSystem::init() {
	// ��ʼ��ϵͳӵ�е�Block�� 200����ÿ��512B
	for (auto i = 0; i < BLOCK_COUNT; ++i) {
		auto block_tmp = std::make_shared<Block>(i);
		block_set.insert(block_tmp);
	}
	// ����root��
	Group group(0, "root_group");
	group_set.insert(group);
	// ����root�û�
	User user("root", "root", 0);
	user_set.insert(user);

	// ����root�ļ��������inode
	auto directory_inode = std::make_shared<INode>(1, 100, 0, "root");
	// ���η��䣬���Է����һ���տ�
	directory_inode->get_file_address_array()[0] = *block_set.begin();
	inode_set.insert(directory_inode);

	// ����root�ļ���, root�ļ��еĸ�Ŀ¼��������
	auto directory_tmp = std::make_shared<Directory>("root", nullptr, 1);
	directory_tmp->set_parent_directory(directory_tmp.get());
	directory_set.insert(directory_tmp);
	// �л�rootĿ¼��currentĿ¼
	root_directory = *directory_tmp;
	current_directory = root_directory;

	// ���õ�ǰ��͵�ǰ�û�
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
	// ���ҵ�ǰĿ¼�µ����ļ�
	auto files = current_directory.get_children_files();
	auto flag = std::find_if(files.begin(), files.end(), [filename](const std::shared_ptr<File> & file_tmp) {return file_tmp->get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_directory_exist(std::string directory_name) const {
	// ���ҵ�ǰĿ¼�µ���Ŀ¼
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
