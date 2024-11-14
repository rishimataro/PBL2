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
bool Patient::setID_patient() { 
    path file_path = "../Database/PatientDB/patient.txt";
    file_path = absolute(file_path);
    
    fstream fi;
    fi.open(file_path, ios::in);

    int maxID = 0;
    if (!fi.is_open()) {
        return false;
    } else {
        if (isFileEmpty(fi)) {
            maxID = 0;
        } else {
            string temp;
            moveToEndOfLastLine(fi);
            getline(fi, temp, ';');
            if (!temp.empty() && temp[0] == 'P') {
                maxID = stoi(temp.substr(1));
            }
        }
    }

    maxID++;
    string id = to_string(maxID);
    id = "P" + id;
    
    this->ID_patient = id;

    fi.close();
    return true;
}

void Patient::setFullName(string fullName) { this->fullName = fullName; }
void Patient::setPhone(string phone) { this->phone = phone; }
void Patient::setDayOfBirth(string dayOfBirth) { this->dayOfBirth.setDate(dayOfBirth); }
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

// Lưu 1 bệnh nhân vào file
bool Patient::writePatientToFile_all(ofstream& fout) {
    fout << this->ID_patient << endl;
    return true;
}

bool Patient::writePatientToFile(fstream& f) {
    string data;

    data.append(this->ID_patient + "\n");
    data.append(this->fullName + "\n");
    data.append(this->phone + "\n");
    data.append(this->dayOfBirth.getDate() + "\n");
    data.append(this->CCCD + "\n");
    data.append(to_string(this->gender) + "\n");
    data.append(this->address + "\n");

    f << data;

    return true;
}

// Lấy 1 bệnh nhân từ file
void Patient::readPatientFromFile(fstream& f) {
    string dayOfBirthStr, genderStr;
    getline(f, this->ID_patient);
    getline(f, this->fullName);
    getline(f, this->phone);
    
    getline(f, dayOfBirthStr);
    this->dayOfBirth.setDate(dayOfBirthStr);
    
    getline(f, this->CCCD);

    getline(f, genderStr);
    this->gender = genderStr == "1" ? true : false;

    getline(f, this->address);
}