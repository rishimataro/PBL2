#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H

#include <Management/Account.hpp>
#include <Management/listPatient.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>
#include <unordered_map>  // Đảm bảo thêm thư viện này

enum class SearchField { ID, UserName};

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
        int signUp(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole);
        int signIn(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole);
        void forgotPassword(Account &account, const string& tmpUser, const string& tmpPass, const string& tmpRePass);
        bool checkSignIn(const string& userName, const string& password, const int& role, Account &account);
        
        // * Check
        int checkID(const string& ID);
        int checkUserName(const string& userName);
        int checkPassword(const string& password);
        int checkRole(const int& role);

        // * Delete
        void removeAccountByID(const string& ID);

        // * Update
        void updateAccountByID(const string& ID);

        // * Search
        vector<Account> searchAccount(SearchField field, const string& value);
        // vector<Account> searchAccountByID(const string& ID);
};
        Patient getPatientInfoByID(const string& patientID);
#endif
