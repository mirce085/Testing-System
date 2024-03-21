#include "Category.h"

Category::Category(const std::string& a_name) : m_category_name(a_name){}

void Category::add_test(const Test& test) {
	m_tests.push_back(test);
}

const Test& Category::get_by_index(int index) const{
	return m_tests[index];
}

const std::string& Category::get_name() const{
	return m_category_name;
}

int Category::get_len() const {
	return m_tests.size();
}



Test& Category::operator[](int index) {
	return m_tests[index];
}

void Category::serialize(std::ofstream& ofile) {
	int tests_len = static_cast<int>(m_tests.size());
	ofile.write(reinterpret_cast<const char*>(&tests_len), sizeof(tests_len));
	for (auto& test : m_tests) {
		int test_name_len = static_cast<int>(test.get_name().size());
		ofile.write(reinterpret_cast<const char*>(&test_name_len), sizeof(test_name_len));
		ofile.write(test.get_name().c_str(), test_name_len);

		test.serialize(ofile);
	}
}

void Category::deserialize(std::ifstream& ifile) {
	int tests_len;
	ifile.read(reinterpret_cast<char*>(&tests_len), sizeof(tests_len));
	for (int i = 0; i < tests_len; ++i) {
		int test_name_len;
		ifile.read(reinterpret_cast<char*>(&test_name_len), sizeof(test_name_len));
		std::string test_name;
		test_name.resize(test_name_len);
		ifile.read(&test_name[0], test_name_len);

		Test test{ test_name };

		test.deserialize(ifile);

		m_tests.emplace_back(std::move(test));
	}
}
