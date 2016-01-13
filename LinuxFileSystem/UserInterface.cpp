#include "UserInterface.h"
#include <iostream>
#include <string>
#include <ctime>

void help() {
	std::cout << "这里是帮助文件" << std::endl;
	std::cout << "命令格式说明" << std::endl;
	std::cout << "ls                      -->   列出当前目录中的子目录和文件" << std::endl;
	std::cout << "chmod xxx               -->   xxx为1-7之间的数字，表示用户权限" << std::endl;
	std::cout << "chgrp <name>            -->   改变当前文件的目录" << std::endl;
	std::cout << "psw                     -->   显示当前目录" << std::endl;
	std::cout << "cd <name>               -->   跳转到目录<name>， ..表示上层目录，/表示根目录，~表示home目录" << std::endl;
	std::cout << "mkdir <name>            -->   在当前目录下创建子目录" << std::endl;
	std::cout << "rmdir <name>            -->   删除子目录<name>" << std::endl;
	std::cout << "umask <name>            -->   创建文件屏蔽码" << std::endl;
	std::cout << "mv <source> <target>    -->   将文件从<source>移动到<target>" << std::endl;
	std::cout << "cp <source> <target>    -->   将文件从<source>移动到<target>" << std::endl;
	std::cout << "rm <name>               -->   删除文件名为<name>的文件" << std::endl;
	std::cout << "ln <source>             -->   将文件从<source>链接到当前文件夹" << std::endl;
	std::cout << "cat <name1> <name2> ... -->   连接显示文件内容" << std::endl;
	std::cout << "passwd                  -->   修改当前用户密码" << std::endl;
	std::cout << "help                    -->   显示帮助文件" << std::endl;
	std::cout << "exit                    -->   退出当前系统" << std::endl;
}
void dsptime(const struct tm * ptm);

int main() {
	time_t time_now = time(nullptr);
	std::string s = ctime(&time_now);
	std::cout << s << std::endl;
	system("pause");
	return 0;
}