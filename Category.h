#pragma once
#include "Test.h"
#include<utility>
#include<unordered_map>

class Category {
public:
	Category(const std::string& a_name);
	void add_test(const Test& test);
	const Test& get_by_index(int index) const;
	Test& operator[](int index);
	const std::string& get_name() const;
	int get_len() const;
	void serialize(std::ofstream& ofile);
	void deserialize(std::ifstream& ifile);

private:
	std::vector<Test> m_tests;
	std::string m_category_name;
};