#ifndef ACCOUNTADMIN_H
#define ACCOUNTADMIN_H
#include <Header/Header.hpp>
#include <Management/Account.hpp>

class AccountAdmin : public Account
{
    public:
        //* Constructor & Destructor
        AccountAdmin(const string ID_acc = "", string userName = "", string password = "");   
        AccountAdmin(const AccountAdmin &another);
        virtual ~AccountAdmin() = default;

        //* Setter
        void setID() override;

        //* Function
        // Lấy 1 account từ file
        void readFromFile(const string& line) override;    
        // Lưu 1 account vào file
        void writeToFile(ofstream &f) override;

        //* Operator
        bool operator==(const AccountAdmin& another);
        bool operator!=(const AccountAdmin& another);
        AccountAdmin& operator=(const AccountAdmin& another);
};

#endif