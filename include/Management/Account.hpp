#ifndef ACCOUNT_H
#define ACCOUNT_H   
#include <Header/Header.hpp>
#include <Library/Graphics.hpp>
#include <Management/Patient.hpp>

class Account
{
    private:
        string ID_acc;
        string userName;
        string password;
        int role; // 0: Admin, 1: Bệnh nhân
        string ID_patient;
    public:
        //* Constructor & Destructor
        Account(const string ID_acc = "", string userName = "", string password = "",  int role = 0, string ID_patient = "");   
        Account(const Account &another);
        ~Account();

        //* Setter
        void setID();
        void setPassword(const string& password);
        void setUserName(const string& userName);
        void setRole(const int& role);
        void setID_patient(const string& ID_patient);

        //* Getter
        string getID() const;
        string getPassword() const;
        string getUserName() const;
        int getRole() const;
        string getRoleToString() const;
        string getID_patient() const;   
        string getCCCD() const;

        //* Function
        // Lấy 1 account từ file
        void readAccountFromFile(const string& line);    
        // Lưu 1 account vào file
        void writeAccountToFile(ofstream &f);

        //* Operator
        bool operator==(const Account& another);
        bool operator!=(const Account& another);
        Account& operator=(const Account& another);
};

#endif