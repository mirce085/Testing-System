#include "User.h"

User::User(const std::string& a_login, const size_t& a_password, const std::string& a_name, const std::string& a_surname, const std::string& a_phonenumber) {
	m_login = a_login;
	m_password = a_password;
	m_name = a_name;
	m_surname = a_surname;
	m_phonenumber = a_phonenumber;
}



const size_t& User::get_password() const {
	return m_password;
}

void User::set_login(const std::string& a_login) {
	m_login = a_login;
}

void User::set_password(const size_t& a_password) {
	m_password = a_password;
}

const std::string& User::get_name() const{
	return m_name;
}

User::User() {}

const std::string& User::get_surname() const {
	return m_surname;
}

const std::string& User::get_login() const {
	return m_login;
}

const std::string& User::get_phone_number() const {
	return m_phonenumber;
}

TestResult& User::operator[](const std::string& test_name) {
	return m_results[test_name];
}

void User::serialize_results(std::ofstream& ofile) {
	int results_len = static_cast<int>(m_results.size());
	ofile.write(reinterpret_cast<const char*>(&results_len), sizeof(results_len));
	for (auto& test_result : m_results) {
		int test_result_name_len = test_result.first.size();
		ofile.write(reinterpret_cast<const char*>(&test_result_name_len), sizeof(test_result_name_len));
		ofile.write(test_result.first.c_str(), test_result_name_len);

		int last_question_num = test_result.second.get_last_question_num();
		ofile.write(reinterpret_cast<const char*>(&last_question_num), sizeof(last_question_num));

		int point = test_result.second.get_point();
		ofile.write(reinterpret_cast<const char*>(&point), sizeof(point));	

		float result_percent = test_result.second.get_result_percent();
		ofile.write(reinterpret_cast<const char*>(&result_percent), sizeof(result_percent));

		int correct_count = test_result.second.get_correct_count();
		ofile.write(reinterpret_cast<const char*>(&correct_count), sizeof(correct_count));

		int answer_numbers_len = test_result.second.get_answer_numbers_len();
		ofile.write(reinterpret_cast<const char*>(&answer_numbers_len), sizeof(answer_numbers_len));
		for (int i = 0; i < answer_numbers_len; ++i) {
			int answer_num = test_result.second.get_answer_number(i);
			ofile.write(reinterpret_cast<const char*>(&answer_num), sizeof(answer_num));
		}
	}
}

void User::deserialize_results(std::ifstream& ifile) {
	int results_len = static_cast<int>(m_results.size());
	ifile.read(reinterpret_cast<char*>(&results_len), sizeof(results_len));
	for (int i = 0; i < results_len; ++i) {
		std::pair<std::string, TestResult> pair;

		int test_result_name_len;
		ifile.read(reinterpret_cast<char*>(&test_result_name_len), sizeof(test_result_name_len));
		std::string test_name;
		test_name.resize(test_result_name_len);
		ifile.read(&test_name[0], test_result_name_len);

		int last_question_num;
		ifile.read(reinterpret_cast<char*>(&last_question_num), sizeof(last_question_num));

		int point;
		ifile.read(reinterpret_cast<char*>(&point), sizeof(point));

		float result_percent;
		ifile.read(reinterpret_cast<char*>(&result_percent), sizeof(result_percent));

		int correct_count;
		ifile.read(reinterpret_cast<char*>(&correct_count), sizeof(correct_count));

		int answer_numbers_len;
		ifile.read(reinterpret_cast<char*>(&answer_numbers_len), sizeof(answer_numbers_len));
		for (int i = 0; i < answer_numbers_len; ++i) {
			int answer_num;
			ifile.read(reinterpret_cast<char*>(&answer_num), sizeof(answer_num));
			pair.second.add_answer(answer_num);
		}
		pair.first = test_name;
		pair.second.set_point(point);
		pair.second.set_correct_count(correct_count);
		pair.second.set_result_percent(result_percent);
		pair.second.set_last_question_num(last_question_num);
		m_results.insert(pair);
	}
}