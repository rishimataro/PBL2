#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H

#include <Management/Account.hpp>
#include <Management/AccountUser.hpp>
#include <Management/AccountAdmin.hpp>
#include <Management/listPatient.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>

enum class SearchField_acc { ID, UserName};

class listAccount : public LinkedList<Account>
{
    public:
        // * Constructor & Destructor  
        listAccount();
        ~listAccount();

        // * Setter & Getter
        int setCountRole(bool isUser);
        bool readListAccountFromFile();
        bool writeListAccountToFile(bool check, bool isUser);

        vector<Account*> setAccountByRole(bool isUser);
        vector<Account*> setAllAccount();

        // * Sign Up & Sign In
        int signUp(Account* &account, const string &tmpUserName, const string &tmpPassword);
        int addAdmin(Account &account, const string &tmpUserName, const string &tmpPassword);
        int signIn(Account* &account, const string &tmpUserName, const string &tmpPassword);
        int forgotPassword(Account* &account, const string &tmpCCCD, const string &tmpUser, const string &tmpPass, const string &tmpRePass);
        bool checkSignIn(const string &userName, const string &password, Account* &account);

        // * Check
        int checkCCCD(const string& CCCD);
        int checkID(const string& ID);
        int checkUserName(const string& userName);
        int checkPassword(const string& password);
        bool checkRole(const string& id, const string& role);

        // * Delete
        bool removeAccountByID(const string& ID);

        // * Update
        bool updateAccountByID(const string &ID, const string &newUserName, const string &newPwd);

        // * Search
        vector<Account*> searchAccount(SearchField_acc field, const string& value);
};
#endif
