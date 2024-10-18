#include "./Patient.h"

//* Constructor & Destructor
Patient::Patient(string ID_patien, string fullName, string phon, Date dayOfBirth, bool sex, string address) {
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
    
    box_(x, y - 3, w, h,"          THÔNG TIN BỆNH NHÂN", "000000", "FF1E00", "FF1E00" );
    box(x, y + 2, w, h, "  ID       : ", "000000", "FFFFFF", "FFFFFF"); 

    box(x, y + 4, w, h, "  HỌ TÊN   : ",  "000000", "FFFFFF", "FFFFFF"); 
    box(x, y + 6, w, h, "  SĐT      : ", "000000", "FFFFFF", "FFFFFF");  
    box(x, y + 8, w, h, "  NGÀY SINH: ", "000000", "FFFFFF", "FFFFFF");   
    box(x, y + 10, w, h, "  GIỚI TÍNH: ", "000000", "FFFFFF", "FFFFFF");
    box(x, y + 12, w, h, "  ĐỊA CHỈ  : ", "000000", "FFFFFF", "FFFFFF");

    // box_(x, y - 3, w, h, 12, 14, 12, "          THÔNG TIN BỆNH NHÂN");
    // box(x, y + 2, w, h, 15, 1, 15,  "  ID       : "); 
    // box(x, y + 4, w, h, 15, 1, 15,  "  HỌ TÊN   : "); 
    // box(x, y + 6, w, h, 15, 1, 15,  "  SĐT      : "); 
    // box(x, y + 8, w, h, 15, 1, 15,  "  NGÀY SINH: "); 
    // box(x, y + 10, w, h, 15, 1, 15, "  GIỚI TÍNH: ");
    // box(x, y + 12, w, h, 15, 1, 15, "  ĐỊA CHỈ  : ");

    for(int i = 2; i <= 6; i ++ ){
        gotoXY(x, y + (i*2)); cout << "├";
        gotoXY(x + w, y + (i*2)); cout << "┤";
    }

    string sex_str;

    gotoXY(x + 14, y + 3); cin >> this->ID_patient;
    gotoXY(x + 14, y + 5); cin.ignore(); getline(cin, this->fullName);
    gotoXY(x + 14, y + 7); cin >> this->phone;
    gotoXY(x + 14, y + 9); dayOfBirth.inputDate();
    gotoXY(x + 14, y + 11); cin >> sex_str;
    if(sex_str == "Nam") this->sex = true;
    else this->sex = false;
    gotoXY(x + 14, y + 13); cin.ignore(); getline(cin, this->address);
}

// In thông tin 1 bệnh nhân
void Patient::printPatient() {
    int x = 60, y = 5, w = 40, h = 2;
    string sex_str = this->sex ? "Nam" : "Nữ";
    box_(x, y - 3, w, h,"          THÔNG TIN BỆNH NHÂN", "000000", "FFFFFF", "FFFFFF");
    box(x, y + 2, w, h, "  ID       : " + this->ID_patient, "000000", "FFFFFF", "FFFFFF"); 
    box(x, y + 4, w, h, "  HỌ TÊN   : " + this->fullName, "000000", "FFFFFF", "FFFFFF"); 
    box(x, y + 6, w, h, "  SĐT      : " + this->phone, "000000", "FFFFFF", "FFFFFF"); 
    box(x, y + 8, w, h, "  NGÀY SINH: " + this->dayOfBirth.getDate(), "000000", "FFFFFF", "FFFFFF");
    box(x, y + 10, w, h, "  GIỚI TÍNH: " + sex_str, "000000", "FFFFFF", "FFFFFF");
    box(x, y + 12, w, h, "  ĐỊA CHỈ  : " + this->address, "000000", "FFFFFF", "FFFFFF");

    // box_(x, y - 3, w, h, 12, 14, 12, "          THÔNG TIN BỆNH NHÂN");
    // box(x, y + 2, w, h, 15, 1, 15,  "  ID       : " + this->ID_patient); 
    // box(x, y + 4, w, h, 15, 1, 15,  "  HỌ TÊN   : " + this->fullName); 
    // box(x, y + 6, w, h, 15, 1, 15,  "  SĐT      : " + this->phone); 
    // box(x, y + 8, w, h, 15, 1, 15,  "  NGÀY SINH: " + this->dayOfBirth.getDate());
    // box(x, y + 10, w, h, 15, 1, 15, "  GIỚI TÍNH: " + sex_str);
    // box(x, y + 12, w, h, 15, 1, 15, "  ĐỊA CHỈ  : " + this->address);

    for(int i = 2; i <= 6; i ++ ){
        gotoXY(x, y + (i*2)); cout << "├";
        gotoXY(x + w, y + (i*2)); cout << "┤";
    }
}

// Lưu 1 bệnh nhân vào file
void Patient::savePatient(fstream& f) {
    f << this->ID_patient << endl;
    f << this->fullName << endl;
    f << this->phone << endl;
    f << this->dayOfBirth.getDate() << endl;
    f << this->sex << endl;
    f << this->address << endl;
}

// Lấy 1 bệnh nhân từ file
void Patient::setPatient(fstream& f) {
    string DOB_str;
    getline(f, this->ID_patient, '\n');
    getline(f, this->fullName, '\n');
    getline(f, this->phone, '\n');

    getline(f, DOB_str, '\n');
    this->dayOfBirth.setDate(DOB_str);

    f >> this->sex;
    f.ignore();

    getline(f, this->address, '\n');
}