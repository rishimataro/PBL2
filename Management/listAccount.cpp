#include "./listAccount.h"

// * Constructor & Destructor  
listAccount::listAccount() {
    this->head = NULL;
    
}

listAccount::~listAccount() {
    if(this->head == NULL) {
        return;
    }

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
void listAccount::setListAccountByFile() {
    fstream fin;
    fin.open("./Database/AccountDB/account.txt", ios::in);

    if(!fin.is_open()) return;

    string line;
    while(getline(fin, line)) {
        if(line.empty()) continue;

        Account account;
        account.setAccount(line);
        this->append(account);
    }
    fin.close();
}

void listAccount::saveListAccountToFile() {
    fstream fout("../Database/AccountDB/account.txt", ios::out);

    if(!fout.is_open()) return;
    
    // this->get(0).saveAccount(fout);
    for(int i = 0; i < this->size(); i++) {
        if(i != 0) fout << endl;
        this->get(i).saveAccount(fout);
    }
    fout.close();
}

// * Display
void listAccount::printAccountByID() {
    
}

void listAccount::printAllAccount() {
    int x = 40, y = 5, w = 20, h = 2; // tổng w = 80

    box_(x, y - 3, 80, h, " ******************** DANH SÁCH TẤT CẢ TÀI KHOẢN HIỆN CÓ ******************** ", "000000", "FF1E00", "FF1E00" );
    box(x, y, w - 5, h, "ID", "000000", "E8F9FD", "59CE8F");
    box(x + 15, y, w + 5, h, "TÀI KHOẢN", "000000", "E8F9FD", "59CE8F");
    box(x + 40, y, w, h,  "MẬT KHẨU", "000000", "E8F9FD", "59CE8F");
    box(x + 60, y, w, h, "VAI TRÒ", "000000", "E8F9FD", "59CE8F");

    gotoXY(x + 15, y); cout << "┬"; 
    for(int i = 2; i < 4; i++) {    
        gotoXY(x + (i * 20), y); cout << "┬";
    }

    for(int i = 0; i < this->size(); i++) {
        y += 2;
        emptyBox(x, y, w - 5, h, 15, 1);          
        emptyBox(x + 15, y, w + 5, h, 15, 1);     
        emptyBox(x + 40, y, w, h, 15, 1);     
        emptyBox(x + 60, y, w, h, 15, 1);     

        gotoXY(x, y); cout << "├";
        gotoXY(x + 80, y); cout << "┤";
        gotoXY(x + 15, y); cout << "┼"; 
        for (int j = 2; j < 4; j++) {
            gotoXY(x + (j * 20), y); cout << "┼"; 
        }
    }

    gotoXY(x + 15, y); cout << "┴"; 
    for(int i = 2; i < 4; i++) {
        gotoXY(x + (i * 20), y); cout << "┴";
    }

    int y2 = 8;
    for(int i = 0; i < this->size(); i++) {
        gotoXY(x + 1, y2);
        this->get(i).printAccount();
        y2 += 2;
        for (int j = 0; j < 4; j++) {
            gotoXY(x + (j * 20), y2 - 2);
        }
    }
    gotoXY(x, y2);
}

// * Sign Up & Sign In
void listAccount::signUp(Account &account) {

}
void listAccount::signIn(Account &account) {
    
}
bool listAccount::checkSignIn(const string& id, const string& password, Account &account) {
    return 0;
}

// * Check
bool listAccount::checkID(const string& ID) {
    return 0;
}
bool listAccount::checkUserName(const string& userName) {
    return 0;
}
bool listAccount::checkPassword(const string& password) {
    return 0;
}
bool listAccount::checkRole(const int& role) {
    return 0;
}

// * Delete
void listAccount::removeAccountByID(const string& ID) {

}

// * Update
void listAccount::updateAccountByID(const string& ID) {

}

// * Search
void listAccount::searchAccountByID(const string& id) {

}
void listAccount::searchAccountByUserName(const string& userName) {

}