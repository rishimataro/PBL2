#include <Management/listAccount.hpp>
#include <unordered_map>

// * Constructor & Destructor
listAccount::listAccount()
{
    this->head = NULL;
}

listAccount::~listAccount()
{
    if (this->head == NULL)
        return;

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
    }

    return count;
}

// * done
// bool listAccount::readListAccountFromFile()
// {
//     string file_path = "./Database/AccountDB/account.txt";
//     ifstream fin;
//     Account account;

//     fin.open(file_path, ios::in);
//     if (!fin.is_open())
//         return false;

//     string line;
//     while (getline(fin, line))
//     {
//         if (line.empty())
//             continue;

//         account.readAccountFromFile(line);
//         this->append(account);
//     }
//     fin.close();
//     return true;
// }

//* done
bool listAccount::writeListAccountToFile(bool check)
{
    string file_path = "./Database/AccountDB/account.txt";
    char ch;

    ifstream fi(file_path, ios::in | ios::binary);
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
    if (!fo.is_open())
        return false;

    Account account;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
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

//* done
vector<Account> listAccount::setAccountByRole(int role)
{
    vector<Account> result;
    if (this->size() == 0)
        return result;

    copy_if(this->begin(), this->end(), back_inserter(result),
            [role](const Account &account)
            { return account.getRole() == role; });

    return result;
}

//* done
vector<Account> listAccount::setAllAccount()
{
    vector<Account> result;
    if (this->size() == 0)
        return result;

    copy(this->begin(), this->end(), back_inserter(result));
    return result;
}

// * Sign Up & Sign In
// Đăng ký tài khoản: thêm account vào listAccount
int listAccount::signUp(Account &account, const string &tmpUserName, const string &tmpPassword, const int &tmpRole)
{
    if(checkUserName(tmpUserName) != -1) return -1;

    Account newAccount;
    newAccount.setID();
    newAccount.setUserName(tmpUserName);
    newAccount.setPassword(tmpPassword);
    newAccount.setRole(tmpRole);

    this->append(newAccount);
    this->writeListAccountToFile(false);

    return newAccount.getRole();

    //! Sau hàm này gọi hàm addPatient() để nhập thông tin bệnh nhân
}

// Đăng nhập: kiểm tra thông tin đăng nhập
int listAccount::signIn(Account &account, const string &tmpUserName, const string &tmpPassword, const int &tmpRole)
{
    if (checkSignIn(tmpUserName, tmpPassword, tmpRole, account)) return account.getRole();
    return false;
}

// bool listAccount::checkSignIn(const string &userName, const string &password, const int &role, Account &account)
// {
//     auto it = find_if(this->begin(), this->end(),
//                       [&userName, &password, &role](const Account &acc)
//                       {
//                           return acc.getUserName() == userName &&
//                                  acc.getPassword() == password &&
//                                  acc.getRole() == role;
//                       });

//     if (it != this->end())
//     {
//         account = *it;
//         return true;
//     }

//     return false;
// }

// void listAccount::forgotPassword(Account &account, const string &tmpCCCD, const string &tmpUser, const string &tmpPass, const string &tmpRePass)
// {
//     int index = checkCCCD(tmpCCCD);
//     if (index == -1)
//         return;

//     Account currentAccount = this->get(index);
//     if (this->checkUserName(tmpUser) == -1 || this->checkCCCD(tmpCCCD) == -1)
//         return;

//     if (tmpPass != tmpRePass)
//         return;

//     currentAccount.setPassword(tmpPass);
//     this->set(index, currentAccount);
//     this->writeListAccountToFile(true);
    
//     return;
// }

// * Check
int listAccount::checkCCCD(const string &CCCD) {
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (this->get(mid).getCCCD() == CCCD)
            return mid;
        else if (this->get(mid).getCCCD() < CCCD)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int listAccount::checkID(const string &ID)
{
    int left = 0, right = this->size() - 1;

    while (left <= right)
    {
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

int listAccount::checkUserName(const std::string &userName)
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

int listAccount::checkPassword(const std::string &password)
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

// * Delete
void listAccount::removeAccountByID(const string &ID)
{
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
// void listAccount::updateAccountByID(const string &ID, const string &newUserName, const string &newPwd)
// {
//     Node<Account> *current = this->head;
//     if (current == NULL)
//         return;

//     int index = this->checkID(ID);
//     if (index == 0)
//         return;

//     Account currentAccount = this->get(index);
//     string file_path = "../Database/AccountDB/account.txt";
//     if (std::remove(file_path.c_str()) != 0)
//         return;

//     currentAccount.setUserName(newUserName);
//     currentAccount.setPassword(newPwd);

//     this->set(index, currentAccount);
//     this->writeListAccountToFile();
//     return;
// }

// * Search (tuong doi)
string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// vector<Account> listAccount::searchAccount(SearchField field, const string &value)
// {
//     vector<Account> result;
//     if (this->size() == 0)
//         return result;

//     string lowerValue = toLowerCase(value);

//     if (field == SearchField::ID)
//     {
//         for (const auto &entry : idMap)
//         {
//             string fieldValue = toLowerCase(entry.first);
//             if (fieldValue.find(lowerValue) == 0)
//             {
//                 result.push_back(entry.second);
//             }
//         }
//     }
//     else if (field == SearchField::UserName)
//     {
//         for (const auto &entry : userNameMap)
//         {
//             string fieldValue = toLowerCase(entry.first);
//             if (fieldValue.find(lowerValue) == 0)
//             {
//                 result.push_back(entry.second);
//             }
//         }
//     }

//     return result;
// }