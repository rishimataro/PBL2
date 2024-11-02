#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H
#include <Management/Account.hpp>
#include <Template/LinkedList.hpp>
#include <Header/Header.hpp>

class listAccount : public LinkedList<Account>
{
    public:
        // * Constructor & Destructor  
        listAccount();
        ~listAccount();

        // * Setter & Getter
        int setCountRole(int role);
        void setListAccountByFile();
        void saveListAccountToFile();

        // * Display
        void printAccountByRole(int role);
        void printAllAccount();

        // * Sign Up & Sign In
        void signUp(Account &account);
        void signIn(Account &account);
        void forgotPassword(Account &account);
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
        void searchAccountByID(const string& ID);
        void searchAccountByUserName(const string& userName);
};

#endif