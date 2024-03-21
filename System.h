#pragma once
#include<unordered_map>
#include<string>
#include"User.h"
#include"Category.h"
#include<exception>
#include<iostream>
#include "Category.h"
#include "User.h"
#include <functional>

class System
{
public:
	void registrate_user(const std::string& login, const User& user);
	bool is_admin_registered();
	bool find_user(const std::string& login);
	void show_statistics();
	void show_results();
	void take_test(const std::string& category);
	bool find_user(const std::string& login, const size_t& password);
	void login(const std::string& login);
	void delete_user();
	void show_users();
	void change_login(const std::string& login);
	void change_password(const size_t& password);
	void add_category(const Category& category);
	void add_category(Category&& category);
	Test& test_choice();
	Category& category_choice();
	void input_answers(Test& test);

	void serialize_categories(std::ofstream& ofile);
	void serialize_user_collection(std::ofstream& ofile);
	void deserialize_categories(std::ifstream& ifile);
	void deserialize_user_collection(std::ifstream& ifile);

	

private:
	void show_test_collection(const Category& category);
	void delete_user(int index);
	std::hash<std::string> m_hash_engine;
	User m_user;

	std::unordered_map<std::string, User> m_users;
	std::vector<Category> m_categories;
	bool m_isadmin;
	size_t m_admin_hash;
};

