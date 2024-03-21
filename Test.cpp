#include "Test.h"


Test::Test(const std::string& a_test_name) : m_test_name(a_test_name), m_test_count(0){}

void Test::add_question(const std::string& a_question_text, std::vector<std::string> a_answers, int a_answer_num) {
	Question question{ a_question_text, a_answers, a_answer_num };
	m_questions.push_back(std::move(question));
}

void Test::add_question(const Question& question) {
	m_questions.push_back(question);
}

void Test::increment_test_count() {
	++m_test_count;
}

int Test::get_answer_by_index(int index) const{
	return m_questions[index].get_option_num();
}

int Test::get_count() const {
	return m_test_count;
}


const std::string& Test::get_name() const{
	return m_test_name;
}


int Test::get_questions_len() const {
	return m_questions.size();
}

const Question& Test::get_question_by_index(int index) const{
	return m_questions[index];
}



void Test::serialize(std::ofstream& ofile) {
	ofile.write(reinterpret_cast<const char*>(&m_test_count), sizeof(m_test_count));

	int questions_len = static_cast<int>(m_questions.size());
	ofile.write(reinterpret_cast<const char*>(&questions_len), sizeof(questions_len));
	for (auto& question : m_questions) {
		int question_text_len = static_cast<int>(question.get_text().size());
		ofile.write(reinterpret_cast<const char*>(&question_text_len), sizeof(question_text_len));
		ofile.write(question.get_text().c_str(), question_text_len);

		int option_num = question.get_option_num();
		ofile.write(reinterpret_cast<const char*>(&option_num), sizeof(option_num));

		question.serialize(ofile);
	}
}

void Test::deserialize(std::ifstream& ifile) {
	ifile.read(reinterpret_cast<char*>(&m_test_count), sizeof(m_test_count));

	int questions_len;
	ifile.read(reinterpret_cast<char*>(&questions_len), sizeof(questions_len));
	for (int i = 0; i < questions_len; ++i) {
		int question_text_len;
		ifile.read(reinterpret_cast<char*>(&question_text_len), sizeof(question_text_len));
		std::string question_text;
		question_text.resize(question_text_len);
		ifile.read(&question_text[0], question_text_len);
		int option_num;
		ifile.read(reinterpret_cast<char*>(&option_num), sizeof(option_num));
		Question question;
		question.set_option_num(option_num);
		question.set_text(question_text);
		question.deserialize(ifile);
		m_questions.push_back(std::move(question));
	}
}
