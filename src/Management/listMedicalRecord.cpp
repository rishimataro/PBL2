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
    check ? fo.open(file_path, ios::trunc) : fo.open(file_path, ios::app);

    if (!fo.is_open())
        return false;

    MedicalRecord record;
    if (check) {
        forEach([&](MedicalRecord record) {
            fo << record.getID_record() << "\n";
        });
    } else {
        record = this->get(this->size() - 1);
        record.writeMedicalRecordToFile(fo);
    }

    fo.close();
    return true;
}

vector<MedicalRecord> listMedicalRecord::setAllMedicalRecords() {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    forEach([&](MedicalRecord record) {
        records.push_back(record);
    });
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByPatientID(const string& patientID) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    forEach([&](MedicalRecord record) {
        if (record.getID_patient() == patientID) {
            records.push_back(record);
        }
    });
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByDiagnosis(const string& diagnosis) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    forEach([&](MedicalRecord record) {
        if (record.getDiagnosis() == diagnosis) {
            records.push_back(record);
        }
    });
    return records;
}

vector<MedicalRecord> listMedicalRecord::setMedicalRecordsByRecordRange(const string &startDate, const string &endDate) {
    vector<MedicalRecord> records;
    if (this->size() == 0) return records;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    forEach([&](MedicalRecord record) {
        Date currentRecordDate = record.getDateOfRecord();
        if (currentRecordDate >= startDateObj && currentRecordDate <= endDateObj) {
            records.push_back(record);
        }
    });

    return records;
}

vector<pair<string, int>> listMedicalRecord::setDiagnosisCount() {
    vector<pair<string, int>> diagnosisCount;
    if (this->size() == 0) return diagnosisCount;

    map<string, int> diagnosisMap;

    forEach([&](MedicalRecord record) {
        string diagnosis = record.getDiagnosis();
        diagnosisMap[diagnosis]++;
    });

    for (const auto& pair : diagnosisMap) {
        diagnosisCount.push_back(pair);
    }

    return diagnosisCount;
}

void listMedicalRecord::addMedicalRecord(const string& patientID, const string& symptoms, const string& diagnosis, const string& dateOfRecord) {
    MedicalRecord newRecord;

    newRecord.setID_record();
    newRecord.setID_patient(patientID);
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
    this->writeListMedicalRecordToFile(true);

    return true;
}

void listMedicalRecord::updateMedicalRecordByID(const string& recordID, const string& newDiagnosis, const string& newSymptoms) {
    Node<MedicalRecord> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkRecordID(recordID);
    if (index == -1)
        return;

    string file_path = "../Database/Medical_recordDB/medical_record.txt";
    fstream file;
    file.open(file_path, ios::in | ios::out);
    if (!file.is_open()) return;

    string line;
    bool updated = false;

    while(getline(file, line)) {
        if (line == recordID) {
            file.seekp(file.tellg() - line.length() - 1);
            file << recordID << ";" << newDiagnosis << ";" << newSymptoms << endl;
            updated = true;
            break;
        }
    }

    if (!updated) return;

    file.close();

    MedicalRecord curMR = this->get(index);
    curMR.setDiagnosis(newDiagnosis);
    curMR.setSymptoms(newSymptoms);

    this->set(index, curMR);
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
        string diagnosis, solution;
        getline(stream, diagnosis, ';');
        getline(stream, solution);
        symptomSolutions[diagnosis] = solution;
    }

    file.close();
}

map<string, string> listMedicalRecord::getSymptomSolutions() {
    return symptomSolutions;
}

bool listMedicalRecord::appendDiagnosisSolutionToFile(const string& diagnosis, const string& solution) {
    this->symptomSolutions[diagnosis] = solution;

    path file_path = "../Database/Medical_recordDB/symptom_solutions.txt";
    file_path = absolute(file_path);

    ofstream file;
    file.open(file_path, ios::app);

    if (!file.is_open()) return false;

    file << diagnosis << ";" << solution << "\n";

    file.close();
    return true;
}

string listMedicalRecord::analyzeDiagnosisAndProvideSolutions(const string& diagnosis) {
    auto it = symptomSolutions.find(diagnosis);
    if (it != symptomSolutions.end()) {
        return it->second;
    } else {
        return "No solution available for this diagnosis.";
    }
}