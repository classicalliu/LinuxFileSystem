#include "Shell.h"
#include "SetColor.h"
#include <iostream>
#include <chrono>
#include <thread>


Shell::Shell()
{
}


Shell::~Shell()
{
}

void Shell::pause() {
	system("pause");
}

void Shell::clear_screen() {
	system("cls");
}

void Shell::exit_process() {
	exit(0);
}

void Shell::trim(std::string& str) {
	if (str.empty()) {
		return;
	}
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
}

void Shell::sleep_second(const double second) {
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(1000 * second)));
}

std::vector<std::string> Shell::split_command(const std::string& command) {
	std::vector<std::string> result;
	std::string c = " ";
	std::string::size_type pos1, pos2;
	pos2 = command.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		result.push_back(command.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = command.find(c, pos1);
	}
	if (pos1 != command.length())
		result.push_back(command.substr(pos1));

	std::vector<std::string> result2;
	for (const auto &tmp : result) {
		if (tmp != "") {
			result2.push_back(tmp);
		}
	}
	return result2;
}

void Shell::show_path() const {
	set_command();
	auto path = file_system.display_current_directory();
	auto username = file_system.get_username();
	std::string symbol = " $ ";
	if (username == "root") {
		symbol = " # ";
	}
	std::cout << "                  " << username << " @ " << path << symbol;
	set_white();
}

void Shell::hello_window() {
	clear_screen();
	set_white();
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  *                                          *" << std::endl;
	std::cout << "                  *                ��(�R�ڨQ)��              *" << std::endl;
	std::cout << "                  *            ��ӭʹ��XXX�ļ�ϵͳ           *" << std::endl;
	std::cout << "                  *                                          *" << std::endl;
	std::cout << "                  ********************************************" << std::endl;
	sleep_second(1.5);
	start();
}

void Shell::error() {
	clear_screen();
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  *                ��������                   " << std::endl;
	std::cout << "                  *                1. ����                    " << std::endl;
	std::cout << "                  *                2. �˳�                    " << std::endl;
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                                     ��ѡ��:  ";
	std::string command;
	std::cin >> command;
	if (command == "1") {
		start();
	} else if (command == "2") {
		exit_process();
	} else {
		error();
	}
}

void Shell::help() {
	clear_screen();
	set_yellow_high();
	std::cout << "                         �����ļ�" << std::endl;
	std::cout << "                       �����ʽ˵��" << std::endl;
	set_white();
	std::cout << " 1. ls                      -->   �г���ǰĿ¼�е���Ŀ¼���ļ�" << std::endl;
	std::cout << " 2. chmod xxx               -->   xxxΪ1-7֮������֣���ʾ�û�Ȩ��" << std::endl;
	std::cout << " 3. chgrp <name>            -->   �ı䵱ǰ�ļ���Ŀ¼" << std::endl;
	std::cout << " 4. psw                     -->   ��ʾ��ǰĿ¼" << std::endl;
	std::cout << " 5. cd <name>               -->   ��ת��Ŀ¼<name>�� ..��ʾ�ϲ�Ŀ¼��/��ʾ��Ŀ¼��~��ʾhomeĿ¼" << std::endl;
	std::cout << " 6. mkdir <name>            -->   �ڵ�ǰĿ¼�´�����Ŀ¼" << std::endl;
	std::cout << " 7. rmdir <name>            -->   ɾ����Ŀ¼<name>" << std::endl;
	std::cout << " 8. umask <name>            -->   �����ļ�������" << std::endl;
	std::cout << " 9. mv <source> <target>    -->   ���ļ���<source>�ƶ���<target>" << std::endl;
	std::cout << "10. cp <source> <target>    -->   ���ļ���<source>�ƶ���<target>" << std::endl;
	std::cout << "11. rm <name>               -->   ɾ���ļ���Ϊ<name>���ļ�" << std::endl;
	std::cout << "12. ln <source>             -->   ���ļ���<source>���ӵ���ǰ�ļ���" << std::endl;
	std::cout << "13. cat <name1> <name2> ... -->   ������ʾ�ļ�����" << std::endl;
	std::cout << "14. passwd                  -->   �޸ĵ�ǰ�û�����" << std::endl;
	std::cout << "15. help                    -->   ��ʾ�����ļ�" << std::endl;
	std::cout << "16. exit                    -->   �˳���ǰϵͳ" << std::endl;
	pause();
	main_window();
}

void Shell::start() {
	clear_screen();
	//	set_magenta();
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  *                1. �û���¼                " << std::endl;
	std::cout << "                  *                2. �û�ע��                " << std::endl;
	std::cout << "                  ********************************************" << std::endl;
	//	set_white();

	std::string choice;
	std::cout << "                                     ��ѡ��:  ";
	std::cin >> choice;
	trim(choice);

	if (choice == "1") {
		clear_screen();
		user_login();
	} else if (choice == "2") {
		clear_screen();
		user_register();
	} else {
		error();
		std::cin >> choice;
		trim(choice);
		if (choice == "1") {
			start();
		} else {
			exit_process();
		}
	}

}

void Shell::user_login() {
	clear_screen();
	std::string username;
	std::string password;
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                                   �������û�����              " << std::endl;
	std::cout << "                                   ";
	std::cin >> username;

	std::cout << "                                   ���������룺              " << std::endl;
	std::cout << "                                   ";
	std::cin >> password;
	auto result = file_system.login(username, password);
	
	std::cout << "\n\n\n";
	if (result == "user_not_exist") {
		set_red_high();
		std::cout << "                                   �û������ڣ�              " << std::endl;
		set_white();
		std::cout << "                  ********************************************" << std::endl;
		sleep_second(1.5);
		user_login();
	} else if (result == "password_not_right") {
		set_red_high();
		std::cout << "                                   �������              " << std::endl;
		set_white();
		std::cout << "                  ********************************************" << std::endl;
		sleep_second(1.5);
		user_login();
	} else {
		// result == "success"
		std::cout << "                                   ��¼�ɹ���              " << std::endl;
		set_white();
		std::cout << "                  ********************************************" << std::endl;
		sleep_second(1.5);
		main_window();
	}


	clear_screen();
}

void Shell::user_register() {
	clear_screen();
	std::string username;
	std::string password;
	std::string password2;
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                                   �������û�����              " << std::endl;
	std::cout << "                                   ";
	std::cin >> username;

	std::cout << "                                   ���������룺              " << std::endl;
	std::cout << "                                   ";
	std::cin >> password;

	std::cout << "                                  ���ٴ��������룺              " << std::endl;
	std::cout << "                                   ";
	std::cin >> password2;
	if (password != password2) {
		clear_screen();

		std::cout << "\n\n\n";
		std::cout << "                  ********************************************" << std::endl;
		set_red_high();
		std::cout << "                                   ���벻һ�£�              " << std::endl;
		set_white();
		std::cout << "                  ********************************************" << std::endl;

		pause();
		user_register();
		return;
	}
	auto result = file_system.user_register(username, password);
	clear_screen();
	if (result == "user_already_exist") {
		clear_screen();
		set_red_high();
		std::cout << "\n\n\n";
		std::cout << "                  ********************************************" << std::endl;
		std::cout << "                  *                �û��Ѵ���                 " << std::endl;
		std::cout << "                  ********************************************" << std::endl;
		set_white();
		pause();
		user_register();
	} else if (result == "username_error") {
		clear_screen();
		set_red_high();
		std::cout << "\n\n\n";
		std::cout << "                  ********************************************" << std::endl;
		std::cout << "                  *                �û�����������             " << std::endl;
		std::cout << "                  ********************************************" << std::endl;
		set_white();
		pause();
		user_register();
	} else if (result == "password_error") {
		clear_screen();
		set_red_high();
		std::cout << "\n\n\n";
		std::cout << "                  ********************************************" << std::endl;
		std::cout << "                  *                ������������               " << std::endl;
		std::cout << "                  ********************************************" << std::endl;
		set_white();
		pause();
		user_register();
	} else {
		clear_screen();
		set_yellow_high();
		std::cout << "\n\n\n";
		std::cout << "                  ********************************************" << std::endl;
		std::cout << "                  *                  ע��ɹ�                 " << std::endl;
		std::cout << "                  ********************************************" << std::endl;
		set_white();
		sleep_second(1.5);
		// TODO ������һ��
		start();
	}
}

void Shell::main_window() {
	clear_screen();
	std::cout << "\n\n\n";
	set_yellow_high();
	std::cout << "                       ��ӭʹ��ɽկ�ļ�ϵͳ_(:�٩f��)_" << std::endl;
	set_white();
	std::cout << "                  ********************************************" << std::endl;
	sub_window();
}

void Shell::sub_window() {
	show_path();
//	std::string command;
	//	std::cin >> commond;
//	getchar();
//	getline(std::cin, command);
	std::string command1 = "", command2 = "", command3 = "";
//	set_command();
	std::cin >> command1;
//	set_white();

//	auto command_vec = split_command(command);
//	if (command_vec[0] == "mk") {
//		mk_command(command_vec[1]);
//	} else if (command_vec[0] == "ls") {
//		ls_command();
//	}

	if (command1 == "mk") {
		std::cin >> command2;
		mk_command(command2);
	}  else if (command1 == "ls") {
		if (std::cin >> command2 && command2 == "-l") {
			if (std::cin >> command3) {
				ls_l_file_command(command3);
			} else {
				ls_l_command();
			}
		} else {
			ls_command();
		}
	} else if (command1 == "mkdir") {
		std::cin >> command2;
		mkdir_command(command2);
	} else if (command1 == "cd") {
		std::cin >> command2;
		cd_command(command2);
	} else if (command1 == "passwd") {
		passwd_command();
	} else if (command1 == "exit") {
		exit_command();
	} else if (command1 == "chmod") {
		int command4;
		std::cin >> command2 >> command4;
		chmod_command(command2, command4);
	} else if (command1 == "pwd") {
		pwd_command();
	} else if (command1 == "chown") {
		std::cin >> command2 >> command3;
		chown_command(command2, command3);
	} else if (command1 == "chgrp") {
		std::cin >> command2 >> command3;
		chgrp_command(command2, command3);
	} else if (command1 == "mv") {
		std::cin >> command2 >> command3;
		mv_command(command2, command3);
	} else if (command1 == "cp") {
		std::cin >> command2 >> command3;
		cp_command(command2, command3);
	} else if (command1 == "rm") {
		std::cin >> command2;
		rm_command(command2);
	} else if (command1 == "rmdir") {
		std::cin >> command2;
		rmdir_command(command2);
	} else if (command1 == "ln") {
		std::cin >> command2 >> command3;
		ln_command(command2, command3);
	} else if (command1 == "help") {
		help();
	} else if (command1 == "cat") {
		std::cin >> command2 >> command3;
		cat_command(command2, command3);
	} else if (command1 == "umask") {
		int command4;
		std::cin >> command4;
		umask_command(command4);
	} else if (command1 == "vi") {
		// command2 ���ļ���
		std::cin >> command2;
		vi_windows();
		std::vector<std::string> vec_tmp;
		std::string content_tmp;
		while(std::cin >> content_tmp) {
			if (content_tmp == "exit") {
				break;
			}
			vec_tmp.push_back(content_tmp);
		}
		clear_screen();
		std::cout << "\n\n\n";
		set_yellow_high();
		std::cout << "                       ��ӭʹ��ɽկ�ļ�ϵͳ_(:�٩f��)_" << std::endl;
		set_white();
		std::cout << "                  ********************************************" << std::endl;
		vi_command(command2, vec_tmp);
	} else {
		show_path();
		set_red_high();
		std::cout << "û�д����" << std::endl;
		set_white();
		sub_window();
	}
}

std::string Shell::authority_to_string(const int authority) {
	if (authority < 100 || authority >= 1000) {
		return "error";
	}
	auto a = authority / 100;
	auto b = (authority % 100) / 10;
	auto c = authority % 10;
	if (!(a < 8 && b < 8 && c < 8)) {
		return "error";
	}
	std::string result = "";
	result += to_binary(a);
	result += to_binary(b);
	result += to_binary(c);
	return result;
}

std::string Shell::to_binary(const int num) {
	std::string result;
	if (num == 7) {
		result = "111";
	} else if (num == 6) {
		result = "110";
	} else if (num == 5) {
		result = "101";
	} else if (num == 4) {
		result = "100";
	} else if (num == 3) {
		result = "011";
	} else if (num == 2) {
		result = "010";
	} else if (num == 1) {
		result = "001";
	} else if (num == 0) {
		result = "000";
	}
	return result;
}

void Shell::mk_command(std::string filename) {
	auto result = file_system.new_file(filename);
	show_path();
	set_red_high();
	if (result == "file_already_exist") {
		std::cout << "�ļ��Ѵ��ڣ�" << std::endl;
	} else if (result == "filename_error") {
		std::cout << "�ļ�������" << std::endl;
	} else if (result == "no_space") {
		std::cout << "�ռ䲻�㣡" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ�" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::mkdir_command(std::string dir_name) {
	auto result = file_system.new_directory(dir_name);
	show_path();
	set_red_high();
	if (result == "directory_already_exist") {
		std::cout << "�ļ����Ѵ��ڣ�" << std::endl;
	} else if (result == "directory_error") {
		std::cout << "�ļ���������" << std::endl;
	} else if (result == "no_space") {
		std::cout << "�ռ䲻�㣡" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::ls_command() {
	show_path();
	auto result = file_system.list_names();
	auto files = result.first;
	auto directories = result.second;
	set_ls_file();
	for (auto c : files) {
		std::cout << c << "   ";
	}
	set_blue_high();
	for (auto c : directories) {
		std::cout << c << "   ";
	}
	set_white();
	std::cout << std::endl;
	sub_window();
}

void Shell::cd_command(std::string path) {
	file_system.change_current_directory(path);
	sub_window();
}

void Shell::passwd_command() {
	show_path();
	std::cout << "�����룺";
	std::string old_password;
	std::cin >> old_password;
	if (!file_system.check_password(old_password)) {
		sub_window();
	}
	std::string password;
	std::string re_password;
	show_path();
	std::cout << "������: ";
	std::cin >> password;
	show_path();
	std::cout << "��������������: ";
	std::cin >> re_password;
	if (password != re_password) {
		show_path();
		set_green_high();
		std::cout << "�������벻һ�£�" << std::endl;
		set_white();
		sub_window();
	}
	auto result = file_system.change_password(password);
	if (!result) {
		show_path();
		set_magenta_high();
		std::cout << "�����ʽ���ԣ�" << std::endl;
		set_white();
	}
	show_path();
	set_yellow_high();
	std::cout << "�����޸ĳɹ���" << std::endl;
	set_white();
	sub_window();
}

void Shell::exit_command() {
	exit_process();
}

void Shell::chmod_command(std::string filename, const int authority) {
	auto auth = authority_to_string(authority);
	show_path();
	set_red_high();
	if (auth == "error") {
		std::cout << "Ȩ����������" << std::endl;
	} else {
		auto result = file_system.change_mode(filename, auth);
		if (!result) {
			std::cout << "�ļ������ڣ�" << std::endl;
		}
		else {
			set_yellow_high();
			std::cout << "�����ɹ���" << std::endl;
		}
	}
	set_white();
	sub_window();
}

void Shell::pwd_command() {
	show_path();
	set_green_high();
	std::cout << file_system.display_current_directory() << std::endl;
	set_white();
	sub_window();
}

void Shell::chown_command(const std::string& filename, const std::string& username) {
	auto result = file_system.change_file_user(filename, username);
	show_path();
	set_red_high();
	if (result == "not_root") {
		std::cout << "��root�û��޲���Ȩ�ޣ�" << std::endl;
	} else if (result == "user_not_exist") {
		std::cout << "�û������ڣ�" << std::endl;
	} else if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::chgrp_command(const std::string& filename, const std::string& group_name) {
	auto result = file_system.change_file_group(filename, group_name);
	show_path();
	set_red_high();
	if (result == "not_root") {
		std::cout << "��root�û��޲���Ȩ�ޣ�" << std::endl;
	}
	else if (result == "group_not_exist") {
		std::cout << "�鲻���ڣ�" << std::endl;
	}
	else if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	}
	else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::mv_command(const std::string& filename_old, const std::string& filename_new) {
	auto result = file_system.rename_file(filename_old, filename_new);
	show_path();
	set_red_high();
	if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	} else if (result == "filename_error") {
		std::cout << "�ļ�������" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::cp_command(const std::string& filename_old, const std::string& filename_new) {
	auto result = file_system.copy_file(filename_old, filename_new);
	show_path();
	set_red_high();
	if (result == "filename_error") {
		std::cout << "�ļ�������" << std::endl;
	} else if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::rm_command(const std::string& filename) {
	auto result = file_system.remove_file(filename);
	show_path();
	set_red_high();
	if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	} else if (result == "no_authority") {
		std::cout << "û��Ȩ�ޣ�" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::rmdir_command(const std::string& dir_name) {
	auto result = file_system.remove_empty_directory(dir_name);
	show_path();
	set_red_high();
	if (result == "directory_not_exist") {
		std::cout << "�ļ��в����ڣ�" << std::endl;
	} else if (result == "not_empty") {
		std::cout << "�ļ��зǿգ�" << std::endl;
	} else if (result == "no_authority") {
		std::cout << "û��Ȩ�ޣ�" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::ln_command(const std::string& filename, const std::string& linkname) {
	auto result = file_system.link_file(filename, linkname);
	show_path();
	set_red_high();
	if (result == "filename_error") {
		std::cout << "�ļ�������" << std::endl;
	} else if (result == "file_not_exist") {
		std::cout << "�ļ������ڣ�" << std::endl;
	} else {
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::cat_command(const std::string& filename1, const std::string& filename2) {
	auto result1 = file_system.display_file_context(filename1);
	auto result2 = file_system.display_file_context(filename2);
	show_path();
	if (result1 == "file_not_exist" || result2 == "file_not_exist") {
		set_red_high();
		std::cout << "�ļ������ڣ�" << std::endl;
		set_white();
	} else {
		std::cout << result1 << result2 << std::endl;
	}
	sub_window();
}

void Shell::umask_command(const int authority) {
	auto auth = authority_to_string(authority);
	show_path();
	set_red_high();
	if (auth == "error") {
		std::cout << "Ȩ����������" << std::endl;
	}
	else {
		file_system.umask_command(auth);
		set_yellow_high();
		std::cout << "�����ɹ���" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::vi_command(const std::string& filename, const std::vector<std::string>& content_vec) {
	std::string content_str = "";
	for (const auto &c : content_vec) {
		content_str += c;
	}

	auto result = file_system.new_file_with_content(filename, content_str);
	show_path();
	set_red_high();
	if (result == "file_already_exist") {
		std::cout << "�ļ��Ѵ��ڣ�" << std::endl;
	}
	else if (result == "filename_error") {
		std::cout << "�ļ�������" << std::endl;
	}
	else if (result == "no_space") {
		std::cout << "�ռ䲻�㣡" << std::endl;
	}
	else {
		set_yellow_high();
		std::cout << "�����ɹ�" << std::endl;
	}
	set_white();
	sub_window();
}

void Shell::vi_windows() {
	clear_screen();
	std::cout << "\n\n\n";
	set_yellow_high();
	std::cout << "                       ��ӭʹ��ɽկvi�༭��_(:�٩f��)_" << std::endl;
	set_white();
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  ";
}

void Shell::ls_l_file_command(const std::string& filename) {
	auto result = file_system.list_file_details(filename);
	show_path();
	if (result == "file_not_exist") {
		set_red_high();
		std::cout << "�ļ������ڣ�" << std::endl;
	} else {
		std::cout << result << std::endl;
	}
	sub_window();
}

void Shell::ls_l_command() {
	auto result = file_system.list_all_file_details();
	for (const auto &c : result) {
		show_path();
		std::cout << c << std::endl;
	}
	sub_window();
}
