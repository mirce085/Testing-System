#include "TestResult.h"

TestResult::TestResult() {
	m_correct_count = 0;
	m_last_question_num = 0;
	m_point = 0;
	m_result_percent = 0;
}

int TestResult::get_last_question_num() const{
	return m_last_question_num;
}

int TestResult::get_point() const{
	return m_point;
}

float TestResult::get_result_percent() const{
	return m_result_percent;
}

int TestResult::get_correct_count() const{
	return m_correct_count;
}

void TestResult::grade(const Test& test) {
	for (int i = 0; i < m_answer_numbers.size(); ++i) {
		if (m_answer_numbers[i] == test.get_answer_by_index(i)) {
			++m_correct_count;
		}
	}
	m_point = m_correct_count * 12 / m_answer_numbers.size();
	m_result_percent = static_cast<float>(m_point) / 12 * 100;
}



TestResult::TestResult(int a_last_question_num, int a_point, float a_result_percent, int a_correct_count, const std::vector<int>& a_answer_numbers) {
	m_last_question_num = a_last_question_num;
	m_point = a_point;
	m_result_percent = a_result_percent;
	m_correct_count = a_correct_count;
	m_answer_numbers = a_answer_numbers;
}

void TestResult::add_answer(int answer_num) {
	m_answer_numbers.push_back(answer_num);
}

void TestResult::increment_last_question_num() {
	++m_last_question_num;
}

void TestResult::set_point(int a_point) {
	m_point = a_point;
}

void TestResult::set_result_percent(float a_result_percent) {
	m_result_percent = a_result_percent;
}

void TestResult::set_correct_count(int a_correct_count) {
	m_correct_count = a_correct_count;
}

int TestResult::get_answer_number(int index) const{
	return m_answer_numbers[index];
}

int TestResult::get_answer_numbers_len() const {
	return m_answer_numbers.size();
}

void TestResult::set_last_question_num(int a_last_question_num) {
	m_last_question_num = a_last_question_num;
}