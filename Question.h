#pragma once
#include<string>
#include<vector>
#include<fstream>

class Question
{
public:
	Question();
	Question(const std::string& a_question_text, std::vector<std::string> a_options, int a_option_num);
	const std::string& get_text() const;
	void set_text(const std::string& a_question_text);
	const std::vector<std::string>& get_options() const;
	void set_options(const std::vector<std::string>& a_options);
	bool correct(int a_answer_num);
	int get_options_len() const;
	int get_option_num() const;
	void set_option_num(int num);
	void serialize(std::ofstream& ofile);
	void deserialize(std::ifstream& ifile);

private:
	std::string m_question_text;
	std::vector<std::string> m_options;
	int m_option_num;
};

