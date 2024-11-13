#include <Management/Account.hpp>
int safe_stoi(const std::string &str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << std::endl;
        return 0; // Giá trị mặc định hoặc xử lý lỗi
    }
}

//* Constructor & Destructor
Account::Account(const string ID_acc, string userName, string password, int role)
{
    this->ID_acc = ID_acc;
    this->userName = userName;
    this->password = password;
    this->role = role;
}

Account::Account(const Account &another)
{
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
    this->role = another.role;
}

Account::~Account() {}

//* Setter
void Account::setID(const string &ID_acc) { this->ID_acc = ID_acc; }
void Account::setPassword(const string &password) { this->password = password; }
void Account::setUserName(const string &userName) { this->userName = userName; }
void Account::setRole(const int &role) { this->role = role; }

//* Getter
string Account::getID() const { return this->ID_acc; }
string Account::getPassword() const { return this->password; }
string Account::getUserName() const { return this->userName; }
int Account::getRole() const { return this->role; }
string Account::getRoleToString() const { 
    string roleStr;
    if(this->role == 0) roleStr = "Quản trị viên";
    else if(this->role == 1) roleStr = "Bác sĩ";
    else if(this->role == 2) roleStr = "Bệnh nhân";
    return roleStr; 
}

//* Function
// Lấy 1 account từ file
void Account::readPatientFromFile(const string& line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ';'); this->ID_acc = token;
    getline(ss, token, ';'); this->userName = token;
    getline(ss, token, ';'); this->password = token;
    getline(ss, token, ';'); this->role = safe_stoi(token);
}

// Lưu 1 account vào file
void Account::writeAccountToFile(ofstream &f) {
    string data;

    data.append(this->ID_acc + ";");
    data.append(this->userName + ";");
    data.append(this->password + ";");
    data.append(to_string(this->role) + "\n");

    f << data;
}

bool Account::operator==(const Account& another) {
    return this->ID_acc == another.getID() && this->userName == another.getUserName()
            && this->password == another.getPassword() && this->role == another.getRole();
}

Account& Account::operator=(const Account& another) {
    if (this == &another) {
        return *this; 
    }

    this->ID_acc = another.getID();
    this->userName = another.getUserName();
    this->password = another.getPassword();
    this->role = another.getRole();
    return *this;
}