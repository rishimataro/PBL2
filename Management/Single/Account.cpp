#include "./Account.h"

//* Constructor & Destructor
Account::Account(string ID_acc, string userName, string password, int role)
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

//* Function

// Nhập 1 account
void Account::inputAccount() {
    int x = 60, y = 5, w = 30, h = 2;
    box_(x, y - 3, w, h, 12, 14, 12, "       USER INFORMATION");
    box(x, y + 2, w, h, 15, 1, 15, "  ID       : "); 
    box(x, y + 4, w, h, 15, 1, 15, "  TAI KHOAN: "); 
    box(x, y + 6, w, h, 15, 1, 15, "  MAT KHAU : "); 
    box(x, y + 8, w, h, 15, 1, 15, "  VAI TRO  : "); 

    for(int i = 2; i <= 4; i ++ ){
        gotoXY(x, y + (i*2)); cout << char(195);
        gotoXY(x + w, y + (i*2)); cout << char(180);
    }

    gotoXY(x + 14, y + 3); cin >> this->ID_acc;
    gotoXY(x + 14, y + 5); cin >> this->userName;
    gotoXY(x + 14, y + 7); cin >> this->password;
    gotoXY(x + 14, y + 9); cin >> this->role;
}

// Lấy 1 account từ file
void Account::setAccount(fstream &f)
{
    string roleStr;
    getline(f, this->ID_acc, ';');
    getline(f, this->userName, ';');
    getline(f, this->password, ';');
    getline(f, roleStr, ';');

    // Chuyển đổi từ chuỗi sang số nguyên
    this->role = stoi(roleStr);
}

// Lưu 1 account vào file
void Account::saveAccount(fstream &f)
{
    f << this->ID_acc << ";" << this->userName << ";" << this->password << ";" << this->role << endl;
}

// In thông tin 1 account
void Account::printAccount()
{
    int x = 60, y = 5, w = 30, h = 2;
    box_(x, y - 3, w, h, 12, 14, 12, "       USER INFORMATION");
    box(x, y + 2, w, h, 15, 1, 15, "  ID       : " + this->ID_acc);
    box(x, y + 4, w, h, 15, 1, 15, "  TAI KHOAN: " + this->userName);
    box(x, y + 6, w, h, 15, 1, 15, "  MAT KHAU : " + this->password);
    box(x, y + 8, w, h, 15, 1, 15, "  VAI TRO  : " + to_string(this->role));

    for(int i = 2; i <= 4; i ++ ){
        gotoXY(x, y + (i*2)); cout << char(195);
        gotoXY(x + w, y + (i*2)); cout << char(180);
    }
}