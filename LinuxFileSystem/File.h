#pragma once
#include <string>

// 文件块结构
class File {
	// 文件块大小为512B
	static const int size = 512;
	// 文件内容
	std::string file_content;
};