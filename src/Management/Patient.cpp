#include <Management/Patient.hpp>
Patient::Patient(string ID_patient, string fullName, string phone, string dayOfBirthStr, string CCCD, bool gender, string address) {
    this->ID_patient = ID_patient;
    this->fullName = fullName;
    this->phone = phone;
    this->dayOfBirth.setDate(dayOfBirthStr);
    this->CCCD = CCCD;
    this->gender = gender;
    this->address = address;
}

Patient::Patient(const Patient &patient) {
    this->ID_patient = patient.ID_patient;
    this->fullName = patient.fullName;
    this->phone = patient.phone;
    this->dayOfBirth = patient.dayOfBirth;
    this->CCCD = patient.CCCD;
    this->gender = patient.gender;
    this->address = patient.address;
}

Patient::~Patient() { }

//* Setter
void Patient::setID_patient(string ID_patient) { this->ID_patient = ID_patient; }
void Patient::setFullName(string fullName) { this->fullName = fullName; }
void Patient::setPhone(string phone) { this->phone = phone; }
void Patient::setDayOfBirth(Date dayOfBirth) { this->dayOfBirth = dayOfBirth; }
void Patient::setCCCD(string CCCD) { this->CCCD = CCCD; }
void Patient::setGender(bool gender) { this->gender = gender; }
void Patient::setAddress(string address) { this->address = address; }

//* Getter
string Patient::getID_patient() const { return this->ID_patient; }
string Patient::getFullName() const { return this->fullName; }
string Patient::getPhone() const { return this->phone; }
Date Patient::getDayOfBirth() const { return this->dayOfBirth; }
string Patient::getCCCD() const { return this->CCCD; }
bool Patient::getGender() const { return this->gender; }
string Patient::getGenderToString() const { return (this->gender) ? "Nữ" : "Nam"; }
string Patient::getAddress() const { return this->address; }

//* Function
// Nhập 1 bệnh nhân
void Patient::inputPatient() {
    int x = whereX(), y = whereY();
    string gender_str;

    gotoXY(x + 12, y + 1); cout << this->ID_patient;
    gotoXY(x + 12, y + 4); cin.ignore(); getline(cin, this->fullName);
    gotoXY(x + 12, y + 7); cin >> this->phone;
    gotoXY(x + 12, y + 10); dayOfBirth.inputDate();
    gotoXY(x + 12, y + 13); cin >> this->CCCD;

    gotoXY(x + 12, y + 16); cin >> gender_str;
    if(gender_str == "Nam") this->gender = true;
    else this->gender = false;

    gotoXY(x + 12, y + 19); cin.ignore(); getline(cin, this->address);
}

// In thông tin 1 bệnh nhân
void Patient::printPatientHorizontal() {
    int x = whereX(), y = whereY();
    string gender_str = this->gender ? "Nam" : "Nữ";

    gotoXY(x + 4, y);
    cout << this->ID_patient;
    gotoXY(x + 16, y);
    cout << this->fullName;
    gotoXY(x + 41, y);
    cout << this->phone;
    gotoXY(x + 61, y);
    cout << this->dayOfBirth.getDate();
    gotoXY(x + 81, y);
    cout << this->CCCD;
    gotoXY(x + 101, y);
    cout << gender_str;
    gotoXY(x + 121, y);
    cout << this->address << endl;
}

// Lưu 1 bệnh nhân vào file
void Patient::saveAllPatient(fstream& f) {
    f << this->ID_patient << ";" << this->fullName << ";" << this->phone << ";" <<
            this->dayOfBirth.getDate() << ";" << this->CCCD << ";" << this->gender << ";" << this->address << endl;
}

void Patient::savePatient(fstream& f) {
    f << this->ID_patient << endl;
    f << this->fullName << endl;
    f << this->phone << endl;
    f << this->dayOfBirth.getDate() << endl;
    f << this->CCCD << endl;
    f << this->getGenderToString() << endl;
    f << this->address << endl;
}

// Lấy 1 bệnh nhân từ file
void Patient::setPatient(const string& line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ';'); this->ID_patient = token;
    getline(ss, token, ';'); this->fullName = token;
    getline(ss, token, ';'); this->phone = token;
    getline(ss, token, ';'); this->dayOfBirth.setDate(token);
    getline(ss, token, ';'); this->CCCD = token;
    getline(ss, token, ';'); this->gender = (token == "Nữ") ? true : false;
    getline(ss, token, ';'); this->address = token;
}