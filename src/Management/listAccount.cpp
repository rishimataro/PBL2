#include <Management/listAccount.hpp>
#include <unordered_map>

// * Constructor & Destructor
listAccount::listAccount() {
    this->head = NULL;
}

<<<<<<< HEAD
listAccount::~listAccount()
{
    if (this->head == NULL)
        return;
=======
listAccount::~listAccount() {
    if (this->head == NULL) return;
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c

    Node<Account> *current = this->head;
    Node<Account> *tail = this->head->prev;

    do
    {
        Node<Account> *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

// * Setter & Getter
<<<<<<< HEAD
int listAccount::setCountRole(int role)
{
    int left = 0;
    int right = this->size() - 1;
    int count = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (this->get(mid).getRole() < role)
        {
            left = mid + 1;
        }
        else if (this->get(mid).getRole() > role)
        {
            right = mid - 1;
        }
        else
        {
            int start = mid;
            while (start >= 0 && this->get(start).getRole() == role)
            {
                count++;
                start--;
            }
            int end = mid + 1;
            while (end < this->size() && this->get(end).getRole() == role)
            {
                count++;
                end++;
            }
            break;
        }
=======
int listAccount::setCoif (accountsByRole.find(role) != accountsByRole.end()) {
            return accountsByRole[role].size();
        }
        return 0;
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    }

    return count;
}

<<<<<<< HEAD
// * done
bool listAccount::readListAccountFromFile()
{
    string file_path = "../Database/AccountDB/account.txt";
    ifstream fin;
    Account account;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;
=======
// ! Sửa lại hàm này
// * done
bool listAccount::readListAccountFromFile()
{
    string file_path = "./Database/AccountDB/account.txt";
    fstream fin;
    Account account;

    fin.open(file_path, ios::in);
    if (!fin.is_open()) return false;
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        account.readAccountFromFile(line);
        this->append(account);
        idMap[account.getID()] = account;
        userNameMap[account.getUserName()] = account;
    }
    fin.close();
    return true;
}

<<<<<<< HEAD
//* done
bool listAccount::writeListAccountToFile(bool check)
{
    string file_path = "../Database/AccountDB/account.txt";
    char ch;

    ofstream fo;
    if (check)
    {
        if (std::remove(file_path.c_str()) != 0)
            return false;
        fo.open(file_path, ios::trunc);
    }
    else
    {
        fo.open(file_path, ios::app);
    }

    if (!fo.is_open())
        return false;

    Account account;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
=======
// ! Sửa lại hàm này
//* done
bool listAccount::writeListAccountToFile(bool check)
{
    string file_path = "./Database/AccountDB/account.txt";
    char ch;

    ifstream fi(file_path);
    if (fi.is_open())
    {
        fi.seekg(-1, ios::end);
        fi.get(ch);
        if (ch != '\n' && ch != '\0')
        {
            ofstream temp(file_path, ios::app);
            temp << "\n";
            temp.close();
        }
        fi.close();
    }

    ofstream fo(file_path, ios::app);
    if (!fo.is_open()) return false;

    Account account;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
            account = this->get(i);
            account.writeAccountToFile(fo);
        }
    }
    else
    {
        account = this->get(this->size() - 1);
        account.writeAccountToFile(fo);
    }

    fo.close();
    return true;
}

<<<<<<< HEAD

=======
// ! Sửa lại hàm này
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
//* done
vector<Account> listAccount::setAccountByRole(int role)
{
    vector<Account> result;
<<<<<<< HEAD
    if (this->size() == 0)
        return result;

    for(int i = 0; i < this->size(); i++) {
        if(this->get(i).getRole() == role) {
            result.push_back(this->get(i));
        }
    }
    return result;
}

=======
    if(this->size() == 0) return result;

    copy_if(this->begin(), this->end(), back_inserter(result),
                 [role](const Account& account) { return account.getRole() == role; });

    return result;
}

// ! Sửa lại hàm này
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
//* done
vector<Account> listAccount::setAllAccount()
{
    vector<Account> result;
<<<<<<< HEAD
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++) {
        result.push_back(this->get(i));
    }

=======
    if(this->size() == 0) return result;

    copy(this->begin(), this->end(), back_inserter(result));
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    return result;
}

// * Sign Up & Sign In
<<<<<<< HEAD
// Đăng ký tài khoản: thêm account vào listAccount
int listAccount::signUp(Account &account, const string &tmpUserName, const string &tmpPassword)
{
    if (checkUserName(tmpUserName) != -1)
        return -1;
 
    Account newAccount;
    newAccount.setID();
    newAccount.setUserName(tmpUserName);
    newAccount.setPassword(tmpPassword);
    newAccount.setRole(1);

    this->append(newAccount);
    this->writeListAccountToFile(false);

    return 1;
    //! Sau hàm này gọi hàm addPatient() để nhập thông tin bệnh nhân, 
    //! và gọi setID_patient(setID()) để set ID_patient cho account
}

// Đăng nhập: kiểm tra thông tin đăng nhập
int listAccount::signIn(Account &account, const string &tmpUserName, const string &tmpPassword)
{
    if (checkSignIn(tmpUserName, tmpPassword, account))
        return account.getRole();
    return -1;
}

bool listAccount::checkSignIn(const string &userName, const string &password, Account &account)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getUserName() == userName && this->get(i).getPassword() == password)
        {
            account = this->get(i);
            return true;
        }
=======
// string enterPassword()
// {
//     string pw;
//     char ch;
//     while ((ch = _getch()) != '\r')
//     {
//         if (ch == '\b' && pw.length() > 0)
//         {
//             cout << "\b \b";
//             pw.pop_back();
//         }
//         else if (ch != '\b')
//         {
//             cout << "●";
//             pw.push_back(ch);
//         }
//     }
//     return pw;
// }

// ! Sửa lại hàm này
// Đăng ký tài khoản
void listAccount::signUp(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole) {
    account.setUserName(tmpUserName);
    account.setPassword(tmpPassword);
    account.setRole(tmpRole);
    this->append(account);
    idMap[account.getID()] = account;
    userNameMap[account.getUserName()] = account;
}

// ! Sửa lại hàm này
void listAccount::signIn(Account &account, const string& tmpUserName, const string& tmpPassword, const int& tmpRole) {
    auto it = userNameMap.find(tmpUserName);
    if (it != userNameMap.end() && it->second.getPassword() == tmpPassword && it->second.getRole() == tmpRole) {
        account = it->second;
    }
}

bool listAccount::checkSignIn(const string &userName, const string &password, const int &role, Account &account)
{
    auto it = find_if(this->begin(), this->end(),
                           [&userName, &password, &role](const Account &acc) {
                               return acc.getUserName() == userName && 
                                      acc.getPassword() == password && 
                                      acc.getRole() == role;
                           });
    
    if (it != this->end()) {
        account = *it;
        return true;
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    }

    return false;
}

<<<<<<< HEAD
int listAccount::forgotPassword(Account &account, const string &tmpCCCD, const string &tmpUser, const string &tmpPass, const string &tmpRePass)
{
    if (this->checkUserName(tmpUser) == -1)
        return -1;

    int index = checkCCCD(tmpCCCD);
    if (index == -1)
        return -2;

    Account currentAccount = this->get(index);

    if (tmpPass != tmpRePass)
        return -3;

    currentAccount.setPassword(tmpPass);
    this->set(index, currentAccount);
    this->writeListAccountToFile(true);

    return 0;
=======
// ! Sửa lại hàm này
void listAccount::forgotPassword(Account &account, const string &tmpUser) {
    auto it = userNameMap.find(tmpUser);
    if (it != userNameMap.end() && tmpPass == tmpRePass) {
        it->second.setPassword(tmpPass);
        account = it->second;
        this->saveListAccountToFile();
    }
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
}

// * Check
int listAccount::checkCCCD(const string &CCCD)
{
    for(int i = 0; i < this->size(); i++) {
        if(this->get(i).getCCCD() == CCCD) {
            return i;
        }
    }
    return -1;
}

int listAccount::checkID(const string &ID)
{
    int left = 0, right = this->size() - 1;

<<<<<<< HEAD
    while (left <= right)
    {
=======
    while (left <= right) {
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
        int mid = left + (right - left) / 2;
        if (this->get(mid).getID() == ID)
            return mid;
        else if (this->get(mid).getID() < ID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

<<<<<<< HEAD
int listAccount::checkUserName(const string &userName)
{
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (this->get(mid).getUserName() == userName)
            return mid;
        else if (this->get(mid).getUserName() < userName)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int listAccount::checkPassword(const string &password)
{
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (this->get(mid).getPassword() == password)
            return mid;
        else if (this->get(mid).getPassword() < password)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int listAccount::checkRole(const int &role)
{
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (this->get(mid).getRole() == role)
            return mid;
        else if (this->get(mid).getRole() < role)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
=======
 int listAccount::checkUserName(const std::string &userName) {
        int left = 0, right = this->size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (this->get(mid).getUserName() == userName)
                return mid;
            else if (this->get(mid).getUserName() < userName)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    int listAccount::checkPassword(const std::string &password) {
        int left = 0, right = this->size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (this->get(mid).getPassword() == password)
                return mid;
            else if (this->get(mid).getPassword() < password)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c

    int listAccount::checkRole(const int &role) {
        int left = 0, right = this->size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (this->get(mid).getRole() == role)
                return mid;
            else if (this->get(mid).getRole() < role)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
};
// * Delete
<<<<<<< HEAD
void listAccount::removeAccountByID(const string &ID)
{
=======
// ! Sửa lại hàm này
void listAccount::removeAccountByID(const string &ID) {
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    Node<Account> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == -1)
        return;

    this->remove(index);

    return;
}

//* Update Account
<<<<<<< HEAD
void listAccount::updateAccountByID(const string &ID, const string &newUserName, const string &newPwd)
{
=======
// ! Sửa lại hàm này
void listAccount::updateAccountByID(const string &ID, const string &newUserName, const string &newPwd) {
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    Node<Account> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == 0)
        return;

    Account currentAccount = this->get(index);
    string file_path = "../Database/AccountDB/account.txt";
    if (std::remove(file_path.c_str()) != 0)
        return;

    currentAccount.setUserName(newUserName);
    currentAccount.setPassword(newPwd);

    this->set(index, currentAccount);
<<<<<<< HEAD
    this->writeListAccountToFile(true);
=======
    this->writeListAccountToFile();
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
    return;
}

// * Search (tuong doi)
vector<Account> listAccount::searchAccount(SearchField_acc field, const string &value)
{
    vector<Account> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);
    int left = 0, right = this->size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        string fieldValue;
        switch (field)
        {
        case SearchField_acc::ID:
            fieldValue = toLowerCase(this->get(mid).getID());
            break;
        case SearchField_acc::UserName:
            fieldValue = toLowerCase(this->get(mid).getUserName());
            break;
        }

        if (fieldValue.find(lowerValue) == 0)
        {
            result.push_back(this->get(mid));
            int temp = mid - 1;
            while (temp >= left)
            {
                string tempFieldValue;
                switch (field)
                {
                case SearchField_acc::ID:
                    tempFieldValue = toLowerCase(this->get(temp).getID());
                    break;
                case SearchField_acc::UserName:
                    tempFieldValue = toLowerCase(this->get(temp).getUserName());
                    break;
                }
                if (tempFieldValue.find(lowerValue) == 0)
                {
                    result.push_back(this->get(temp));
                    temp--;
                }
                else
                {
                    break;
                }
            }
            temp = mid + 1;
            while (temp <= right)
            {
                string tempFieldValue;
                switch (field)
                {
                case SearchField_acc::ID:
                    tempFieldValue = toLowerCase(this->get(temp).getID());
                    break;
                case SearchField_acc::UserName:
                    tempFieldValue = toLowerCase(this->get(temp).getUserName());
                    break;
                }
                if (tempFieldValue.find(lowerValue) == 0)
                {
                    result.push_back(this->get(temp));
                    temp++;
                }
                else
                {
                    break;
                }
            }
            break;
        }

        if (fieldValue < lowerValue)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return result;
<<<<<<< HEAD
=======
}

// ! Sửa lại hàm này
vector<Account> listAccount::searchAccount(SearchField field, const string &value)
{
    vector<Account> result;
    if (this->size() == 0) return result;

    string lowerValue = toLowerCase(value);

    if (field == SearchField::ID)
    {
        for (const auto &entry : idMap)
        {
            string fieldValue = toLowerCase(entry.first);
            if (fieldValue.find(lowerValue) == 0)
            {
                result.push_back(entry.second);
            }
        }
    }
    else if (field == SearchField::UserName)
    {
        for (const auto &entry : userNameMap)
        {
            string fieldValue = toLowerCase(entry.first);
            if (fieldValue.find(lowerValue) == 0)
            {
                result.push_back(entry.second);
            }
        }
    }
    
    return result;
>>>>>>> 91cbe2779d8b4925c2749e7fd4ddbfd0996ea21c
}