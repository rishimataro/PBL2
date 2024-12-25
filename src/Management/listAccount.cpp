#include <Management/listAccount.hpp>
#include <unordered_map>
#include <memory>

// * Constructor & Destructor
listAccount::listAccount() : LinkedList<Account>() {
    this->readListAccountFromFile();
}

listAccount::~listAccount() { 
    // for (int i = 0; i < this->size(); i++) {
    //     delete this->get(i); // Free memory for each account
    // }
    // this->clear(); // Clear all elements from the linked list   
}

// * Setter & Getter
bool listAccount::readListAccountFromFile() {
    string file_path_user = "../Database/AccountDB/accountUser.txt";
    string file_path_admin = "../Database/AccountDB/accountAdmin.txt";
    ifstream finUser(file_path_user), finAdmin(file_path_admin);

    if (!finUser.is_open() || !finAdmin.is_open())
        return false;

    string line;

    while (getline(finUser, line)) {
        if (!line.empty()) {
            auto acc = std::make_unique<AccountUser>();
            acc->readFromFile(line);
            this->append(reinterpret_cast<Account*>(acc.release()));  // Release ownership to the list
        }
    }

    while (getline(finAdmin, line)) {
        if (!line.empty()) {
            auto acc = std::make_unique<AccountAdmin>();
            acc->readFromFile(line);
            this->append(reinterpret_cast<Account*>(acc.release()));  // Release ownership to the list
        }
    }

    finUser.close();
    finAdmin.close();
    return true;
}

bool listAccount::writeListAccountToFile(bool check, bool isUser) {
    if(isUser) {
        string file_path_user = "../Database/AccountDB/accountUser.txt";
        ifstream fiUser(file_path_user);
        char lastChar;
        
        if (fiUser.is_open()) {
            fiUser.seekg(-1, ios::end);  // Di chuyển con trỏ đến cuối tệp
            fiUser.get(lastChar);
            if (lastChar != '\n' && lastChar != '\0') {
                ofstream temp(file_path_user, ios::app);
                temp << "\n";
                temp.close();
            }
            fiUser.close();
        }

        ofstream foUser(file_path_user, check ? ios::trunc : ios::app);
        if (!foUser.is_open()) return false;

        if(check) {
            int totalUser = this->setCountRole(true);
            for (int i = 0; i < totalUser; i++) {
                Account* acc = reinterpret_cast<Account*>(this->get(i));
                acc->writeToFile(foUser);
            }
        } else  {
            Account* acc = reinterpret_cast<Account*>(this->get(this->size() - 1));
            acc->writeToFile(foUser);
        }
        foUser.close();
    }
    else {
        string file_path_admin = "../Database/AccountDB/accountAdmin.txt";
        ifstream fiAdmin(file_path_admin);
        char lastChar;
        
        if (fiAdmin.is_open()) {
            fiAdmin.seekg(-1, ios::end);  // Di chuyển con trỏ đến cuối tệp
            fiAdmin.get(lastChar);
            if (lastChar != '\n' && lastChar != '\0') {
                ofstream temp(file_path_admin, ios::app);
                temp << "\n";
                temp.close();
            }
            fiAdmin.close();
        }

        ofstream foAdmin(file_path_admin, check ? ios::trunc : ios::app);
        if (!foAdmin.is_open()) return false;

        if(check) {
            // int totalAdmin = this->setCountRole(false), total = this->size();   
            int totalUser = this->setCountRole(true), total = this->size(); 
            for (int i = totalUser; i < total; i++) {
                Account* acc = reinterpret_cast<Account*>(this->get(i));
                acc->writeToFile(foAdmin);
            }
        } else  {
            Account* acc = reinterpret_cast<Account*>(this->get(this->size() - 1));
            acc->writeToFile(foAdmin);
        }
        foAdmin.close();
    }

    return true;
}

int listAccount::setCountRole(bool isUser) {
    string role = isUser ? "USER" : "ADMIN";
    int count = 0;
    if(this->size() == 0)
        return count;

    for (int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (acc->getID().rfind(role, 0) == 0)
            count++;
    }

    return count;
}

vector<Account*> listAccount::setAccountByRole(bool isUser) {
    vector<Account*> result;
    if(this->size() == 0)
        return result;

    string role = isUser ? "USER" : "ADMIN";

    for (int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (this->checkRole(acc->getID(), role))
            result.push_back(acc);
    }

    return result;
}

vector<Account*> listAccount::setAllAccount() {
    vector<Account*> result;
    if(this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        result.push_back(acc);
    }   

    return result;
}

// * Sign Up & Sign In
int listAccount::signUp(Account* &account, const string &tmpUserName, const string &tmpPassword) {
    if (checkUserName(tmpUserName) != -1)
        return -1;

    auto newAccount = std::make_unique<AccountUser>();
    newAccount->setID();
    newAccount->setUserName(tmpUserName);
    newAccount->setPassword(tmpPassword);

    this->append(reinterpret_cast<Account*>(newAccount.release())); // Release ownership to the list
    this->writeListAccountToFile(false, true);
    account = newAccount.release(); // Transfer ownership to account
    return 1;
}
int listAccount::allocateAdminAccount(Account* &account, const string &tmpUserName, const string &tmpPassword)
{
    if (checkUserName(tmpUserName) != -1)
        return -1;

    auto newAccount = std::make_unique<AccountAdmin>();
    newAccount->setID();
    newAccount->setUserName(tmpUserName);
    newAccount->setPassword(tmpPassword);

    this->append(reinterpret_cast<Account*>(newAccount.release())); // Release ownership to the list
    this->writeListAccountToFile(false, false);
    account = newAccount.release(); // Transfer ownership to account
    return 1;
}

int listAccount::signIn(Account* &account, const string &tmpUserName, const string &tmpPassword) {
    if(!checkSignIn(tmpUserName, tmpPassword, account))
        return -1;

    return account->getID().rfind("USER", 0) == 0 ? 1 : 0;
}

bool listAccount::checkSignIn(const string &userName, const string &password, Account* &account)
{
    for(int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (acc->getUserName() == userName && acc->getPassword() == password) {
            account = acc;
            return true;
        }
    }

    return false;
}

int listAccount::forgotPassword(Account* &account, const string &tmpCCCD, const string &tmpUser, const string &tmpPass, const string &tmpRePass)
{
    int index = checkCCCD(tmpCCCD);
    if (index == -1)
        return -1;

    AccountUser* currentAccount = reinterpret_cast<AccountUser*>(this->get(index));
    if (currentAccount->getUserName() != tmpUser)
        return -2;

    if (tmpPass != tmpRePass)
        return -3;

    currentAccount->setPassword(tmpPass);
    this->set(index, currentAccount);
    this->writeListAccountToFile(true, true);
    
    account = currentAccount;
    return 1;
}

// * Check
int listAccount::checkCCCD(const string &CCCD)
{
    for (int i = 0; i < this->size(); i++) {
        AccountUser* acc = reinterpret_cast<AccountUser*>(this->get(i));
        if (acc->getCCCD() == CCCD) {
            return i;
        }
    }
    return -1;
}

int listAccount::checkID(const string &ID) {
    for (int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (acc->getID() == ID) {
            return i;
        }
    }
    return -1;
}

int listAccount::checkUserName(const string &userName) {
    for(int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (acc->getUserName() == userName) {
            cout << acc->getUserName() << endl;
            return i;
        }
    }
    return -1;
}

int listAccount::checkPassword(const string &password)
{
    for (int i = 0; i < this->size(); i++) {
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        if (acc->getPassword() == password) {
            return i;   
        }
    }
    return -1;
}

bool listAccount::checkRole(const string &id, const string &role)
{
    return id.rfind(role, 0) == 0;
}

// * Delete
bool listAccount::removeAccountByID(const string &ID)
{
    int index = this->checkID(ID);
    if (index == -1) return false;

    this->remove(index);
    this->writeListAccountToFile(true, ID.rfind("USER", 0) == 0);
    return true;
}

//* Update Account
bool listAccount::updateAccountByID(const string &ID, const string &newUserName, const string &newPwd) {
    int index = this->checkID(ID);
    if (index == -1) return false;

    Account* currentAccount = this->get(index);

    if (dynamic_cast<AccountUser*>(currentAccount)) {
        auto* accountUser = dynamic_cast<AccountUser*>(currentAccount);
        accountUser->setUserName(newUserName);
        accountUser->setPassword(newPwd);
    } else if (dynamic_cast<AccountAdmin*>(currentAccount)) {
        auto* accountAdmin = dynamic_cast<AccountAdmin*>(currentAccount);
        accountAdmin->setUserName(newUserName);
        accountAdmin->setPassword(newPwd);
    } else return false;

    bool isUser = checkRole(ID, "USER");
    return this->writeListAccountToFile(true, isUser);
}

// * Search (tuong doi)
vector<Account*> listAccount::searchAccount(SearchField_acc field, const string &value)
{
    vector<Account*> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++) {
        string fieldValue;
        Account* acc = reinterpret_cast<Account*>(this->get(i));
        switch (field) {
        case SearchField_acc::ID:
            fieldValue = toLowerCase(acc->getID());
            break;
        case SearchField_acc::UserName:
            fieldValue = toLowerCase(acc->getUserName());
            break;
        }

        if (fieldValue.find(lowerValue) == 0) {
            result.push_back(acc);
        }
    }

    return result;
}