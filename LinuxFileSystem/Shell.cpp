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
}

void Shell::start() {
	//	set_magenta();
	std::cout << "\n\n\n";
	std::cout << "                  ********************************************" << std::endl;
	std::cout << "                  *                1. �û���¼                " << std::endl;
	std::cout << "                  *                2. �û�ע��                " << std::endl;
	std::cout << "                  ********************************************" << std::endl;
	//	set_white();
}

void Shell::user_login() {
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
	if (result == "user_not_exist") {
		set_red_high();
		std::cout << "                                   �û������ڣ�              " << std::endl;
		set_white();
	}
}

int main() {
	Shell shell;
	shell.user_login();
	system("pause");
	return 0;
}
