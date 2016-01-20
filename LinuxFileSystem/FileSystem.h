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

// ����ʹ�õ�
class FileSystem {
	// �ļ�ϵͳ������
	std::string name;
	// �ļ�ϵͳ��С, Ĭ��200���飬ÿ��512B
	int size = init_file::BLOCK_COUNT * init_file::BLOCK_SIZE;
	//��¼������
	std::set<std::shared_ptr<Group>> group_set;
	// ��¼�û�
	std::set<std::shared_ptr<User>> user_set;
	// ��¼���п�
	std::set<std::shared_ptr<Block>> block_set;
	// ��¼���е�inode
	std::set<std::shared_ptr<INode>> inode_set;
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
	bool check_username(const std::string& username);
	// ���û��Ѿ����ڵ�ǰ���¼�������Ƿ���ȷ
	bool check_password(const std::string& password) const;
	// ����ļ��Ƿ��Ѿ�����
	bool check_file_exist(const std::string& filename) const;
	// ����ļ����Ƿ��Ѿ�����
	bool check_directory_exist(const std::string& directory_name) const;

//	bool check_authority(const std::string& authority);

	static std::vector<std::string> split_path(const std::string &path);

	// int to string
	static std::string int_to_string(const int num);

	/**
	* �û���¼����
	* ���ȼ���û��Ƿ���ڣ������ھͷ��ش�����Ϣ
	* Ȼ�����û������Ƿ�ƥ�䣬��ƥ��ͷ��ش�����Ϣ
	* ���ͨ���򷵻سɹ���Ϣ
	*/
	std::string login(const std::string& username, const std::string& password);

	/**
	* �û�ע��
	* ����û����Ƿ���ڣ����ھͷ��ش�����Ϣ
	* ����û����Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* ��������Ƿ�Ϸ������Ϸ��ͷ��ش�����Ϣ
	* �����û���Ϣ����Ϊ��ǰ��
	* ����ע��ɹ���Ϣ
	*/
	std::string user_register(const std::string& username, const std::string& password);

	/**
	* ���ݵ�ǰ�û���id�ҳ��û�
	*/
	std::shared_ptr<Group> load_group_by_id(const short id);
	std::shared_ptr<File> load_file_by_filename(const std::string& filename) const;
	std::shared_ptr<INode> load_inode_by_id(const short id);

	/**
	* �������ļ�
	*/
	std::string new_file(const std::string& filename);
	// vi command
	std::string new_file_with_content(const std::string& filename, const std::string& content);

	// �������ļ���
	std::string new_directory(const std::string& directory_name);

	// ls������ʾ��ǰ���ļ����ļ��е�����
	std::pair<std::vector<std::string>, std::vector<std::string>> list_names() const;

	// �޸�����
	bool change_password(const std::string& password) const;

	// �޸��û�Ȩ�ޣ�����string ����777��ʾ�û����飬�����û�
	// ȷ���������һ����λ������
	// ��⹤������һ�����
	bool change_mode(const std::string& filename, const std::string& authority);

	// �޸��ļ��û�
	std::string change_file_user(const std::string& filename, const std::string& username);

	// �޸��ļ���
	std::string change_file_group(const std::string& filename, const std::string& group);
	// ��ʾ��ǰĿ¼
	std::string display_current_directory() const;
	// �ı䵱ǰĿ¼
	bool change_current_directory(const std::string& dir);
	void change_dir(const std::vector<std::string>& dir, const int count, const int count_size);

	// ɾ���ļ�
	std::string remove_file(const std::string& filename);

	// ɾ���ļ���rm -r
	std::string remove_directory(const std::string& dirctory_name);
	void delete_directory(const std::shared_ptr<Directory>& dir_pointer);
	// ɾ�����ļ��� rmdir
	std::string remove_empty_directory(const std::string& directory_name);

	// mv����������ļ�
	std::string rename_file(const std::string& filename_old, const std::string& filename_new) const;

	// cp ��������ļ�,���ļ������ļ�����ֻҪ���֣���Ҫ·������ʵ��
	std::string copy_file(const std::string& filename, const std::string& filename_newfile);

	// ln��������ļ�����
	std::string link_file(const std::string& filename, const std::string& link_name);

	//cat ����
	std::string display_file_context(const std::string& filename);

	static bool umask_command(const std::string& authority);

	std::string get_username() const;

	std::string list_file_details(const std::string &filename);
	std::vector<std::string> list_all_file_details();

};


#endif
