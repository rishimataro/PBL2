#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H

#include <Management/Account.hpp>
#include <Management/listPatient.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>

enum class SearchField { ID, UserName};

class listAccount : public LinkedList<Account>
{
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
        int checkCCCD(const string& CCCD);
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
};
#endif
