#include "Shell.h"
#include "SetColor.h"
#include <iostream>


Shell::Shell()
{
}


Shell::~Shell()
{
}

void Shell::help() {
	set_yellow_high();
	std::cout << "                         帮助文件" << std::endl;
	std::cout << "                       命令格式说明" << std::endl;
	set_white();
	std::cout << " 1. ls                      -->   列出当前目录中的子目录和文件" << std::endl;
	std::cout << " 2. chmod xxx               -->   xxx为1-7之间的数字，表示用户权限" << std::endl;
	std::cout << " 3. chgrp <name>            -->   改变当前文件的目录" << std::endl;
	std::cout << " 4. psw                     -->   显示当前目录" << std::endl;
	std::cout << " 5. cd <name>               -->   跳转到目录<name>， ..表示上层目录，/表示根目录，~表示home目录" << std::endl;
	std::cout << " 6. mkdir <name>            -->   在当前目录下创建子目录" << std::endl;
	std::cout << " 7. rmdir <name>            -->   删除子目录<name>" << std::endl;
	std::cout << " 8. umask <name>            -->   创建文件屏蔽码" << std::endl;
	std::cout << " 9. mv <source> <target>    -->   将文件从<source>移动到<target>" << std::endl;
	std::cout << "10. cp <source> <target>    -->   将文件从<source>移动到<target>" << std::endl;
	std::cout << "11. rm <name>               -->   删除文件名为<name>的文件" << std::endl;
	std::cout << "12. ln <source>             -->   将文件从<source>链接到当前文件夹" << std::endl;
	std::cout << "13. cat <name1> <name2> ... -->   连接显示文件内容" << std::endl;
	std::cout << "14. passwd                  -->   修改当前用户密码" << std::endl;
	std::cout << "15. help                    -->   显示帮助文件" << std::endl;
	std::cout << "16. exit                    -->   退出当前系统" << std::endl;
}

void Shell::start() {
	//	set_magenta();
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  *                1. 用户登录                " << std::endl;
	std::cout << "                  *                2. 用户注册                " << std::endl;
	std::cout << "                  ********************************************" << std::endl;
	//	set_white();
}

void Shell::user_login() {
	std::string username;
	std::string password;
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                                   请输入用户名：              " << std::endl;
	std::cout << "                                   ";
	std::cin >> username;

	std::cout << "                                   请输入密码：              " << std::endl;
	std::cout << "                                   ";
	std::cin >> password;
	auto result = file_system.login(username, password);
	if (result == "user_not_exist") {
		set_red_high();
		std::cout << "                                   用户不存在！              " << std::endl;
		set_white();
	}
}

int main() {
	Shell shell;
	shell.user_login();
	system("pause");
	return 0;
}
