#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H
#include "./Single/Account.h"
#include "../Template/LinkedList.cpp"
#include "../Library/Header.h"

class listAccount : public LinkedList<Account>
{
    public:
        // * Constructor & Destructor  
        listAccount();
        ~listAccount();

        // * Setter & Getter
        void setListAccountByFile();
        void saveListAccountToFile();

        // * Display
        void printAccountByID();
        void printAllAccount();

        // * Sign Up & Sign In
        void signUp(Account &account);
        void signIn(Account &account);
        bool checkSignIn(const string& id, const string& password, Account &account);
        
        // * Check
        bool checkID(const string& ID);
        bool checkUserName(const string& userName);
        bool checkPassword(const string& password);
        bool checkRole(const int& role);

        // * Delete
        void removeAccountByID(const string& ID);

        // * Update
        void updateAccountByID(const string& ID);

        // * Search
        void searchAccountByID(const string& id);
        void searchAccountByUserName(const string& userName);
};

#endif