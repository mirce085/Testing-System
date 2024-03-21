#include "Question.h"

Question::Question(const std::string& a_question_text, std::vector<std::string> a_options, int a_option_num) {
	m_question_text = a_question_text;
	m_options = a_options;
	m_option_num = a_option_num;
}

const std::string& Question::get_text() const{
	return m_question_text;
}

const std::vector<std::string>& Question::get_options() const{
	return m_options;
}

bool Question::correct(int a_option_num) {
	return m_option_num == a_option_num;
}

int Question::get_options_len() const {
	return m_options.size();
}

int Question::get_option_num() const {
	return m_option_num;
}

void Question::serialize(std::ofstream& ofile) {
	int options_len = static_cast<int>(m_options.size());
	ofile.write(reinterpret_cast<const char*>(&options_len), sizeof(options_len));
	for (auto& option : m_options) {
		int option_len = static_cast<int>(option.size());
		ofile.write(reinterpret_cast<const char*>(&option_len), sizeof(option_len));
		ofile.write(option.c_str(), option_len);
	}
}


void Question::deserialize(std::ifstream& ifile) {
	int options_len;
	ifile.read(reinterpret_cast<char*>(&options_len), sizeof(options_len));
	for (int i = 0; i < options_len; ++i) {
		int option_len;
		ifile.read(reinterpret_cast<char*>(&option_len), sizeof(option_len));
		std::string option;
		option.resize(option_len);
		ifile.read(&option[0], option_len);
		m_options.push_back(option);
	}
}

Question::Question() : m_option_num(0){}

void Question::set_options(const std::vector<std::string>& a_options) {
	m_options = a_options;
}

void Question::set_option_num(int num) {
	m_option_num = num;
}

void Question::set_text(const std::string& a_question_text) {
	m_question_text = a_question_text;
}