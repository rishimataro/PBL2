#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H

#include <Management/Account.hpp>
#include <Management/listPatient.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>
#include <unordered_map>  // Đảm bảo thêm thư viện này

enum class SearchField { ID, UserName};

enum class SearchField_acc { ID, UserName};

class listAccount : public LinkedList<Account>
{
    
    private:
    
        std::unordered_map<std::string, Account> idMap;          // Bảng băm lưu trữ theo ID
        std::unordered_map<std::string, Account> userNameMap
        ;    // Bảng băm lưu trữ theo UserName

    public:
        // * Constructor & Destructor  
        listAccount();
        ~listAccount();

        // * Setter & Getter
        int setCountRole(int role);
        bool readListAccountFromFile();
        bool writeListAccountToFile(bool check);

        vector<Account> setAccountByRole(int role);
        vector<Account> setAllAccount();

        // * Sign Up & Sign In
<<<<<<< HEAD
        int signUp(Account &account, const string &tmpUserName, const string &tmpPassword);
        int signIn(Account &account, const string &tmpUserName, const string &tmpPassword);
        int forgotPassword(Account &account, const string &tmpCCCD, const string &tmpUser, const string &tmpPass, const string &tmpRePass);
        bool checkSignIn(const string &userName, const string &password, Account &account);
=======
        int signUp(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole);
        int signIn(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole);
        void forgotPassword(Account &account, const string& tmpUser, const string& tmpPass, const string& tmpRePass);
        bool checkSignIn(const string& userName, const string& password, const int& role, Account &account);
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
        
        // * Check
        int checkCCCD(const string& CCCD);
        int checkID(const string& ID);
        int checkUserName(const string& userName);
        int checkPassword(const string& password);
        int checkRole(const int& role);

        // * Delete
        void removeAccountByID(const string& ID);

        // * Update
        void updateAccountByID(const string &ID, const string &newUserName, const string &newPwd);

        // * Search
<<<<<<< HEAD
        vector<Account> searchAccount(SearchField_acc field, const string& value);
};
=======
        vector<Account> searchAccount(SearchField field, const string& value);
        // vector<Account> searchAccountByID(const string& ID);
};
        Patient getPatientInfoByID(const string& patientID);
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
#endif
