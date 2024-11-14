#include <Management/Account.hpp>

int safe_stoi(const string &str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Lỗi: Chuỗi không hợp lệ để chuyển đổi thành số nguyên: " << e.what() << endl;
        return 0;
    }
}

//* Constructor & Destructor
Account::Account(const string ID_acc, string userName, string password, int role, string ID_patient)
{
    this->ID_acc = ID_acc;
    this->userName = userName;
    this->password = password;
    this->role = role;
    this->ID_patient = ID_patient;
}

Account::Account(const Account &another)
{
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
    this->role = another.role;
    this->ID_patient = another.ID_patient;
}

Account::~Account() {}

//* Setter
void Account::setID() {
    path file_path = "../Database/AccountDB/account.txt";
    file_path = absolute(file_path);

    ifstream fi(file_path);

    int maxID = 0;

    if (!fi.is_open()) {
        return;
    }

    string line;
    while (getline(fi, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string id_str = line.substr(0, pos);
            if (id_str.size() > 3 && id_str.substr(0, 3) == "ACC") {
                int currentID = stoi(id_str.substr(3));
                maxID = max(maxID, currentID);
            }
        }
    }

    maxID++;
    this->ID_acc = "ACC" + to_string(maxID);

    fi.close();
}

void Account::setPassword(const string &password) { this->password = password; }
void Account::setUserName(const string &userName) { this->userName = userName; }
void Account::setRole(const int &role) { this->role = role; }
void Account::setID_patient(const string &ID_patient) { this->ID_patient = ID_patient; }

//* Getter
string Account::getID() const { return this->ID_acc; }
string Account::getPassword() const { return this->password; }
string Account::getUserName() const { return this->userName; }
int Account::getRole() const { return this->role; }
string Account::getRoleToString() const { 
    string roleStr;
    if(this->role == 0) roleStr = "Quản trị viên";
    else if(this->role == 1) roleStr = "Bệnh nhân";
    return roleStr; 
}

string Account::getID_patient() const { return this->ID_patient; }

string Account::getCCCD() const {
    if(this->role != 1) {
        return "";
    }

    string file_path = "../Database/PatientDB/" + this->ID_patient + ".txt";

    ifstream fi;
    fi.open(file_path);
    string CCCD;

    if (!fi.is_open()) {
        cerr << "Không thể mở file " << file_path << endl;
        return "";
    }

    string line;
    int lineCount = 0;
    while (getline(fi, line)) {
        lineCount++;
        if (lineCount == 5) {
            CCCD = line;
            break;
        }
    }

    fi.close();

    if (lineCount < 5) {
        return "";
    }

    return CCCD;
}

//* Function
// Lấy 1 account từ file
void Account::readAccountFromFile(const string& line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ';'); this->ID_acc = token;
    getline(ss, token, ';'); this->userName = token;
    getline(ss, token, ';'); this->password = token;
    getline(ss, token, ';'); this->role = safe_stoi(token);
    if(this->role == 1) {
        getline(ss, token, ';'); this->ID_patient = token;
    }
    else {
        this->ID_patient = "";
    }
}

// Lưu 1 account vào file
void Account::writeAccountToFile(ofstream &f) {
    ostringstream oss;
    oss << this->ID_acc << ";" << this->userName << ";" << this->password << ";" << this->role;
    if (this->role == 1) {
        oss << ";" << this->ID_patient;
    }
    f << oss.str() << endl;
}

bool Account::operator==(const Account& another) {
    return this->ID_acc == another.getID() && this->userName == another.getUserName()
            && this->password == another.getPassword() && this->role == another.getRole() && this->ID_patient == another.getID_patient();
}

bool Account::operator!=(const Account& another) {
    return !(*this == another);
}

Account& Account::operator=(const Account& another) {
    if (this == &another) {
        return *this; 
    }
    this->ID_acc = another.getID();
    this->userName = another.getUserName();
    this->password = another.getPassword();
    this->role = another.getRole();
    this->ID_patient = another.getID_patient();
    return *this;
}