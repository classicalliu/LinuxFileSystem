#include "UserInterface.h"
#include <iostream>
#include <string>
#include <ctime>

void help() {
	std::cout << "�����ǰ����ļ�" << std::endl;
	std::cout << "�����ʽ˵��" << std::endl;
	std::cout << "ls                      -->   �г���ǰĿ¼�е���Ŀ¼���ļ�" << std::endl;
	std::cout << "chmod xxx               -->   xxxΪ1-7֮������֣���ʾ�û�Ȩ��" << std::endl;
	std::cout << "chgrp <name>            -->   �ı䵱ǰ�ļ���Ŀ¼" << std::endl;
	std::cout << "psw                     -->   ��ʾ��ǰĿ¼" << std::endl;
	std::cout << "cd <name>               -->   ��ת��Ŀ¼<name>�� ..��ʾ�ϲ�Ŀ¼��/��ʾ��Ŀ¼��~��ʾhomeĿ¼" << std::endl;
	std::cout << "mkdir <name>            -->   �ڵ�ǰĿ¼�´�����Ŀ¼" << std::endl;
	std::cout << "rmdir <name>            -->   ɾ����Ŀ¼<name>" << std::endl;
	std::cout << "umask <name>            -->   �����ļ�������" << std::endl;
	std::cout << "mv <source> <target>    -->   ���ļ���<source>�ƶ���<target>" << std::endl;
	std::cout << "cp <source> <target>    -->   ���ļ���<source>�ƶ���<target>" << std::endl;
	std::cout << "rm <name>               -->   ɾ���ļ���Ϊ<name>���ļ�" << std::endl;
	std::cout << "ln <source>             -->   ���ļ���<source>���ӵ���ǰ�ļ���" << std::endl;
	std::cout << "cat <name1> <name2> ... -->   ������ʾ�ļ�����" << std::endl;
	std::cout << "passwd                  -->   �޸ĵ�ǰ�û�����" << std::endl;
	std::cout << "help                    -->   ��ʾ�����ļ�" << std::endl;
	std::cout << "exit                    -->   �˳���ǰϵͳ" << std::endl;
}
void dsptime(const struct tm * ptm);

int main() {
	time_t time_now = time(nullptr);
	std::string s = ctime(&time_now);
	std::cout << s << std::endl;
	system("pause");
	return 0;
}