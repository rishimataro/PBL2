#ifndef ACCOUNT_H
#define ACCOUNT_H   
#include <Header/Header.h>

class Account
{
    private:
        string ID_acc;
        string userName;
        string password;
        int role;
    public:
        //* Constructor & Destructor
        Account(string ID_acc = "", string userName = "", string password = "",  int role = 0);
        Account(const Account &another);
        ~Account();

        //* Setter
        void setID(const string& ID_acc);
        void setPassword(const string& password);
        void setUserName(const string& userName);
        void setRole(const int& role);

        //* Getter
        string getID() const;
        string getPassword() const;
        string getUserName() const;
        int getRole() const;

        //* Function
        // Nhập 1 account
        void inputAccount();
        // Lấy 1 account từ file
        void setAccount(const string& line);    
        // Lưu 1 account vào file
        void saveAccount(fstream &f);
        // In thông tin 1 account
        void printAccount();
};

#endif