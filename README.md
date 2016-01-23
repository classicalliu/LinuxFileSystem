# Linux文件系统模拟实验

## 开发环境
### 开发语言
C++ 11/14
### 系统环境
Windows 10
### 开发工具
Visual Studio 2015 && Resharper 10

## 实现功能
1. ls                      -->   列出当前目录中的子目录和文件
2. ls-l <name>             -->   列出<name>的详细信息
3. ls-L                    -->   列出当前目录中所有的文件和子目录的信息
4. chmod xxx               -->   x为1-7之间的数字，表示用户权限
5. chgrp <name>            -->   改变当前文件的目录
6. chown <name>            -->   改变当前文件的用户
7. psw                     -->   显示当前目录
8. cd <name>               -->   跳转到目录<name>， ..表示上层目录，/表示根目录，~表示home目录
9. mkdir <name>            -->   在当前目录下创建子目录
10. rmdir <name>            -->   删除子目录<name>
11. umask <name>            -->   创建文件屏蔽码
12. mv <source> <target>    -->   将文件从<source>移动到<target>
13. cp <source> <target>    -->   将文件从<source>移动到<target>
14. rm <name>               -->   删除文件名为<name>的文件
15. ln <source>             -->   将文件从<source>链接到当前文件夹
16. cat <name1> <name2> ... -->   连接显示文件内容
17. passwd                  -->   修改当前用户密码
18. vi <filename>           -->   创建名为<filename>的文件，进入vi编辑界面，输入exit退出
19. help                    -->   显示帮助文件
20. exit                    -->   退出当前系统
