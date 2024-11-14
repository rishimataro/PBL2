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

    string id;
    while (getline(fin, id))
    {
        if (id.empty())
            continue;

        file_path = "../Database/PatientDB/" + id + ".txt";
        patientFile.open(file_path, ios::in);

        if (!patientFile.is_open())
            continue;

        patient.readPatientFromFile(patientFile);
        this->append(patient);

        patientFile.close();
    }
    fin.close();
    return true;
}

bool listPatient::writeListPatientToFile(bool check)
{
    string file_path = "../Database/PatientDB/patient.txt";
    char ch;

    ofstream fo;
    if (check)
    {
        fo.open(file_path, ios::trunc); 
    }
    else
    {
        fo.open(file_path, ios::app);  
    }

    if (!fo.is_open())
        return false;

    Patient patient;
    if (check)
    {
        for (int i = 0; i < this->size(); i++)
        {
            patient = this->get(i);
            patient.writePatientToFile_all(fo);
        }
    }
    else
    {
        patient = this->get(this->size() - 1);
        patient.writePatientToFile_all(fo);
    }

    fo.close();

    return true;
}

bool listPatient::writePatientToFile(int index)
{
    string path = "../Database/PatientDB/";
    string fileName = path + this->get(index).getID_patient() + ".txt";

    fstream fout;
    fout.open(fileName, ios::out);

    if (!fout.is_open())
    {
        return false;
    }

    this->get(index).writePatientToFile(fout);
    fout.close();
    return true;
}

//* Setter & Getter
vector<Patient> listPatient::setPatientByGender(bool gender)
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    for (int i = 0; i < this->size(); i++)
    {
        Patient patient = this->get(i);
        if (patient.getGender() == gender)
        {
            result.push_back(patient);
        }
    }
    return result;
}

vector<Patient> listPatient::setPatientByBirthRange(const string &startDate, const string &endDate)
{
    vector<Patient> result;

    // Chuyển đổi startDate và endDate thành đối tượng Date
    Date startDateObj, endDateObj;
    startDateObj.setDate(startDate);
    endDateObj.setDate(endDate);

    // Duyệt qua danh sách bệnh nhân và tìm những bệnh nhân có ngày sinh trong phạm vi
    for (int i = 0; i < this->size(); i++)
    {
        // Lấy ngày sinh của bệnh nhân
        Date currentPatientDate = this->get(i).getDayOfBirth();

        // Kiểm tra nếu ngày sinh của bệnh nhân trong khoảng startDate và endDate
        if (currentPatientDate >= startDateObj && currentPatientDate <= endDateObj)
        {
            result.push_back(this->get(i));
        }
    }

    return result;
}
vector<Patient> listPatient::setAllPatient()
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    result.reserve(this->size());
    for (int i = 0; i < this->size(); i++)
    {
        result.push_back(this->get(i));
    }
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
    int left = 0, right = this->size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        string midID = this->get(mid).getID_patient();
        if (midID == ID)
            return mid;
        if (midID < ID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

//* Delete
void listPatient::removePatientByID(const string &ID)
{
    Node<Patient> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == 0)
        return;

    this->remove(index);

    return;
}

//* Update
void listPatient::updatePatientByID(const string &ID, const string &newFullName, const string &newPhone, const string &newDayOfBirth, const string &newCCCD, const string &newGender, const string &newAddress)
{
    Node<Patient> *current = this->head;
    if (current == NULL)
        return;

    int index = this->checkID(ID);
    if (index == 0)
        return;

    Patient currentPatient = this->get(index);
    string file_path = "../Database/PatientDB/" + currentPatient.getID_patient() + ".txt";
    if (std::remove(file_path.c_str()) != 0)
        return;

    currentPatient.setFullName(newFullName);
    currentPatient.setPhone(newPhone);
    currentPatient.setDayOfBirth(newDayOfBirth);
    currentPatient.setCCCD(newCCCD);
    currentPatient.setGender(newGender == "Nữ");
    currentPatient.setAddress(newAddress);

    this->set(index, currentPatient);
    this->writePatientToFile(index);
    return;
}

//* Search
vector<Patient> listPatient::searchPatient(SearchField field, const string &value)
{
    vector<Patient> result;
    if (this->size() == 0)
        return result;

    string lowerValue = toLowerCase(value);

    for (int i = 0; i < this->size(); i++)
    {
        string fieldValue;
        switch (field)
        {
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

        if (fieldValue.find(lowerValue) != 0)
        {
            result.push_back(this->get(i));
        }
    }

    return result;
}