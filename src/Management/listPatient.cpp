#include <Management/listPatient.hpp>

//* Constructor & Destructor
listPatient::listPatient()
{
    this->head = NULL;
}

listPatient::~listPatient()
{
    if (this->head == NULL)
        return;

    Node<Patient> *current = this->head;
    Node<Patient> *tail = this->head->prev;

    do
    {
        Node<Patient> *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

//* Read & Write
bool listPatient::readListPatientFromFile()
{
    string file_path = "../Database/PatientDB/patient.txt";
    fstream fin, patientFile;
    Patient patient;

    fin.open(file_path, ios::in);
    if (!fin.is_open())
        return false;
    
    Patient p;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            break;

        p.readPatientFromFile(line);
        this->append(p);
    }
    fin.close();
    return true;
}

bool listPatient::writeListPatientToFile(bool check)
{
    string file_path = "../Database/PatientDB/patient.txt";
    char ch;

    ofstream fo;
    check ? fo.open(file_path, ios::trunc) : fo.open(file_path, ios::app);

    if (!fo.is_open())
        return false;

    Patient patient;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
            patient = this->get(i);
            patient.writePatientToFile(fo);
        }
    }
    else
    {
        patient = this->get(this->size() - 1);
        patient.writePatientToFile(fo);
    }

    fo.close();

    return true;
}

//* Setter & Getter
vector<Patient> listPatient::setPatientByGender(bool gender)
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    forEach([&](Patient patient) {
        if (patient.getGender())
            result.push_back(patient);
    });
    return result;
}

vector<Patient> listPatient::setPatientByBirthRange(const string &startDate, const string &endDate)
{
    vector<Patient> result;
    if(this->size() == 0)
        return result;

    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    forEach([&](Patient patient) {
        Date currentPatientDate = patient.getDayOfBirth();
        if (currentPatientDate >= startDateObj && currentPatientDate <= endDateObj)
            result.push_back(patient);
    });

    return result;
}
vector<Patient> listPatient::setAllPatient()
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    forEach([&](Patient patient) {
        result.push_back(patient);
    });
    return result;
}

//* Add
void listPatient::addPatient(const string &newFullName, const string &newPhone, const string &newDayOfBirth, const string &newCCCD, const string &newGender, const string &newAddress)
{
    Patient newPatient;

    newPatient.setID_patient();
    newPatient.setFullName(newFullName);
    newPatient.setPhone(newPhone);
    newPatient.setDayOfBirth(newDayOfBirth);
    newPatient.setCCCD(newCCCD);

    newPatient.setGender(newGender == "Nữ");
    newPatient.setAddress(newAddress);

    this->append(newPatient);
    this->writePatientToFile(this->size() - 1);
    this->writeListPatientToFile(false);

    return;
}

//* Check
int listPatient::checkID(const string &ID)
{
    for(int i = 0; i < this->size(); i++) {
        if(this->get(i).getID_patient() == ID) {
            return i;
        }
    }
    return -1;
}

//* Delete
bool listPatient::removePatientByID(const string &ID)
{
    Node<Patient> *current = this->head;
    if (current == NULL) return false;

    int index = this->checkID(ID);
    if (index == 0) return false;

    this->remove(index);
    this->writeListPatientToFile(true);

    return true;
}

//* Update
bool listPatient::updatePatientByID(const string &ID, const string &newFullName, const string &newPhone, const string &newDayOfBirth, const string &newCCCD, const string &newGender, const string &newAddress) {

    fstream file;
    string file_path = "../Database/PatientDB/patient.txt";
    file.open(file_path, ios::in | ios::out);

    if (!file.is_open()) return false;

    string line;
    bool updated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string patientID;
        getline(ss, patientID, ';');

        if (patientID == ID) {
            file.seekp(file.tellg() - line.length() - 1);
            file << ID << ";" << newFullName << ";" << newPhone << ";" << newDayOfBirth << ";" << newCCCD << ";" << (newGender == "Nữ" ? "Nữ" : "Nam") << ";" << newAddress << endl;
            updated = true;
            break;
        }
    }

    if (!updated) return false;
    
    file.close();

    Patient currentPatient = this->get(index);
    currentPatient.setFullName(newFullName);
    currentPatient.setPhone(newPhone);
    currentPatient.setDayOfBirth(newDayOfBirth);
    currentPatient.setCCCD(newCCCD);
    currentPatient.setGender(newGender == "Nữ");
    currentPatient.setAddress(newAddress);

    this->set(index, currentPatient);
    return true;
}

//* Search
vector<Patient> listPatient::searchPatient(SearchField field, const string &value) {
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++) {
        string fieldValue;
        switch (field) {
        case SearchField::ID:
            fieldValue = toLowerCase(this->get(i).getID_patient());
            break;
        case SearchField::FullName:
            fieldValue = toLowerCase(this->get(i).getFullName());
            break;
        case SearchField::CCCD:
            fieldValue = toLowerCase(this->get(i).getCCCD());
            break;
        }

        if (fieldValue.find(lowerValue) == 0) {
            result.push_back(this->get(i));
        }
    }

    return result;
}