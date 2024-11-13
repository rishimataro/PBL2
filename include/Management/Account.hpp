#ifndef ACCOUNT_H
#define ACCOUNT_H   
#include <Header/Header.hpp>
#include <Library/Graphics.hpp>

class Account
{
    private:
        string ID_acc;
        string userName;
        string password;
        int role;
    public:
        //* Constructor & Destructor
        Account(const string ID_acc = "", string userName = "", string password = "",  int role = 0);
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
        string getRoleToString() const;

        //* Function
        // Lấy 1 account từ file
        void readPatientFromFile(const string& line);    
        // Lưu 1 account vào file
        void writeAccountToFile(ofstream &f);

        //* Operator
        bool operator==(const Account& another);
        Account& operator=(const Account& another);
};

#endif