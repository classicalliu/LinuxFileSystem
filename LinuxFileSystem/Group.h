#pragma once
#include <string>

class Group {
	int group_id = 0;
	std::string group_name;

public:
	Group(const int group_id, const std::string& group_name)
		: group_id(group_id),
		group_name(group_name) {
	}

	Group() {
	}

	const int& get_group_id() const {
		return group_id;
	}

	void set_group_id(const int group_id) {
		this->group_id = group_id;
	}

	const std::string& get_group_name() const {
		return group_name;
	}

	void set_group_name(const std::string& group_name) {
		this->group_name = group_name;
	}

	void set_group_name(std::string group_name) {
		this->group_name = std::move(group_name);
	}
};
