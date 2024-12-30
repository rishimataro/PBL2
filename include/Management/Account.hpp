#ifndef ACCOUNT_H
#define ACCOUNT_H   
#include <Header/Header.hpp>
#include <Library/Graphics.hpp>
#include <Management/Patient.hpp>

class Account
{
    protected:
        string ID_acc;
        string userName;
        string password;
    public:
        //* Constructor & Destructor
        Account(const string ID_acc = "", string userName = "", string password = "");   
        Account(const Account &another);
        virtual ~Account() = default;

        //* Setter
        virtual void setID() = 0;
        void setPassword(const string& password);
        void setUserName(const string& userName);

        //* Getter
        string getID() const;
        string getPassword() const;
        string getUserName() const;

        //* Function
        // Lấy 1 account từ file
        virtual void readFromFile(const string& line) = 0;    
        // Lưu 1 account vào file
        virtual void writeToFile(ofstream &f) = 0;

        //* Operator
        virtual bool operator==(const Account& another);
        virtual bool operator!=(const Account& another);
        virtual Account& operator=(const Account& another);
};

#endif