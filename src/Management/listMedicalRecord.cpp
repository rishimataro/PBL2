#include <Management/listMedicalRecord.hpp>

listMedicalRecord::listMedicalRecord() {
    this->head = NULL;
    loadSymptomSolutionsFromFile();
}

listMedicalRecord::~listMedicalRecord() {
    if (this->head == NULL) return;
    
    Node<MedicalRecord>* current = this->head;
    Node<MedicalRecord>* tail = this->head->prev;

    do {
        Node<MedicalRecord>* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

bool listMedicalRecord::readListMedicalRecordFromFile() {
    string file_path = "../Database/Medical_recordDB/medical_record.txt";
    fstream fin, recordFile;
    MedicalRecord record;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;

    string id;
    while (getline(fin, id)) {
        if (id.empty())
            continue;

        file_path = "../Database/Medical_recordDB/" + id + ".txt";
        recordFile.open(file_path, ios::in);

        if (!recordFile.is_open())
            continue;

        record.readMedicalRecordFromFile(recordFile);
        this->append(record);

        recordFile.close();
    }
    fin.close();
    return true;
}

bool listMedicalRecord::writeListMedicalRecordToFile(bool check) {
    string file_path = "../Database/Medical_recordDB/medical_record.txt";
    char ch;

    ifstream fi(file_path);
    if (fi.is_open()) {
        fi.seekg(-1, ios::end);
        fi.get(ch);
        if (ch != '\n' && ch != '\0') {
            ofstream temp(file_path, ios::app);
            temp << "\n";
            temp.close();
        }
        fi.close();
    }

    ofstream fo;
    if (check) {
        fo.open(file_path, ios::trunc); 
    } else {
        fo.open(file_path, ios::app);  
    }

    if (!fo.is_open())
        return false;

    MedicalRecord record;
    if (check) {
        for (int i = 0; i < this->size(); i++) {
            record = this->get(i);
            record.writeMedicalRecordToFile_all(fo);
        }
    } else {
        record = this->get(this->size() - 1);
        record.writeMedicalRecordToFile_all(fo);
    }

    fo.close();
    return true;
}

bool listMedicalRecord::writeMedicalRecordToFile(int index) {
    string fileName = "../Database/Medical_recordDB/" + this->get(index).getID_record() + ".txt";

    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open()) {
        return false;
    }

    this->get(index).writeMedicalRecordToFile(fout);
    fout.close();
    return true;
}

vector<MedicalRecord> listMedicalRecord::setAllMedicalRecords() {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        records.push_back(this->get(i));
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByPatientID(const string& patientID) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getID_patient() == patientID) {
            records.push_back(record);
        }
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByDiagnosis(const string& diagnosis) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        if (record.getDiagnosis() == diagnosis) {
            records.push_back(record);
        }
    }
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByRecordRange(const string &startDate, const string &endDate) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    for (int i = 0; i < this->size(); i++) {
        Date currentRecordDate = this->get(i).getDateOfRecord();
        if (currentRecordDate >= startDateObj && currentRecordDate <= endDateObj) {
            records.push_back(this->get(i));
        }
    }

    return records;
}

vector<pair<string, int>> listMedicalRecord::setDiagnosisCount() {
    vector<pair<string, int>> diagnosisCount;
    if (this->size() == 0) return diagnosisCount;

    map<string, int> diagnosisMap;

    for (int i = 0; i < this->size(); i++) {
        MedicalRecord record = this->get(i);
        string diagnosis = record.getDiagnosis();
        diagnosisMap[diagnosis]++;
    }

    for (const auto& pair : diagnosisMap) {
        diagnosisCount.push_back(pair);
    }

    return diagnosisCount;
}

void listMedicalRecord::addMedicalRecord(const string& patientID, Patient* patient, const string& symptoms, const string& diagnosis, const string& dateOfRecord) {
    MedicalRecord newRecord;

    newRecord.setID_record();
    newRecord.setID_patient(patientID);
    newRecord.setPatient(patient);
    newRecord.setSymptoms(symptoms);
    newRecord.setDiagnosis(diagnosis);
    newRecord.setDateOfRecord(dateOfRecord);

    this->append(newRecord);
    this->writeMedicalRecordToFile(this->size() - 1);
    this->writeListMedicalRecordToFile(false);
}

int listMedicalRecord::checkRecordID(const string& recordID) {
    Node<MedicalRecord> *current = this->head;
    if (current == NULL)
        return -1;

    for (int i = 0; i < this->size(); i++) {
        if (current->data.getID_record() == recordID)
            return i;
        current = current->next;
    }

    return -1;
}

bool listMedicalRecord::removeMedicalRecordByID(const string& recordID) {
    Node<MedicalRecord> *current = this->head;
    if (current == NULL)
        return false;

    int index = this->checkRecordID(recordID);
    if (index == -1)
        return false;

    this->remove(index);

    return true;
}

void listMedicalRecord::updateMedicalRecordByID(const string& recordID, const string& newDiagnosis, const string& newSymptoms) {
    Node<MedicalRecord> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkRecordID(recordID);
    if (index == -1)
        return;

    MedicalRecord curMR = this->get(index);
    string file_path = "../Database/Medical_recordDB/" + curMR.getID_record() + ".txt";
    if (std::remove(file_path.c_str()) != 0)
        return;

    curMR.setDiagnosis(newDiagnosis);
    curMR.setSymptoms(newSymptoms);

    this->set(index, curMR);
    this->writeMedicalRecordToFile(index);

    return;
}

vector<MedicalRecord> listMedicalRecord::searchMedicalRecord(SearchField_MR field, const string& value) {
    vector<MedicalRecord> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++) {
        string fieldValue;
        switch (field) {
        case SearchField_MR::RecordID:
            fieldValue = toLowerCase(this->get(i).getID_record());
            break;
        case SearchField_MR::PatientID:
            fieldValue = toLowerCase(this->get(i).getID_patient());
            break;
        case SearchField_MR::Diagnosis:
            fieldValue = toLowerCase(this->get(i).getDiagnosis());
            break;
        }

        if (fieldValue.find(lowerValue) == 0) {
            result.push_back(this->get(i));
        }
    }

    return result;
}

void listMedicalRecord::loadSymptomSolutionsFromFile() {
    path file_path = "../Database/Medical_recordDB/symptom_solutions.txt";
    file_path = absolute(file_path);

    ifstream file;
    file.open(file_path);

    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string symptom, solution;
        getline(stream, symptom, ';');
        getline(stream, solution);
        symptomSolutions[symptom] = solution;
    }

    file.close();
}

void listMedicalRecord::appendSymptomSolutionToFile(const string& symptom, const string& solution) {
    path file_path = "../Database/Medical_recordDB/symptom_solutions.txt";
    file_path = absolute(file_path);
    ofstream file;
    file.open(file_path, ios::app);

    if (!file.is_open()) return;

    file << symptom << ";" << solution << "\n";

    file.close();
}

map<string, int> listMedicalRecord::analyzeSymptomsAndProvideSolutions() {
    map<string, int> symptomFrequency;
    for (const MedicalRecord& record : this->setAllMedicalRecords()) {
        istringstream symptomsStream(record.getSymptoms());
        string symptom;
        while (getline(symptomsStream, symptom, ',')) {
            symptomFrequency[symptom]++;
        }
    }

    return symptomFrequency;

    // * Chạy giao diện thì viết cái này hen
    // for (const auto& entry : symptomFrequency) {
    //     cout << "Triệu chứng: " << entry.first << ", Số lần gặp: " << entry.second << "\n";
        
    //     auto it = symptomSolutions.find(entry.first);
    //     if (it != symptomSolutions.end()) {
    //         cout << "Giải pháp: " << it->second << "\n";
    //     } else {
    //         cout << "Giải pháp chưa có.\n";
    //     }
    // }
}