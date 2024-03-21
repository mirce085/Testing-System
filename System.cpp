#include "System.h"


void System::show_users() {
    int i = 1;
    for(auto& user : m_users){
        if (m_hash_engine(user.first) != m_admin_hash) {
            std::cout << '[' << i << "]\n";
            std::cout << "Login : " << user.second.get_login() << "\nName : " << user.second.get_name() << "\nSurname : " << user.second.get_surname() << "\nPassword : " << user.second.get_password() << "\nPhone Number : " << user.second.get_phone_number() << '\n';
            std::cout << '\n';
        }
        ++i;
    }
}


void System::add_category(const Category& category) {
    m_categories.push_back(category);
}

void System::add_category(Category&& category) {
    m_categories.push_back(std::move(category));
}

void System::registrate_user(const std::string& login, const User& user) {
    if (m_users.size() == 0) {
        m_admin_hash = m_hash_engine(login);
    }
    m_users.emplace(login, user);
}


bool System::find_user(const std::string& login) {
    return m_users.find(login) != m_users.end();
}

bool System::find_user(const std::string& login, const size_t& password) {
    return m_users.find(login) != m_users.end() && m_users[login].get_password() == password;
}

bool System::is_admin_registered() {
    return m_isadmin;
}

void System::login(const std::string& login) {
    if (m_hash_engine(login) == m_admin_hash) {
        m_isadmin = true;
    }
    else {
        m_isadmin = false;
    }
    m_user = m_users[login];
}


void System::show_results() {
    for (auto& category : m_categories) {
        std::cout << category.get_name() << ':' << '\n';
        for (int j = 0; j < category.get_len(); ++j) {
            std::cout << '\t' << category.get_by_index(j).get_name() << ':' << '\n';
            std::cout << "\t\tCorrect answers :" << m_user[category.get_by_index(j).get_name()].get_correct_count() << '\n';
            std::cout << "\t\t" << m_user[category.get_by_index(j).get_name()].get_result_percent() << '%' << '\n';
            std::cout << "\t\t" << m_user[category.get_by_index(j).get_name()].get_point() << "/12" << "\n\n";
        }
        std::cout << '\n';
    }
}

void System::show_test_collection(const Category& category) {
    for (int i = 0; i < category.get_len(); ++i) {
        std::cout << '[' << i + 1 << ']' << category.get_by_index(i).get_name() << '\n';
    }
}

void System::input_answers(Test& test) {
    int ch;
    bool flag = true;
    for (int i = m_user[test.get_name()].get_last_question_num(); i < test.get_questions_len(); ++i) {
        flag = false;
        while (true) {
            system("cls");
            Question question = test.get_question_by_index(i);
            std::cout << question.get_text() << '\n';
            for (int j = 0; j < question.get_options_len(); ++j) {
                std::cout << '[' << j + 1 << ']' << question.get_options()[j] << '\n';
            }
            std::cout << "[Any Other]Return\n";
            std::cin >> ch;
            if (ch > question.get_options_len() || ch < 0) {
                return;
            }
            m_user[test.get_name()].add_answer(ch);
            m_user[test.get_name()].increment_last_question_num();
            break;
        }
    }
    if (flag) {
        std::cout << "Completed!\n";
        std::cout << "Go to Results menu to check your result!\n";
        system("pause");
        return;
    }
    test.increment_test_count();
    m_user[test.get_name()].grade(test);
    std::cout << m_user[test.get_name()].get_point() << " out of 12 points\n";
    system("pause");
}
    


void System::take_test(const std::string& category) {
    int ch;
    for (int i = 0; i < m_categories.size(); ++i) {
        if (m_categories[i].get_name() == category) {
            show_test_collection(m_categories[i]);
            std::cin >> ch;
            input_answers(m_categories[i][ch - 1]);
            break;
        }
    }
}

Test& System::test_choice() {
    int ch;
    Category& cat = category_choice();
    while (true) {
        system("cls");
        show_test_collection(cat);
        std::cin >> ch;
        std::cin.ignore();
        if (ch > 0 && ch <= cat.get_len()) {
            return cat[ch - 1];
        }
        std::cout << "wrong input\n";
        system("pause");
    }
}

Category& System::category_choice() {
    int cat_ch;
    while (true) {
        system("cls");
        for (int i = 0; i < m_categories.size(); ++i) {
            std::cout << '[' << i + 1 << ']' << m_categories[i].get_name() << '\n';
        }
        std::cin >> cat_ch;
        std::cin.ignore();
        if (cat_ch > 0 && cat_ch <= m_categories.size()) {
            return m_categories[cat_ch - 1];
        }
        std::cout << "wrong input\n";
        system("pause");
    }
}


void System::serialize_categories(std::ofstream& ofile) {
    int categories_len = static_cast<int>(m_categories.size());
    ofile.write(reinterpret_cast<const char*>(&categories_len), sizeof(categories_len));
    for (auto& category : m_categories) {
        int category_name_len = static_cast<int>(category.get_name().size());
        ofile.write(reinterpret_cast<const char*>(&category_name_len), sizeof(category_name_len));
        ofile.write(category.get_name().c_str(), category_name_len);
        category.serialize(ofile);
    }
    ofile.close();
}

void System::serialize_user_collection(std::ofstream& ofile) {
    m_users[m_user.get_login()] = m_user;

    ofile.write(reinterpret_cast<const char*>(&m_admin_hash), sizeof(m_admin_hash));

    ofile.write(reinterpret_cast<const char*>(&m_isadmin), sizeof(m_isadmin));

    int users_len = static_cast<int>(m_users.size());
    ofile.write(reinterpret_cast<const char*>(&users_len), sizeof(users_len));
    for (auto& user : m_users) {
        int login_len = static_cast<int>(user.first.size());
        ofile.write(reinterpret_cast<const char*>(&login_len), sizeof(login_len));
        ofile.write(user.first.c_str(), login_len);

        int phonenumber_len = static_cast<int>(user.second.get_phone_number().size());
        ofile.write(reinterpret_cast<const char*>(&phonenumber_len), sizeof(phonenumber_len));
        ofile.write(user.second.get_phone_number().c_str(), phonenumber_len);

        int name_len = static_cast<int>(user.second.get_name().size());
        ofile.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        ofile.write(user.second.get_name().c_str(), name_len);

        int surname_len = static_cast<int>(user.second.get_surname().size());
        ofile.write(reinterpret_cast<const char*>(&surname_len), sizeof(surname_len));
        ofile.write(user.second.get_surname().c_str(), surname_len);

        ofile.write(reinterpret_cast<const char*>(&user.second.get_password()), sizeof(user.second.get_password()));
        
        user.second.serialize_results(ofile);
    }
    ofile.close();
}



void System::delete_user(int index) {
    int i = 0;
    for (auto& user : m_users) {
        if (index - 1 == i) {
            if (m_hash_engine(user.first) == m_admin_hash) {
                std::cout << "You can't delete admin account!\n";
                system("pause");
                return;
            }
            m_users.erase(user.first);
            break;
        }
        ++i;
    }
}

void System::delete_user() {
    while (true) {
        system("cls");
        if (m_users.size() <= 1) {
            std::cout << "Empty!\n";
            system("pause");
            return;
        }
        show_users();
        int input;
        std::cin >> input;
        if (input > 0 && input <= m_users.size()) {
            delete_user(input);
            return;
        }
        std::cout << "wrong input!\n";
        system("pause");
    }
}

void System::change_login(const std::string& login) {
    m_users.erase(m_user.get_login());
    m_user.set_login(login);
    m_admin_hash = m_hash_engine(login);
}

void System::change_password(const size_t& password) {
    m_user.set_password(password);
}


void System::show_statistics() {
    int overall_count = 0;
    for (auto& category : m_categories) {
        int category_count = 0;
        std::cout << category.get_name() << " : \n";
        for (int i = 0; i < category.get_len(); ++i) {
            std::cout << '\t' << category[i].get_name() << " : " << category[i].get_count() << '\n';
            overall_count += category[i].get_count();
            category_count += category[i].get_count();
        }
        std::cout << '\t' << category.get_name() << " overall : " << category_count << " tests" << '\n';
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << "Overall : " << overall_count << " tests" << '\n';
}





void System::deserialize_categories(std::ifstream& ifile) {
    int categories_len;
    ifile.read(reinterpret_cast<char*>(&categories_len), sizeof(categories_len));
    for (int i = 0; i < categories_len; ++i) {
        int category_name_len;
        ifile.read(reinterpret_cast<char*>(&category_name_len), sizeof(category_name_len));
        std::string category_name;
        category_name.resize(category_name_len);
        ifile.read(&category_name[0], category_name_len);
        Category category{ category_name };
        category.deserialize(ifile);
        m_categories.emplace_back(category);
    }
    ifile.close();
}

void System::deserialize_user_collection(std::ifstream& ifile) {
    ifile.read(reinterpret_cast<char*>(&m_admin_hash), sizeof(m_admin_hash));

    ifile.read(reinterpret_cast<char*>(&m_isadmin), sizeof(m_isadmin));

    int users_len = static_cast<int>(m_users.size());
    ifile.read(reinterpret_cast<char*>(&users_len), sizeof(users_len));
    for (int i = 0; i < users_len; ++i) {
        int login_len;
        ifile.read(reinterpret_cast<char*>(&login_len), sizeof(login_len));
        std::string login;
        login.resize(login_len);
        ifile.read(&login[0], login_len);

        int phonenumber_len;
        ifile.read(reinterpret_cast<char*>(&phonenumber_len), sizeof(phonenumber_len));
        std::string phonenumber;
        phonenumber.resize(phonenumber_len);
        ifile.read(&phonenumber[0], phonenumber_len);

        int name_len;
        ifile.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        std::string name;
        name.resize(name_len);
        ifile.read(&name[0], name_len);

        int surname_len;
        ifile.read(reinterpret_cast<char*>(&surname_len), sizeof(surname_len));
        std::string surname;
        surname.resize(surname_len);
        ifile.read(&surname[0], surname_len);

        size_t password;
        ifile.read(reinterpret_cast<char*>(&password), sizeof(password));

        User user{ login, password, name, surname, phonenumber };
        user.deserialize_results(ifile);

        m_users.emplace(login, std::move(user));
    }
    ifile.close();
}

