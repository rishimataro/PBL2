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
    fs::path file_path = "../Database/AccountDB/accountUser.txt";
    file_path = fs::absolute(file_path);

    if (!fs::exists(file_path)) {
        cerr << "File không tồn tại: " << file_path << endl;
        return;
    }

    ifstream fi(file_path);
    if (!fi.is_open()) {
        cerr << "Không thể mở file: " << file_path << endl;
        return;
    }

    int maxID = 0;
    string line;
    while (getline(fi, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string id_str = line.substr(0, pos);
            if (id_str.size() > 3 && id_str.substr(0, 3) == "USER") {
                try {
                    int currentID = stoi(id_str.substr(3));
                    maxID = max(maxID, currentID);
                } catch (const invalid_argument& e) {
                    cerr << "Lỗi khi chuyển đổi ID: " << id_str << endl;
                } catch (const out_of_range& e) {
                    cerr << "Lỗi: ID vượt quá phạm vi: " << id_str << endl;
                }
            }
        }
    }

    maxID++;
    this->ID_acc = "USER" + to_string(maxID);

    fi.close();
}

void AccountUser::setID_patient(const string &ID_patient) { this->ID_patient = ID_patient; }

string AccountUser::getID_patient() const { return ID_patient; }

string AccountUser::getCCCD() const {
    fs::path file_path = "../Database/PatientDB/patient.txt";
    file_path = fs::absolute(file_path);

    if (!fs::exists(file_path)) {
        cerr << "File không tồn tại: " << file_path << endl;
        return "";
    }

    ifstream fi(file_path);
    if (!fi.is_open()) {
        cerr << "Không thể mở file: " << file_path << endl;
        return "";
    }

    unordered_map<string, string> patientCCCDs;

    // Duyệt qua file để lưu thông tin CCCD của bệnh nhân vào hashmap
    string line;
    while (getline(fi, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string id_str = line.substr(0, pos);
            if (id_str == ID_patient) {
                pos = line.find(';', pos + 1);
                if (pos != string::npos) {
                    size_t next_pos = line.find(';', pos + 1);
                    if (next_pos != string::npos) {
                        patientCCCDs[id_str] = line.substr(pos + 1, next_pos - pos - 1);
                    }
                }
            }
        }
    }

    fi.close();

    // Kiểm tra và trả về CCCD nếu tìm thấy
    if (patientCCCDs.find(ID_patient) != patientCCCDs.end()) {
        return patientCCCDs[ID_patient];
    } else {
        cerr << "Không tìm thấy CCCD cho bệnh nhân ID: " << ID_patient << endl;
        return "";
    }
}

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
