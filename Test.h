#pragma once
#include"Question.h"
#include <vector>
#include <string>


class Test {
public:
	Test(const std::string& a_test_name);
	void add_question(const std::string& a_question_text, std::vector<std::string> a_answers, int a_answer_num);
	void add_question(const Question& question);
	const Question& get_question_by_index(int index) const;
	int get_answer_by_index(int index) const;
	int get_questions_len() const;
	const std::string& get_name() const;
	void serialize(std::ofstream& ofile);
	void deserialize(std::ifstream& ifile);
	int get_count() const;
	void increment_test_count();

private:
	std::string m_test_name;
	std::vector<Question> m_questions;
	int m_test_count;
};
