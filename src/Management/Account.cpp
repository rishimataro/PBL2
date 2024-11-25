#include <Management/Account.hpp>

//* Constructor & Destructor
Account::Account(const string ID_acc, string userName, string password)
{
    this->ID_acc = ID_acc;
    this->userName = userName;
    this->password = password;
}

Account::Account(const Account &another)
{
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
}

// * Setter
void Account::setPassword(const string &password) { this->password = password; }
void Account::setUserName(const string &userName) { this->userName = userName; }

//* Getter
string Account::getID() const { return this->ID_acc; }
string Account::getPassword() const { return this->password; }
string Account::getUserName() const { return this->userName; }

bool Account::operator==(const Account& another) {
    return this->ID_acc == another.getID() && this->userName == another.getUserName()
            && this->password == another.getPassword();
}

bool Account::operator!=(const Account& another) {
    return !(*this == another);
}

Account& Account::operator=(const Account& another) {
    if (this == &another) {
        return *this; 
    }
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
    return *this;
}