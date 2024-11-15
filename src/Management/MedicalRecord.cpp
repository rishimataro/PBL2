#include <Management/MedicalRecord.hpp>

MedicalRecord::MedicalRecord(string ID_record, string ID_patient, Patient* patient, string symptoms, string diagnosis, string dateOfRecord) {
    this->ID_record = ID_record;
    this->ID_patient = ID_patient;
    this->symptoms = symptoms;
    this->diagnosis = diagnosis;
    this->dateOfRecord.setDate(dateOfRecord);
    this->patient = patient;
}

MedicalRecord::MedicalRecord(const MedicalRecord &record) {
    this->ID_record = record.ID_record;
    this->ID_patient = record.ID_patient;
    this->symptoms = record.symptoms;
    this->diagnosis = record.diagnosis;
    this->dateOfRecord = record.dateOfRecord;
    this->patient = record.patient;
}

MedicalRecord::~MedicalRecord() {}

bool MedicalRecord::setID_record() {
    path file_path = "../Database/Medical_recordDB/medical_record.txt";
    file_path = absolute(file_path);
    
    fstream fi;
    fi.open(file_path, ios::in);

    if (!fi.is_open()) {
        return false;
    }

    int maxID = 1;
    
    if (isFileEmpty(fi)) {
        maxID = 0;
    } else {
        string temp;
        moveToEndOfLastLine(fi);
        getline(fi, temp);

        if (!temp.empty() && temp.substr(0, 2) == "MR") {
            maxID = stoi(temp.substr(2));
        }
    }

    maxID++;
    string id = "MR" + to_string(maxID);

    this->ID_record = id;

    fi.close();
    return true;
}


void MedicalRecord::setID_patient(const string &id) { this->ID_patient = id; }
void MedicalRecord::setSymptoms(const string &sym) { this->symptoms = sym; }
void MedicalRecord::setDiagnosis(const string &diag) { this->diagnosis = diag; }
void MedicalRecord::setDateOfRecord(const string &date) { this->dateOfRecord.setDate(date); }
void MedicalRecord::setPatient(Patient* patient) { this->patient = patient; }

string MedicalRecord::getID_record() const { return this->ID_record; }
string MedicalRecord::getID_patient() const { return this->ID_patient; }
string MedicalRecord::getSymptoms() const { return this->symptoms; }
string MedicalRecord::getDiagnosis() const { return this->diagnosis; }
Date MedicalRecord::getDateOfRecord() const { return this->dateOfRecord; }
Patient* MedicalRecord::getPatient() const { return this->patient; }

MedicalRecord& MedicalRecord::operator=(const MedicalRecord &record) {
    if (this == &record) {
        return *this;
    }

    this->ID_record = record.ID_record;
    this->ID_patient = record.ID_patient;
    this->symptoms = record.symptoms;
    this->diagnosis = record.diagnosis;
    this->dateOfRecord = record.dateOfRecord;
    this->patient = record.patient;

    return *this;
}

bool MedicalRecord::writeMedicalRecordToFile(fstream &f) {
    string data;

    data.append(this->ID_record + "\n");
    data.append(this->ID_patient + "\n");
    data.append(this->symptoms + "\n");
    data.append(this->diagnosis + "\n");
    data.append(this->dateOfRecord.getDate() + "\n");

    f << data;

    return true;
}

bool MedicalRecord::writeMedicalRecordToFile_all(ofstream &fout) {
    fout << this->ID_record << endl;
    return true;
}

void MedicalRecord::readMedicalRecordFromFile(fstream &f) {
    string dateOfRecordStr;
    getline(f, this->ID_record);
    getline(f, this->ID_patient);
    getline(f, this->symptoms);
    getline(f, this->diagnosis);
    
    getline(f, dateOfRecordStr);
    this->dateOfRecord.setDate(dateOfRecordStr);
}
