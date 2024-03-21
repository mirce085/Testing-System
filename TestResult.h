#pragma once
#include "Test.h"


class TestResult
{
public:
	TestResult();
	TestResult(int a_last_question_num, int a_point, float a_result_percent, int a_correct_count, const std::vector<int>& a_answer_numbers);
	
	int get_last_question_num() const;
	int get_point() const;
	int get_correct_count() const;
	float get_result_percent() const;
	int get_answer_number(int index) const;
	int get_answer_numbers_len() const;

	void increment_last_question_num();
	void set_last_question_num(int a_last_question_num);
	void set_point(int a_point);
	void set_result_percent(float a_result_percent);
	void set_correct_count(int a_correct_count);

	void grade(const Test& test);
	void add_answer(int answer_num);



private:
	int m_last_question_num;
	int m_point;
	float m_result_percent;
	int m_correct_count;
	std::vector<int> m_answer_numbers;                                         
};

