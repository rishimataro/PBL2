#include <Management/Appoinment.h>

Appoinment::Appoinment()
{
    this->ID = "T01";
    this->date.setCurrentDate();
    this->time = 0;
    this->Patient_ID = "";
    this->description = "NULL";

}
void Appoinment::setDate(Date date)
{
    this->date = date;
}
void Appoinment::setTime(int time)
{
    this->time = time;
}
void Appoinment::setPatientID(const Patient& patient)
{
    this->Patient_ID = patient.getID_patient();
}
void Appoinment::setDescription(const std::string& description)
{
    this->description = description;
}
    //Chưa sử dụng!!!!!!!
void Appoinment::readFromFile()
{   
    string filename = "../../Database/AppoinmentDB/";
    filename.append(to_string(this->date.getYear()) + "." + to_string(this->date.getMonth()) + ".txt");
    ifstream fi(filename, ios::in);

}
bool Appoinment::setID()
{   
    path file_path = "./Database/AppoinmentDB/";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    cout << file_path << endl;
    fstream fi;
    fi.open(file_path);

    int maxID = 0;
    if (!fi.is_open()) {
        maxID = 0;
    }
    else
    {
        if(isFileEmpty(fi)) maxID = 0;
        else
        {
            string temp;
            moveToEndOfLastLine(fi);
            getline(fi, temp, ';');
            maxID = stoi(temp);
        }
    }
    string id = to_string(maxID + 1);
    id = string(6 - id.length(), '0') + id;
    this->ID = id;
    fi.close();
    return true;
}
bool Appoinment::writeToFile()
{
    path file_path = "./Database/AppoinmentDB/";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);

    ofstream fo;
    string data;
    ifstream fi(file_path);
    fi.seekg(-1, ios::end);
    char ch;
    fi.get(ch);
    if(ch != '\n' && ch != '\0') data.push_back('\n');
    fi.close();

    fo.open(file_path, ios::app);
    if (!fo.is_open()) {
        return false; // File không mở
    }
    data.append(this->ID + ";");
    data.append(to_string(this->date.getDay()) + ";");
    data.append(to_string(this->time) + ";");
    data.append(this->Patient_ID + ";");
    data.append(this->description + "\n");
    fo << data;
    fo.close();
    return true;
}
Appoinment::~Appoinment(){}

//Chưa xong
void printCalendar(int month, int year) 
{
    int x = 20, y = 5, w = 12, h = 2;
    vector<string> monthNames = {"Tháng 1", "Tháng 2", "Tháng 3", "Tháng 4", "Tháng 5", "Tháng 6",
                                "Tháng 7", "Tháng 8", "Tháng 9", "Tháng 10", "Tháng 11", "Tháng 12"};
    vector<string> dayNames = {"CN", "Hai", "Ba", "Tư", "Năm", "Sáu", "Bảy"};

    // In tiêu đề tháng và năm
    gotoXY(x, y);
    cout << "   " << monthNames[month - 1] << " " << year << endl;

    box(x, y + 2, w, h, "    CN    ", "e8f2f7", "#e4e7ee", "fa531f");
    box(x + w, y + 2, w, h, "    Hai    ", "e8f2f7", "#e4e7ee", "#003553");
    box(x + 2 * w, y + 2, w, h, "    Ba    ", "e8f2f7", "#e4e7ee", "#003553");
    box(x + 3 * w, y + 2, w, h, "    Tư    ", "e8f2f7", "#e4e7ee", "#003553");
    box(x + 4 * w, y + 2, w, h, "    Năm    ", "e8f2f7", "#e4e7ee", "#003553");
    box(x + 5 * w, y + 2, w, h, "    Sáu    ", "e8f2f7", "#e4e7ee", "#003553");
    box(x + 6 * w, y + 2, w, h, "    Bảy    ", "e8f2f7", "#e4e7ee", "#003553");

    // Lấy ngày bắt đầu và số ngày trong tháng
    int startDay = getStartDayOfMonth(month, year);
    int daysInMonth = getDaysInMonth(month, year);

    // In khoảng trống cho tuần đầu tiên
    for (int i = 0; i < startDay; i++) {
        cout << setw(5) << " ";
    }

    // In các ngày trong tháng
    for (int day = 1; day <= daysInMonth; day++) {
        cout << setw(5) << day;
        if ((startDay + day) % 7 == 0) {
            cout << endl;  // Xuống dòng sau khi in thứ Bảy
        }
    }
    cout << endl;
}

void AppoinmentUI()
{

    Date currentDate;
    currentDate.setCurrentDate();

}
