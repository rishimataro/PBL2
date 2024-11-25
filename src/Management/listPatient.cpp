#include <Management/listPatient.hpp>

listPatient::listPatient() : LinkedList<Patient>() {
    this->readListPatientFromFile();
}

listPatient::~listPatient() {
    for (int i = 0; i < this->size(); i++) {
        delete this->get(i);
    }
    this->clear();
}

bool listPatient::readListPatientFromFile() {
    string file_path = "../Database/PatientDB/patient.txt";
    fstream fin;

    fin.open(file_path, ios::in);
    if (!fin.is_open()) {
        return false;
    }

    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            Patient* p = new Patient();
            p->readPatientFromFile(line);
            this->append(p);
        }
    }

    fin.close();
    return true;
}

bool listPatient::writeListPatientToFile(bool check) {
    string file_path = "../Database/PatientDB/patient.txt";
    ifstream fi(file_path);

    char lastChar;
    if (fi.is_open()) {
        fi.seekg(-1, ios::end);
        fi.get(lastChar);

        if (lastChar != '\n' && lastChar != '\0') {
            ofstream temp(file_path, ios::app);
            temp << "\n";
            temp.close();
        }
        fi.close();
    }

    ofstream fo;
    fo.open(file_path, check ? ios::trunc : ios::app);

    if (!fo.is_open()) {
        return false;
    }

    Patient* patient;
    if (check) {
        for (int i = 0; i < this->size(); i++) {
            patient = this->get(i);
            patient->writePatientToFile(fo);
        }
    } else {
        patient = this->get(this->size() - 1);
        patient->writePatientToFile(fo);
    }

    fo.close();
    return true;
}

vector<Patient*> listPatient::setPatientByGender(bool gender) {
    vector<Patient*> result;
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)->getGender() == gender)
            result.push_back(this->get(i));
    }
    return result;
}

vector<Patient*> listPatient::setPatientByBirthRange(const string& startDate, const string& endDate) {
    vector<Patient*> result;
    if (this->size() == 0)
        return result;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    for (int i = 0; i < this->size(); i++) {
        Date currentPatientDate = this->get(i)->getDayOfBirth();
        if (currentPatientDate >= startDateObj && currentPatientDate <= endDateObj)
            result.push_back(this->get(i));
    }

    return result;
}

vector<Patient*> listPatient::setAllPatient() {
    vector<Patient*> result;
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++) {
        result.push_back(this->get(i));
    }
    return result;
}

void listPatient::addPatient(const string& newFullName, const string& newPhone, const string& newDayOfBirth, const string& newCCCD, const string& newGender, const string& newAddress) {
    Patient* newPatient = new Patient();

    newPatient->setID_patient();
    newPatient->setFullName(newFullName);
    newPatient->setPhone(newPhone);
    newPatient->setDayOfBirth(newDayOfBirth);
    newPatient->setCCCD(newCCCD);
    newPatient->setGender(newGender == "Nữ");
    newPatient->setAddress(newAddress);

    this->append(newPatient);
    this->writeListPatientToFile(false);
}

int listPatient::checkID(const string& ID) {
    for (int i = 0; i < this->size(); i++) {
        if (this->get(i)->getID_patient() == ID) {
            return i;
        }
    }
    return -1;
}

bool listPatient::removePatientByID(const string& ID) {
    int index = this->checkID(ID);
    if (index == -1) return false;

    Patient* removedPatient = this->get(index);
    this->remove(index);
    this->writeListPatientToFile(true);
    
    delete removedPatient;
    return true;
}

bool listPatient::updatePatientByID(const string& ID, const string& newFullName, const string& newPhone, const string& newDayOfBirth, const string& newCCCD, const string& newGender, const string& newAddress) {
    int index = this->checkID(ID);
    if (index == -1) return false;

    Patient* currentPatient = this->get(index);
    currentPatient->setFullName(newFullName);
    currentPatient->setPhone(newPhone);
    currentPatient->setDayOfBirth(newDayOfBirth);
    currentPatient->setCCCD(newCCCD);
    currentPatient->setGender(newGender == "Nữ");
    currentPatient->setAddress(newAddress);

    return this->writeListPatientToFile(true);
}


vector<Patient*> listPatient::searchPatient(SearchField field, const string& value) {
    vector<Patient*> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++) {
        string fieldValue;
        switch (field) {
        case SearchField::ID:
            fieldValue = toLowerCase(this->get(i)->getID_patient());
            break;
        case SearchField::FullName:
            fieldValue = toLowerCase(this->get(i)->getFullName());
            break;
        case SearchField::CCCD:
            fieldValue = toLowerCase(this->get(i)->getCCCD());
            break;
        }

        if (fieldValue.find(lowerValue) == 0) {
            result.push_back(this->get(i));
        }
    }

    return result;
}
