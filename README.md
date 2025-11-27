# 📝 Testing System

A robust C++-based interactive testing platform that enables administrators to create and manage quizzes while users answer questions in real-time and view their statistics and results.  Built with modern C++ and STL containers for efficient data management.


## ✨ Features

### For Administrators
- 👥 **User Management**: Register new users and delete existing accounts
- 📚 **Category Management**: Create and organize test categories
- ✏️ **Test Creation**: Design custom tests with multiple questions
- ❓ **Question Builder**: Add questions with 2-4 answer options
- 📊 **Statistics Dashboard**: View comprehensive user performance analytics
- 🔐 **Account Management**: Change login credentials and passwords
- 🎯 **Test Taking**: Administrators can also take tests

### For Regular Users
- 📝 **Take Tests**: Access available tests and answer questions
- 📈 **View Results**: Check test scores and performance history
- 🔒 **Secure Authentication**: Password hashing for account security
- 👤 **User Profile**: Personal information management

### System Features
- 🔐 **Password Security**: Hash-based password storage using std::hash
- 💾 **Data Persistence**: Binary file serialization for users and tests
- 🎯 **Real-time Testing**: Interactive question-answer interface
- 📊 **Result Tracking**: Comprehensive test result storage
- 🗂️ **Organized Structure**: Category → Test → Question hierarchy

## 🏗️ Architecture

The system follows an object-oriented design with separate entities:

### Core Classes

1. **System** - Main controller class managing all operations
2. **User** - User account information and authentication
3. **Category** - Test category container
4. **Test** - Individual test with multiple questions
5. **Question** - Question with multiple answer choices
6. **TestResult** - Stores test scores and statistics

### Class Hierarchy
```
System
├── User Collection (unordered_map)
├── Category Collection (vector)
    └── Test Collection
        └── Question Collection
            └── Answer Options
```

## 🛠️ Tech Stack

- **Language**: C++ (100%)
- **IDE**: Visual Studio
- **Build System**: MSBuild (. sln, .vcxproj)
- **Standard Library**: STL (Standard Template Library)
- **Data Structures**: 
  - `std::unordered_map` for user storage
  - `std::vector` for categories, tests, and questions
  - `std::hash` for password encryption
- **Persistence**: Binary file I/O (`std::ofstream`, `std::ifstream`)

## 📋 Prerequisites

- Windows Operating System
- Visual Studio 2017 or later
- C++11 or higher compiler support
- Basic understanding of C++ and OOP concepts

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/mirce085/Testing-System.git
cd Testing-System
```

### 2.  Open in Visual Studio

1. Double-click `Step_stl.sln` to open the solution in Visual Studio
2. Or open Visual Studio → File → Open → Project/Solution → Select `Step_stl.sln`

### 3. Build the Project

1. Select **Build** → **Build Solution** (or press `Ctrl+Shift+B`)
2.  Ensure the build configuration is set to **Debug** or **Release**

### 4. Run the Application

1. Press `F5` to run with debugging or `Ctrl+F5` to run without debugging
2. The console application will launch with the main menu

## 📁 Project Structure

```
Testing-System/
├── Category.h          # Category class declaration
├── Category.cpp        # Category class implementation
├── Question.h          # Question class declaration
├── Question.cpp        # Question class implementation
├── Test.h              # Test class declaration
├── Test.cpp            # Test class implementation
├── TestResult.h        # TestResult class declaration
├── TestResult.cpp      # TestResult class implementation
├── User.h              # User class declaration
├── User.cpp            # User class implementation
├── System.h            # Main system controller declaration
├── System.cpp          # Main system controller implementation
├── Step_stl.cpp        # Main program entry point and UI
├── Step_stl.sln        # Visual Studio solution file
├── Step_stl.vcxproj    # Visual Studio project file
├── user_data.bin       # User data storage (binary)
├── test_data.bin       # Test data storage (binary)
├── . gitignore
└── . gitattributes
```

## 🎮 Usage Guide

### First Time Setup

1. **Register an Account**:
   - Select `[2] Registrate` from the main menu
   - Enter login, name, surname, phone number
   - Create a password (confirm twice)

2. **Login**:
   - Select `[1] Login`
   - Enter your credentials
   - System detects if you're an admin automatically

### Administrator Menu

```
[1] Registrate New User    - Add new users to the system
[2] Delete User            - Remove existing users
[3] Change Login           - Update username
[4] Change Password        - Update password
[5] Add Category           - Create new test category
[6] Add Test               - Add test to existing category
[7] Add Question           - Add question to existing test
[8] Show Statistics        - View all user performance data
[9] Take Test              - Answer test questions
[10] Show Results          - View your test results
```

### User Menu

```
[1] Take Test    - Select and complete a test
[2] Results      - View your test history and scores
```

### Creating a Test (Admin)

1. **Add Category**: Choose option `[5]` and enter category name
2. **Create Test**: Enter test name and begin adding questions
3. **Add Questions**: 
   - Enter question text
   - Add 2-4 answer options
   - Specify correct answer number
   - Repeat for multiple questions
4. **Save**: Exit menus to auto-save

### Taking a Test

1. Select `[9]` (Admin) or `[1]` (User) from menu
2. Choose a category from available options
3. Select a test
4. Answer each question by entering the option number
5. View your score upon completion

## 💾 Data Persistence

The system uses binary file serialization:

- **user_data.bin**: Stores all user accounts and credentials
- **test_data.bin**: Stores categories, tests, and questions

Data is automatically:
- ✅ Loaded on program startup
- ✅ Saved when exiting menus
- ✅ Preserved between sessions

## 🔐 Security Features

- **Password Hashing**: Uses `std::hash<std::string>` for password encryption
- **Login Validation**: Verifies credentials before granting access
- **Role-Based Access**: Admin privileges for user and content management
- **Secure Storage**: Hashed passwords stored in binary format

## 📊 Key Functionalities

### User Management
- Registration with validation (unique logins)
- Login authentication with hashed passwords
- Profile modification (login, password)
- User deletion by administrators

### Content Management
- Hierarchical structure: Category → Test → Question
- Dynamic question creation (2-4 answers per question)
- Flexible test building interface
- Category organization

### Testing & Results
- Interactive test-taking interface
- Real-time answer validation
- Score calculation and storage
- Historical result tracking
- Statistics viewing for all users

## 🔧 Technical Implementation

### Data Structures Used

```cpp
// User storage
std::unordered_map<std::string, User> m_users;

// Category and test hierarchy
std::vector<Category> m_categories;

// Password hashing
std::hash<std::string> hash_engine;
```

### Serialization
Binary file I/O for efficient data storage and retrieval:
```cpp
void serialize_user_collection(std::ofstream& ofile);
void deserialize_user_collection(std::ifstream& ifile);
void serialize_categories(std::ofstream& ofile);
void deserialize_categories(std::ifstream& ifile);
```

## 🚧 Future Enhancements

- [ ] Timed tests with countdown functionality
- [ ] Question randomization
- [ ] Multiple correct answers support
- [ ] Export results to CSV/PDF
- [ ] Database integration (SQLite)
- [ ] GUI implementation (Qt/WinForms)
- [ ] Enhanced encryption (SHA-256, bcrypt)
- [ ] Question image support
- [ ] Category filtering and search
- [ ] Leaderboard system
- [ ] Test difficulty levels
- [ ] Question pools and random selection

## 🎓 Educational Value

This project demonstrates:
- Object-Oriented Programming principles
- STL container usage (`unordered_map`, `vector`)
- File I/O and serialization
- Hash-based authentication
- Menu-driven console application design
- Data persistence strategies
- Class relationships and composition
- Exception handling

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2.  Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 Code Standards

- Follow C++ naming conventions
- Use meaningful variable names
- Comment complex logic
- Maintain class encapsulation
- Handle exceptions appropriately

## 📧 Contact

**Developer**: [mirce085](https://github.com/mirce085)

For questions, bug reports, or feature requests, please open an issue on GitHub.

## 📄 License

This project is maintained by mirce085.  Check the repository for license information. 

---

📚 **Test your knowledge with a robust testing platform! ** 🎯

Built with ❤️ using C++ and Visual Studio
