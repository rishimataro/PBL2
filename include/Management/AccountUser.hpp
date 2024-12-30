#ifndef ACCOUNTUSER_HPP
#define ACCOUNTUSER_HPP
#include <Header/Header.hpp>
#include <Management/Account.hpp>

class AccountUser : public Account
{
    private:
        string ID_patient;
    public:
        //* Constructor & Destructor
        AccountUser(const string ID_acc = "", string userName = "", string password = "", string ID_patient = "");   
        AccountUser(const AccountUser &another);
        virtual ~AccountUser() = default;

        //* Setter
        void setID() override;
        void setID_patient(const string& ID_patient);

        //* Getter
        string getID_patient() const;
        
        //* Function
        // Lấy 1 account từ file
        void readFromFile(const string& line) override;    
        // Lưu 1 account vào file
        void writeToFile(ofstream &f) override;

        //* Operator
        bool operator==(const AccountUser& another);
        bool operator!=(const AccountUser& another);
        AccountUser& operator=(const AccountUser& another);
};  

#endif