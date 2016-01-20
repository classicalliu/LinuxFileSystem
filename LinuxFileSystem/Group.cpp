#include "Group.h"

Group::Group(const int group_id, const std::string& group_name): group_id(group_id),
                                                                 group_name(group_name) {
}

Group::Group() {
}

const int& Group::get_group_id() const {
	return group_id;
}

void Group::set_group_id(const int group_id) {
	this->group_id = group_id;
}

const std::string& Group::get_group_name() const {
	return group_name;
}

void Group::set_group_name(const std::string& group_name) {
	this->group_name = group_name;
}

void Group::set_group_name(std::string group_name) {
	this->group_name = std::move(group_name);
}

bool operator<(const Group& group1, const Group& group2) {
	return group1.group_id < group2.group_id;
}

