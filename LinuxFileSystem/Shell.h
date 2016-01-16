#pragma once
#ifndef SHELL_H
#define SHELL_H
#include "FS_Test.h"

class Shell
{
	FileSystem file_system;
public:
	Shell();
	~Shell();

	void help();
	void start();
	void user_login();
};

#endif
