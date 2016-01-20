#pragma once
#ifndef GROUP_H
#define GROUP_H
#include <string>

class Group {
	int group_id = 0;
	std::string group_name;

public:
	Group(const int group_id, const std::string& group_name);

	Group();

	const int& get_group_id() const;

	void set_group_id(const int group_id);

	const std::string& get_group_name() const;

	void set_group_name(const std::string& group_name);

	void set_group_name(std::string group_name);

	friend bool operator<(const Group& group1, const Group& group2);
};

bool operator<(const Group& group1, const Group& group2);


#endif

