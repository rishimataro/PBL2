#include <Management/Account.h>

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
// Nhập 1 account
void Account::inputAccount() {
    int x = whereX(), y = whereY();

    gotoXY(x + 12, y + 1); cout << this->ID_acc;
    gotoXY(x + 12, y + 4); cin >> this->userName;
    gotoXY(x + 12, y + 7); cin >> this->password;
    gotoXY(x + 12, y + 10); cout << this->getRoleToString();
}

// Lấy 1 account từ file
void Account::setAccount(const string& line)
{
    stringstream ss(line);
    string token;
    getline(ss, token, ';'); this->ID_acc = token;
    getline(ss, token, ';'); this->userName = token;
    getline(ss, token, ';'); this->password = token;
    getline(ss, token, ';'); this->role = stoi(token);
}

// Lưu 1 account vào file
void Account::saveAccount(fstream &f)
{
    f << this->ID_acc << ";" << this->userName << ";" << this->password << ";" << this->role << endl;
}

// In thông tin 1 account (ngang)
void Account::printAccountHorizontal()
{
   int x = whereX(), y = whereY();
   gotoXY(x + 4, y);
   cout << this->ID_acc;
   gotoXY(x + 16, y);
   cout << this->userName;
   gotoXY(x + 41, y);
   cout << this->password;
   gotoXY(x + 61, y);
   cout << getRoleToString() << endl;
}

void Account::printAccountVertical() {
    int x = whereX(), y = whereY();
    gotoXY(x + 12, y + 1);
    cout << this->ID_acc;
    gotoXY(x + 12, y + 4);
    cout << this->userName;
    gotoXY(x + 12, y + 7);
    cout << this->password;
    gotoXY(x + 12, y + 10);
    cout << getRoleToString() << endl;
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