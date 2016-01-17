#pragma once
#ifndef SHELL_H
#define SHELL_H
#include "FileSystem.h"

class Shell
{
	FileSystem file_system;
public:
	Shell();
	~Shell();

	// ¸¨Öúº¯Êý µÈ´ý
	static void pause();
	// ¸¨Öúº¯Êý£¬Çå³ýÆÁÄ»
	static void clear_screen();
	// ¸¨Öúº¯Êý£¬ÍË³ö³ÌÐò
	static void exit_process();
	// ¸¨Öúº¯Êý£¬È¥³ý×Ö·û´®Ê×Î²µÄ¿Õ¸ñ
	static void trim(std::string& str);
	static void sleep_second(const double second);
	static std::vector<std::string> split_command(const std::string& command);
	void show_path() const;

	void error();
	void help();
	void start();
	void user_login();
	void user_register();
	void main_window();
	void sub_window();
	static std::string authority_to_string(const int authority);
	static std::string to_binary(const int num);

	void mk_command(std::string filename);
	void mkdir_command(std::string dir_name);
	void ls_command();
	void cd_command(std::string path);
	void passwd_command();
	void exit_command();
	void chmod_command(std::string filename, const int authority);
	void pwd_command();
	void chown_command(const std::string &filename, const std::string &username);
	void chgrp_command(const std::string &filename, const std::string &group_name);
	void mv_command(const std::string &filename_old, const std::string &filename_new);
	void cp_command(const std::string &filename_old, const std::string &filename_new);
	void rm_command(const std::string &filename);
	void rmdir_command(const std::string &dir_name);
	void ln_command(const std::string &filename, const std::string &linkname);
	void cat_command(const std::string &filename1, const std::string& filename2);
	void umask_command(const int authority);
	// TODO ls -l command
};

#endif
