#include <iostream>
#include "System.h"

System testing_system{};
std::hash<std::string> hash_engine;

bool login() {
    while (true) {
        std::string login;
        std::cout << "Enter login : ";
        std::cin >> login;
        std::string password;
        std::cout << "Enter password : ";
        std::cin >> password;
        if (testing_system.find_user(login, hash_engine(password))) {
            testing_system.login(login);
            std::cout << "Hello " << login << '\n';
            system("pause");
            return true;
        }
        std::cout << "Can't find such user\n";
        system("pause");
        return false;
    }
}

void registrate_user() {
    std::ofstream ofile("user_data.bin", std::ios::binary);
    std::string password1;
    std::string password2;
    std::string login;
    std::string name;
    std::string surname;
    std::string phonenumber;
    while (true) {
        system("cls");
        std::cout << "Enter new login : ";
        std::cin >> login;
        if (!testing_system.find_user(login)) {
            break;
        }
        std::cout << "Existing login\n";
        system("pause");
        continue;
    }
    std::cout << "Enter your name : ";
    std::cin >> name;
    std::cout << "Enter your surname : ";
    std::cin >> surname;
    std::cout << "Enter your phone number : ";
    std::cin >> phonenumber;
    while (password1 == password2) {
        std::cout << "Enter new password : ";
        std::cin >> password1;
        std::cout << "Enter new password again : ";
        std::cin >> password2;
        if (password1 == password2) {
            User user{ login, hash_engine(password1), name , surname, phonenumber};
            testing_system.registrate_user(login, std::move(user));
            testing_system.serialize_user_collection(ofile);
            break;
        }
        std::cout << "wrong password\n"; 
        system("pause");
    }
}



void test_window() {
    testing_system.input_answers(testing_system.test_choice());
}

void question_adding(Test& test);

void test_adding(Category& category) {
    while (true) {
        int ch;
        system("cls");
        std::string test_name;
        std::cout << "Enter test name : ";
        std::cin >> test_name;
        std::cin.ignore();
        Test test{ test_name };
        question_adding(test);
        system("cls");
        category.add_test(std::move(test));
        std::cout << "[1]Add One More Test\n";
        std::cout << "[Any Other]Exit\n";
        std::cin >> ch;
        if (ch != 1) {
            break;
        }
    }
}



void answer_adding(std::vector<std::string>& answers, int& correct_num) {
    int ch;
    int count = 0;
    for (int i = 1; i <= 4; i++) {
        std::string answer;
        std::cout << "Enter " << i << " answer : ";
        std::cin >> answer;
        answers.push_back(answer);
        ++count;
        if (i >= 2 && i < 4) {
            std::cout << "[1]Add One More Answer\n";
            std::cout << "[Any Other]Exit\n";
            std::cin >> ch;
            if (ch != 1) {
                break;
            }
        }
    }
    while (true) {
        std::cout << "Enter correct test number : ";
        std::cin >> correct_num;
        if (0 < correct_num && correct_num <= count) {
            break;
        }
        std::cout << "wrong input!\n";
    }
}

void question_adding(Test& test) {
    int ch;
    while (true) {
        system("cls");
        std::string question_text;
        std::cout << "Enter question : ";
        std::cin >> question_text;
        std::vector<std::string> answers;
        int correct_num;
        answer_adding(answers, correct_num);
        system("cls");
        Question question{ question_text, answers, correct_num };
        test.add_question(std::move(question));
        system("cls");
        std::cout << "[1]Add One More Question\n";
        std::cout << "[Any Other]Exit\n";
        std::cin >> ch;
        if (ch != 1) {
            break;
        }
    }
}

void category_adding_window() {
    std::string category_name;
    std::cout << "Enter category name : ";
    std::cin >> category_name;
    Category cat{ category_name };
    test_adding(cat);
    testing_system.add_category(std::move(cat));
    std::cout << "Category has been successfully added!\n";
    system("pause");
}

void test_adding_window() {
    test_adding(testing_system.category_choice());
    system("cls");
    std::cout << "Test has been successfully added!\n";
    system("pause");
}

void question_adding_window() {
    question_adding(testing_system.test_choice());
    system("cls");
    std::cout << "Question has been successfully added!\n";
    system("pause");
}

void login_change_window(){
    std::string login;
    while (true) {
        system("cls");
        std::cout << "Enter new login : ";
        std::cin >> login;
        if (testing_system.find_user(login)) {
            testing_system.change_login(login);
            std::cout << "existing login\n";
            system("pause");
            continue;
        }
        testing_system.change_login(login);
        std::cout << "login has been successfully changed!\n";
        system("pause");
        break;
    }
}

void password_change_window() {
    std::string password1;
    std::string password2;
    while (true) {
        system("cls");
        std::cout << "Enter new password : ";
        std::cin >> password1;
        std::cout << "Enter password again : ";
        std::cin >> password2;
        if (password1 == password2) {
            testing_system.change_password(hash_engine(password1));
            std::cout << "password has been successfully changed!\n";
            system("pause");
            break;
        }
        std::cout << "wrong input!\n";
        system("pause");
    }
}

void save_all() {
    std::ofstream ofile1("user_data.bin", std::ios::binary);
    ofile1.clear();
    ofile1.seekp(0);
    testing_system.serialize_user_collection(ofile1);
    std::ofstream ofile2("test_data.bin", std::ios::binary);
    ofile2.clear();
    ofile2.seekp(0);
    testing_system.serialize_categories(ofile2);
}


void admin_window() {
    int choice;
    while (true) {
        std::cout << "[1]Registrate New User\n";
        std::cout << "[2]Delete User\n";
        std::cout << "[3]Change Login\n";
        std::cout << "[4]Change Password\n";
        std::cout << "[5]Add Category\n";
        std::cout << "[6]Add Test\n";
        std::cout << "[7]Add Question\n";
        std::cout << "[8]Show Statistics\n";
        std::cout << "[9]Take Test\n";
        std::cout << "[10]Show Results\n";
        std::cout << "[Any Other]Save and Exit\n";
        std::cin >> choice;
        if (choice == 1) {
            system("cls");
            registrate_user();
            system("cls");
        }
        else if (choice == 2) {
            system("cls");
            testing_system.delete_user();
            system("cls");
        }
        else if (choice == 3) {
            system("cls");
            login_change_window();
            system("cls");
        }
        else if (choice == 4) {
            system("cls");
            password_change_window();
            system("cls");
        }
        else if (choice == 5) {
            system("cls");
            category_adding_window();
            system("cls");
        }
        else if (choice == 6) {
            system("cls");
            test_adding_window();
            system("cls");
        }
        else if (choice == 7) {
            system("cls");
            question_adding_window();
            system("cls");
        }
        else if (choice == 8) {
            system("cls");
            testing_system.show_statistics();
            system("pause");
            system("cls");
        }
        else if (choice == 9) {
            system("cls");
            test_window();
            system("cls");
        }
        else if (choice == 10) {
            system("cls");
            testing_system.show_results();
            system("pause");
            system("cls");
        }
        else {
            save_all();
            return;
        }
    }
}

void user_menu_window() {
    int ch;
    int correct;
    while (true) {
        system("cls");
        std::cout << "[1]Take Test\n";
        std::cout << "[2]Results\n";
        std::cout << "[Any Other]Save and Exit\n";
        std::cin >> ch;
        if (ch == 1) {
            system("cls");
            test_window();
            system("cls");
        }
        else if (ch == 2) {
            system("cls");
            testing_system.show_results();
            system("pause");
            system("cls");
        }
        else {
            save_all();
            return;
        }
    }
}

void start_window() {
    int choice;
    std::ifstream ifile1("test_data.bin", std::ios::binary);
    testing_system.deserialize_categories(ifile1);
    std::ifstream ifile2("user_data.bin", std::ios::binary);
    testing_system.deserialize_user_collection(ifile2);
    while (true) {
        system("cls");
        std::cout << "[1]Login\n";
        std::cout << "[2]Registrate\n";
        std::cout << "[Any Other]Exit\n";
        std::cin >> choice;
        if (choice == 2) {
            system("cls");
            registrate_user();
            system("cls");
            continue;
        }
        else if (choice == 1) {
            system("cls");
            bool flag = login();
            if (flag && testing_system.is_admin_registered()) {
                system("cls");
                admin_window();
                break;
            }
            else if (flag) {
                system("cls");
                user_menu_window();
                break;
            }
            continue;
        }
        else {
            return;
        }
    }
}


int main()
{
    /*std::ofstream ofile("test_data.bin", std::ios::binary);
    if (ofile.is_open()) {
        testing_system.serialize_categories(ofile);
    }*/
    start_window();
}
