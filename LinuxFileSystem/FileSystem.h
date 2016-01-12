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
	// ��¼�û�
	std::set<User> user_set;
	// ��¼���п�
	std::list<Block> block_list;
	// ��¼���е�inode
//	std::set<INode> inode_set;
	// ��Ŀ¼
	Directory root_directory;
	// ��ǰĿ¼
	// ���Դӵ�ǰĿ¼�ж�ȡFile��Ϣ����File�ж�ȡinode��Ϣ
	Directory current_directory;
	// ��ǰ��
	Group current_group;
	// ��ǰ�û�
	User current_user;
public:
	// ����û��Ƿ����
	bool check_username(std::string username);
	// ���û��Ѿ����ڵ�ǰ���¼�������Ƿ���ȷ
	bool check_password(std::string password) const;

	bool check_file_exist(std::string filename);

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
	* �������ļ�
	*/
	bool new_file(std::string filename);
};

inline bool FileSystem::check_username(std::string username)
{
	auto flag = std::find(user_set.begin(), user_set.end(), [username](const User &user_tmp) {return user_tmp.get_username() == username; });
	current_user = *flag;
	if (flag != user_set.end()) {
		return true;
	}
	return false;
}

inline bool FileSystem::check_password(std::string password) const {
	return current_user.get_password() == password;
}

inline bool FileSystem::check_file_exist(std::string filename) {
	// ���ҵ�ǰĿ¼�µ����ļ�
	auto files = current_directory.get_children_files();
	auto flag = std::find(files.begin(), files.end(), [filename](const File & file_tmp) {return file_tmp.get_file_name() == filename; });
	if (flag != files.end()) {
		return true;
	}
	return false;
}

inline std::string&& FileSystem::login(std::string username, std::string password)
{
	if (!check_username(username)) {
		return "user_not_exit";
	}
	if (!check_password(password)) {
		return "password_not_right";
	}
	return "success";
}

inline std::string&& FileSystem::user_register(std::string username, std::string password) {
	// �ҵ��˾���ʾ�û��Ѵ���
	if(check_username(username)) {
		return "user_already_exist";
	}
	// ����û����Ϸ��ԣ�ֻ��ΪӢ�Ĵ�Сд��ĸ�����֣�������Ӣ�Ŀ�ͷ�� �û���ֻ����30λ֮�䣩
	std::regex pattern("[A-Za-z]\\w{5,29}");
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
	User registed_user(username, password, current_group.get_group_id());
	user_set.insert(registed_user);
	return "success";
}

inline bool FileSystem::new_file(std::string filename) {
	if (check_file_exist(filename)) {
		return "file_already_exist";
	}
	// �ļ���Ϊ14λ��Ӣ�Ļ����ֻ��»��߻�㣬���ֲ��ܿ�ͷ���㿪ͷΪ�����ļ�,14λ
	std::regex filename_pattern("[A-Za-z_.]\\w{0.14}");
	// ����ļ������Ϸ�
	if (!std::regex_match(filename, filename_pattern)) {
		return "filename_error";
	}
	// �����ļ�
	
}
