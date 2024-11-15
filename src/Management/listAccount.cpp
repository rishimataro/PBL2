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
bool listAccount::readListAccountFromFile()
{
    string file_path = "../Database/AccountDB/account.txt";
    ifstream fin;
    Account account;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        account.readAccountFromFile(line);
        this->append(account);
    }
    fin.close();
    return true;
}

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

    for(int i = 0; i < this->size(); i++) {
        if(this->get(i).getRole() == role) {
            result.push_back(this->get(i));
        }
    }
    return result;
}

//* done
vector<Account> listAccount::setAllAccount()
{
    vector<Account> result;
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++) {
        result.push_back(this->get(i));
    }

    return result;
}

// * Sign Up & Sign In
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
    }
    return false;
}

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
    this->writeListAccountToFile(true);

    return;
}

//* Update Account
void listAccount::updateAccountByID(const string &ID, const string &newUserName, const string &newPwd)
{
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
    this->writeListAccountToFile(true);
    return;
}

// * Search (tuong doi)
vector<Account> listAccount::searchAccount(SearchField_acc field, const string &value)
{
    vector<Account> result;

    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++)
    {
        string fieldValue;
        
        switch (field)
        {
        case SearchField_acc::ID:
            fieldValue = toLowerCase(this->get(i).getID());
            break;
        case SearchField_acc::UserName:
            fieldValue = toLowerCase(this->get(i).getUserName());
            break;
        }

        if (fieldValue.find(lowerValue) == 0)
        {
            result.push_back(this->get(i));
        }
    }

    return result;
}
