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
Account::Account(const string ID_acc, string userName, string password, int role, const Patient& patient)
{
    this->ID_acc = ID_acc;
    this->userName = userName;
    this->password = password;
    this->role = role;
    this->patient = patient;
}

Account::Account(const Account &another)
{
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
    this->role = another.role;
    this->patient = another.patient;
}

Account::~Account() {}

//* Setter
void Account::setID() {
    path file_path = "../Database/PatientDB/account.txt";
    file_path = absolute(file_path);

    ifstream fi(file_path);

    int maxID = 0;
    if (!fi.is_open()) {
        return;
    } else {
        if (fi.peek() == ifstream::traits_type::eof()) {
            maxID = 0;
        } else {
            string temp;
            fi.seekg(-1, ios::end);

            // Move to the start of the last line
            while (fi.tellg() > 0 && fi.peek() != '\n') {
                fi.seekg(-1, ios::cur);
            }
            if (fi.tellg() != 0) {
                fi.seekg(1, ios::cur);
            }

            getline(fi, temp, ';');
            if (!temp.empty() && temp.substr(0, 3) == "ACC") {
                maxID = stoi(temp.substr(3));
            }
        }
    }

    maxID++;
    string id = "ACC" + to_string(maxID);

    this->ID_patient = id;

    fi.close();
}

void Account::setPassword(const string &password) { this->password = password; }
void Account::setUserName(const string &userName) { this->userName = userName; }
void Account::setRole(const int &role) { this->role = role; }

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
string Account::getCCCD() const {
    return this->patient.getCCCD();
}

//* Function
// Lấy 1 account từ file
void Account::readPatientFromFile(const string& line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ';'); this->ID_acc = token;
    getline(ss, token, ';'); this->userName = token;
    getline(ss, token, ';'); this->password = token;
    getline(ss, token, ';'); this->role = safe_stoi(token);
}

// Lưu 1 account vào file
void Account::writeAccountToFile(ofstream &f) {
    string data;

    data.append(this->ID_acc + ";");
    data.append(this->userName + ";");
    data.append(this->password + ";");
    data.append(to_string(this->role) + "\n");

    f << data;
}

bool Account::operator==(const Account& another) {
    return this->ID_acc == another.getID() && this->userName == another.getUserName()
            && this->password == another.getPassword() && this->role == another.getRole();
}

Account& Account::operator=(const Account& another) {
    if (this == &another) {
        return *this; 
    }

    this->ID_acc = another.getID();
    this->userName = another.getUserName();
    this->password = another.getPassword();
    this->role = another.getRole();
    return *this;
}