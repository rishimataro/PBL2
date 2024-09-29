#include "./Patient.h"

//* Constructor & Destructor
Patient::Patient(string ID_patient = "", string fullName = "", string phone = "", Date dayOfBirth = Date(), bool sex = false, string address = "") {
    this->ID_patient = ID_patient;
    this->fullName = fullName;
    this->phone = phone;
    this->dayOfBirth = dayOfBirth;
    this->sex = sex;
    this->address = address;
}

Patient::Patient(const Patient &patient) {
    this->ID_patient = patient.ID_patient;
    this->fullName = patient.fullName;
    this->phone = patient.phone;
    this->dayOfBirth = patient.dayOfBirth;
    this->sex = patient.sex;
    this->address = patient.address;
}

Patient::~Patient() { }

//* Setter
void Patient::setID_patient(string ID_patient) { this->ID_patient = ID_patient; }
void Patient::setFullName(string fullName) { this->fullName = fullName; }
void Patient::setPhone(string phone) { this->phone = phone; }
void Patient::setDayOfBirth(Date dayOfBirth) { this->dayOfBirth = dayOfBirth; }
void Patient::setAddress(string address) { this->address = address; }

//* Getter
string Patient::getID_patient() const { return this->ID_patient; }
string Patient::getFullName() const { return this->fullName; }
string Patient::getPhone() const { return this->phone; }
Date Patient::getDayOfBirth() const { return this->dayOfBirth; }
bool Patient::getSex() const { return this->sex; }
string Patient::getAddress() const { return this->address; }

//* Function
// Nhập 1 bệnh nhân
void Patient::inputPatient() {
    int x = 60, y = 5, w = 40, h = 2;
    box_(x, y - 3, w, h, 12, 14, 12, "       USER INFORMATION");
    box(x, y + 2, w, h, 15, 1, 15,  "  ID       : "); 
    box(x, y + 4, w, h, 15, 1, 15,  "  Ho ten   : "); 
    box(x, y + 6, w, h, 15, 1, 15,  "  SDT      : "); 
    box(x, y + 8, w, h, 15, 1, 15,  "  Ngay sinh: "); 
    box(x, y + 10, w, h, 15, 1, 15, "  Gioi tinh: ");
    box(x, y + 12, w, h, 15, 1, 15, "  Dia chi  : ");

    for(int i = 2; i <= 6; i ++ ){
        gotoXY(x, y + (2*i)); cout << char(195);
        gotoXY(x + w, y + (2*i)); cout << char(180);
    }

    gotoXY(x + 13, y + 3); cin >> this->ID_patient;
    gotoXY(x + 13, y + 5); cin >> this->fullName;
    gotoXY(x + 13, y + 7); cin >> this->phone;
    gotoXY(x + 13, y + 9); dayOfBirth.inputDate();
    gotoXY(x + 13, y + 11); cin >> this->sex;
    gotoXY(x + 13, y + 13); cin >> this->address;
}

// In thông tin 1 bệnh nhân
void Patient::printPatient() {
    int x = 60, y = 5, w = 40, h = 2;
    box_(x, y - 3, w, h, 12, 14, 12, "       USER INFORMATION");
    box(x, y + 2, w, h, 15, 1, 15,  "  ID       : " + this->ID_patient); 
    box(x, y + 4, w, h, 15, 1, 15,  "  Ho ten   : " + this->fullName); 
    box(x, y + 6, w, h, 15, 1, 15,  "  SDT      : " + this->phone); 
    box(x, y + 8, w, h, 15, 1, 15,  "  Ngay sinh: " + this->dayOfBirth.printDate()); 
    box(x, y + 10, w, h, 15, 1, 15, "  Gioi tinh: " + (this->sex ? "Nam" : "Nu"));
    box(x, y + 12, w, h, 15, 1, 15, "  Dia chi  : " + this->address);

    for(int i = 2; i <= 4; i ++ ){
        gotoXY(x, y + (2*i)); cout << char(195);
        gotoXY(x + w, y + (2*i)); cout << char(180);
    }
}
// Lưu 1 bệnh nhân vào file
void Patient::savePatient(fstream& f) {
    f << this->ID_patient << endl;
    f << this->fullName << endl;
    f << this->phone << endl;
    f << this->dayOfBirth.printDate() << endl;
    f << this->sex << endl;
    f << this->address << endl;
}
// Lấy 1 bệnh nhân từ file
void Patient::setPatient(fstream& f) {
    getline(f, this->ID_patient);
    getline(f, this->fullName);
    getline(f, this->phone);
    getline(f, this->dayOfBirth());
    f >> this->sex;
    f.ignore();
    getline(f, this->address);
}