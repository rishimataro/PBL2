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
            getline(fi, temp);
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

// Lưu 1 bệnh nhân vào file
bool Patient::writePatientToFile(ofstream& fout) {
    fout << this->ID_patient << ";" << this->fullName << ";" << this->phone 
         << ";" << this->dayOfBirth.getDate() << ";" << this->CCCD << ";" << this->gender << ";" << this->address << endl;
   return true;
}

// Lấy 1 bệnh nhân từ file
void Patient::readPatientFromFile(const string &line) {
    istringstream stream(line);
    string tmp;
    getline(stream, tmp, ';');
    this->ID_patient = tmp;

    getline(stream, tmp, ';');
    this->fullName = tmp;

    getline(stream, tmp, ';');
    this->phone = tmp;

    getline(stream, tmp, ';');
    this->dayOfBirth.setDate(tmp);

    getline(stream, tmp, ';');
    this->CCCD = tmp;

    getline(stream, tmp, ';');
    this->gender = (tmp == "1") ? true : false;

    getline(stream, tmp);
    this->address = tmp;
}