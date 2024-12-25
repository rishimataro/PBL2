#include <Management/Appoinment.hpp>

Appoinment::Appoinment()
{
    this->ID = "T01";
    this->date.setDate("01/11/2024");
    this->time = 0;
    this->Patient_ID = "";
    this->description = "NULL";

}
void Appoinment::copy(const Appoinment& other){
    this->ID = other.ID;
    this->date = other.date;
    this->time = other.time;
    this->Patient_ID = other.Patient_ID;
    this->description = other.description;
    this->status = other.status;
    this->isProcessed = other.isProcessed;
}
Appoinment::Appoinment(Patient& patient, const Date& date, int time, const string& description)
{
    this->Patient_ID = patient.getID_patient();
    this->date = date;
    this->time = time;
    this->description = description;
}
bool Appoinment::UpdateStatus(const bool& Status, const bool& isProcessed)
{   
    map<string, vector<string>> lichKham;
    DocFileLich(lichKham);
    this->status = Status;
    this->isProcessed = isProcessed;
    for(string& lk : lichKham[this->getDate().getDate()])
    {
        if (lk.find(this->ID) == 0)
        {
            int pos = lk.length() - 1;
            lk.replace(pos - 2, 1, (this->status? "1" : "0"));
            lk.replace(pos, 1, (this->isProcessed? "1" : "0"));
            GhiFileLich(lichKham);
            return true;
        }
    }
    return false;
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
void Appoinment::setDescription(const string& description)
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
void Appoinment::setID(const string& ID)
{
    this->ID = ID;
}
bool Appoinment::setID()
{   
    path file_path = DATA_PATH "AppoinmentDB/";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    cout << file_path << endl;
    fstream fi;
    fi.open(file_path);
    string date = this->date.getDate();
    string line;
    int order = 0;
    bool isExistDate = false;
    int maxID = 0;
    if (!fi.is_open()) {
    }
    else
    {
        while (getline(fi, line)) {
        if (line == date) {
            isExistDate = true;
            continue;
        }
        if (isExistDate && !line.empty() && line != "---") {
            order++;
        }
        if (line == "---") {
            isExistDate = false;
        }
    }
    }
    ostringstream idStream;
    idStream << date.substr(6, 4) << date.substr(3, 2) << date.substr(0, 2) << (order + 1);
    this->ID = idStream.str();
    return true;
    // string id = to_string(maxID + 1);
    // id = string(6 - id.length(), '0') + id;
    // this->ID = id;
    // fi.close();
    // return true;
}
bool Appoinment::writeToFile()
{
    path file_path = DATA_PATH "AppoinmentDB";
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
        return false;
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
void Appoinment::DocFileLich(map<string, vector<string>>& lichKham) {
    path file_path = DATA_PATH "AppoinmentDB";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    ifstream file(file_path);
    string line;
    string currentDate;

    while (getline(file, line)) {
        if (line.empty() || line == "---") continue;

        // Nếu là dòng ngày mới
        if (line.find("/") != string::npos) {
            currentDate = line;
            lichKham[currentDate]; // Tạo vector trống nếu chưa có
        } else {
            // Thêm lịch vào danh sách của ngày hiện tại
            lichKham[currentDate].push_back(line);
        }
    }
    file.close();
}
void Appoinment::GhiFileLich(const map<string, vector<string>>& lichKham) 
{
    path file_path = DATA_PATH "AppoinmentDB";
    file_path.append(to_string(this->date.getYear()) + "_" + to_string(this->date.getMonth()) + ".txt");
    file_path = absolute(file_path);
    ofstream file(file_path);
    for (const auto& entry : lichKham) {
        file << entry.first << endl;
        // cout << entry.first <<endl;
        for (const auto& lich : entry.second) {
            file << lich << endl;
            // cout << lich << endl;
        }
        file << "---" << endl;
        // cout << "---" << endl;
    }
    file.close();
}
void Appoinment::ThemLichKham(const string& hieuLuc, const string& trangThai) {
    map<string, vector<string>> lichKham;
    DocFileLich(lichKham);
    const string ngay = this->date.getDate();
    const string maBenhNhan = this->Patient_ID;
    const string maGio = to_string(this->time);
    const string trieuChung = this->description;
    // Tạo ID tự động
    int soThuTu = lichKham[ngay].size() + 1;
    ostringstream idStream;
    idStream << ngay.substr(8, 2) << ngay.substr(3, 2) << ngay.substr(0, 2) << setw(3) << setfill('0') << soThuTu;
    string idLichKham = idStream.str();

    // Thêm lịch mới vào ngày tương ứng
    ostringstream lichMoi;
    lichMoi << idLichKham << ";" << maBenhNhan << ";" << maGio << ";" << trieuChung << ";" << hieuLuc << ";" << trangThai;
    lichKham[ngay].emplace_back(lichMoi.str());

    // Ghi lại file
    GhiFileLich(lichKham);
    // cout << "Lich kham voi ID: " << idLichKham << " da duoc tao thanh cong!" << endl;
    // cout << "Thông tin ghi trong file: " << lichMoi.str() << endl;
}
Appoinment& Appoinment::operator=(const Appoinment& app)
{
    this->ID = app.getID();
    this->date = app.getDate();
    this->time = app.getTime();
    this->Patient_ID = app.getPatientID();
    this->description = app.getDescription();
    this->status = app.getStatus();
    this->isProcessed = app.getIsProcessed();
    return *this;
}
struct tm to_tmDate(const std::string& date) {
    struct tm tm = {};
    int dd, mm, yyyy;
    char delim1, delim2;

    std::istringstream iss(date);
    iss >> dd >> delim1 >> mm >> delim2 >> yyyy;

    if (iss.fail() || delim1 != '/' || delim2 != '/') {
        std::cerr << "Định dạng ngày không hợp lệ." << std::endl;
        return tm;
    }

    tm.tm_mday = dd;
    tm.tm_mon = mm - 1; // Tháng trong struct tm từ 0-11
    tm.tm_year = yyyy - 1900; // Năm tính từ 1900

    return tm;
}
bool NamTrongKhoangThoiGian(const std::string& ngay, const struct tm& ngayBatDau, const struct tm& ngayKetThuc) {
    struct tm ngayKiemTra = to_tmDate(ngay);
    time_t tKiemTra = mktime(&ngayKiemTra);
    time_t tBatDau = mktime(const_cast<struct tm*>(&ngayBatDau));
    time_t tKetThuc = mktime(const_cast<struct tm*>(&ngayKetThuc));

    return tKiemTra >= tBatDau && tKiemTra <= tKetThuc;
}
vector<Appoinment> searchAppoinments(const Patient& patient)
{
    vector<Appoinment> result;
    //Ngày hiện tại
    time_t currentTime = time(0);
    struct tm currentDate = *localtime(&currentTime);

    //Ngày kết thúc (30 ngày sau)
    struct tm endDate = currentDate;
    endDate.tm_mday += 30;
    mktime(&endDate);


     // Lặp qua các file theo tháng để tìm kiếm
    for (int i = 0; i <= 1; ++i) {
        struct tm searching_month = currentDate;
        searching_month.tm_mon += i;
        mktime(&searching_month);

        path file_path = "../Database/AppoinmentDB/";
        file_path.append(to_string(searching_month.tm_year + 1900) + "_" + (searching_month.tm_mon + 1 < 10 ? "0" : "") + to_string(searching_month.tm_mon + 1) + ".txt");
        file_path = absolute(file_path);
        ofstream temp_fo("temp.txt", ios::app);
        ifstream file(file_path);
        temp_fo  << file_path;
        string line;
        string curDate;
        if (file.is_open()) {
            temp_fo << "1" << endl;
            temp_fo.close();
            while (std::getline(file, line)) {
                if (line.empty() || line == "---") continue;

                // Kiểm tra nếu là dòng ngày mới
                if (line.find("/") != std::string::npos) {
                    curDate = line;
                } else if (!curDate.empty() && line.find(patient.getID_patient()) != std::string::npos &&
                           NamTrongKhoangThoiGian(curDate, currentDate, endDate)) {
                          
                            stringstream ss(line);
                            Date dd;
                            dd.setDate(curDate);
                            Appoinment app;
                            string tmp;
                            app.setDate(dd);
                            getline(ss, tmp, ';');
                            app.setID(tmp);
                            getline(ss, tmp, ';');
                            app.setPatientID(tmp);
                            getline(ss, tmp, ';');
                            app.setTime(stoi(tmp));
                            getline(ss, tmp, ';');
                            app.setDescription(tmp);
                            getline(ss, tmp, ';');
                            app.setStatus(stoi(tmp));
                            app.setIsProcessed(line[line.length() - 1] - '0');
                    result.push_back(app);
                }
            }
            file.close();
        }
    }
    return result;
}

string GioKham(int time_slot){
    std::vector<std::string> time_slots = {
    "07:30 - 08:30", "08:30 - 09:30", "09:30 - 10:30", "10:30 - 11:30",
    "13:30 - 14:30", "14:30 - 15:30", "15:30 - 16:30", "16:30 - 17:00"
    };
    return time_slots[time_slot];
}
//Chưa xong
// void printCalendar(int month, int year) 
// {
//     int x = 20, y = 5, w = 12, h = 2;
//     vector<string> monthNames = {"Tháng 1", "Tháng 2", "Tháng 3", "Tháng 4", "Tháng 5", "Tháng 6",
//                                 "Tháng 7", "Tháng 8", "Tháng 9", "Tháng 10", "Tháng 11", "Tháng 12"};
//     vector<string> dayNames = {"CN", "Hai", "Ba", "Tư", "Năm", "Sáu", "Bảy"};

//     // In tiêu đề tháng và năm
//     gotoXY(x, y);
//     cout << "   " << monthNames[month - 1] << " " << year << endl;

//     box(x, y + 2, w, h, "    CN    ", "e8f2f7", "#e4e7ee", "fa531f");
//     box(x + w, y + 2, w, h, "    Hai    ", "e8f2f7", "#e4e7ee", "#003553");
//     box(x + 2 * w, y + 2, w, h, "    Ba    ", "e8f2f7", "#e4e7ee", "#003553");
//     box(x + 3 * w, y + 2, w, h, "    Tư    ", "e8f2f7", "#e4e7ee", "#003553");
//     box(x + 4 * w, y + 2, w, h, "    Năm    ", "e8f2f7", "#e4e7ee", "#003553");
//     box(x + 5 * w, y + 2, w, h, "    Sáu    ", "e8f2f7", "#e4e7ee", "#003553");
//     box(x + 6 * w, y + 2, w, h, "    Bảy    ", "e8f2f7", "#e4e7ee", "#003553");

//     // Lấy ngày bắt đầu và số ngày trong tháng
//     int startDay = getStartDayOfMonth(month, year);
//     int daysInMonth = getDaysInMonth(month, year);

//     // In khoảng trống cho tuần đầu tiên
//     for (int i = 0; i < startDay; i++) {
//         cout << setw(5) << " ";
//     }

//     // In các ngày trong tháng
//     for (int day = 1; day <= daysInMonth; day++) {
//         cout << setw(5) << day;
//         if ((startDay + day) % 7 == 0) {
//             cout << endl;  // Xuống dòng sau khi in thứ Bảy
//         }
//     }
//     cout << endl;
// }

// void AppoinmentUI()
// {

//     Date currentDate;
//     currentDate.setCurrentDate();

// }
