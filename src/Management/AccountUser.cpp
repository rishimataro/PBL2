#include <Management/AccountUser.hpp>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

// Constructor & Destructor
AccountUser::AccountUser(const string ID_acc, string userName, string password, string ID_patient)
    : Account(ID_acc, userName, password), ID_patient(ID_patient) {}

AccountUser::AccountUser(const AccountUser &another)
    : Account(another), ID_patient(another.ID_patient) {}

void AccountUser::setID() {
    path file_path = "../Database/AccountDB/accountUser.txt";
    file_path = absolute(file_path);

    fstream fi;
    fi.open(file_path, ios::in);
    
    int maxID = 0;
    if(!fi.is_open()) return;
    else {
        if(isFileEmpty(fi)) {
            maxID = 0;
        }
        else {
            string temp;
            moveToEndOfLastLine(fi);
            getline(fi, temp);
            if (!temp.empty() && temp.substr(0, 4) == "USER") {
                try {
                    maxID = stoi(temp.substr(4));
                } catch (const std::invalid_argument& e) {
                    cerr << "Invalid argument: " << e.what() << endl;
                } catch (const std::out_of_range& e) {
                    cerr << "Out of range: " << e.what() << endl;
                }
            }
        }
    }

    maxID++;
    string id = to_string(maxID);
    id = "USER" + id;
    this->ID_acc = id;

    fi.close();
}

void AccountUser::setID_patient(const string &ID_patient) { this->ID_patient = ID_patient; }

string AccountUser::getID_patient() const { return ID_patient; }

void AccountUser::readFromFile(const string &line) {
    size_t pos = line.find(';');
    if (pos != string::npos) {
        this->ID_acc = line.substr(0, pos);
        size_t next_pos = line.find(';', pos + 1);
        if (next_pos != string::npos) {
            this->userName = line.substr(pos + 1, next_pos - pos - 1);
            pos = next_pos;
            next_pos = line.find(';', pos + 1);
            if (next_pos != string::npos) {
                this->password = line.substr(pos + 1, next_pos - pos - 1);
                this->ID_patient = line.substr(next_pos + 1);
            }
        }
    }
}

void AccountUser::writeToFile(ofstream &f) {
    f << ID_acc << ';' << userName << ';' << password << ';' << ID_patient << endl;
}   

bool AccountUser::operator==(const AccountUser &another) {
    return ID_acc == another.ID_acc && userName == another.userName && password == another.password && ID_patient == another.ID_patient;
}

bool AccountUser::operator!=(const AccountUser &another) {
    return !(*this == another);
}

AccountUser &AccountUser::operator=(const AccountUser &another) {
    if (this == &another) return *this;

    ID_acc = another.ID_acc;
    userName = another.userName;
    password = another.password;
    ID_patient = another.ID_patient;

    return *this;
}
