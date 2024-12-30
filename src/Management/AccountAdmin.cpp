#include <Management/AccountAdmin.hpp>

AccountAdmin::AccountAdmin(const string ID_acc, string userName, string password)
    : Account(ID_acc, userName, password) {}

AccountAdmin::AccountAdmin(const AccountAdmin &another)
    : Account(another) {}

void AccountAdmin::setID() {
    fs::path file_path = "../Database/AccountDB/accountAdmin.txt";
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
            if (id_str.size() > 3 && id_str.substr(0, 5) == "ADMIN") {
                try {
                    int currentID = stoi(id_str.substr(5));
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
    this->ID_acc = "ADMIN" + to_string(maxID);

    fi.close();
}

void AccountAdmin::readFromFile(const string &line) {
    size_t pos = line.find(';');
    if (pos != string::npos) {
        this->ID_acc = line.substr(0, pos);
        size_t next_pos = line.find(';', pos + 1);
        if (next_pos != string::npos) {
            this->userName = line.substr(pos + 1, next_pos - pos - 1);
            this->password = line.substr(next_pos + 1);
        }
    }
}

void AccountAdmin::writeToFile(ofstream &f) {
    f << ID_acc << ';' << userName << ';' << password << std::endl;
}

bool AccountAdmin::operator==(const AccountAdmin &another) {
    return this->ID_acc == another.ID_acc;
}

bool AccountAdmin::operator!=(const AccountAdmin &another) {
    return !(*this == another);
}

AccountAdmin &AccountAdmin::operator=(const AccountAdmin &another) {
    if (this == &another) return *this;
    
    this->ID_acc = another.ID_acc;
    this->userName = another.userName;
    this->password = another.password;
    return *this;
}