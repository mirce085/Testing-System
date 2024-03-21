#pragma once
#include <string>
#include<unordered_map>
#include "Test.h"
#include "TestResult.h"


class User
{
public:
	User();
	User(const std::string& a_login, const size_t& a_password, const std::string& a_name, const std::string& a_surname, const std::string& a_phonenumber);
	void set_login(const std::string& a_login);
	void set_password(const size_t& a_password);
	const size_t& get_password() const;
	const std::string& get_login() const;
	const std::string& get_name() const;
	const std::string& get_surname() const;
	const std::string& get_phone_number() const;
	TestResult& operator[](const std::string& test_name);
	void serialize_results(std::ofstream& ofile);
	void deserialize_results(std::ifstream& ifile);


private:
	std::string m_login;
	std::string m_phonenumber;
	size_t m_password;
	std::string m_name;
	std::string m_surname;
	std::unordered_map<std::string, TestResult> m_results;
};

