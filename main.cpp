// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <Management/Appoinment.hpp>
#include <Management/listPatient.hpp>
#include <Management/Patient.hpp>
#include "Interface/Patient_interface.hpp"
#include "Management/Date.hpp"
// #include <fstream>
// #include <iostream>
// #include <windows.h>
#include <filesystem>
#include <string>
using namespace std;
// using namespace filesystem;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Patient pp;
    // pp.setID_patient();
    // pp.setAddress("1234 Hà Nội");
    // pp.setFullName("Cháo Thỏ");
    // pp.setPhone("0987654321");
    // pp.setCCCD("0001234567");
    // pp.setDayOfBirth("15/07/2005");
    // pp.setGender(true);
    listPatient list;
    list.readListPatientFromFile();
    vector<Patient> Patients = list.setAllPatient();
    Patient_UI(Patients[0]);
    // vector<Appoinment> apps = searchAppoinments(Patients[0]);
    // {   
    //     Appoinment app = apps[0];
    //     cout << "ID: " << app.getID() << ", Ngày khám: " << app.getDate().getDate() << ", ID bệnh nhân: " << app.getPatientID() << ", Giờ khám: " << GioKham(app.getTime());
    //     cout << ", Triệu chứng: " << app.getDescription() << ", Trạng thái: " << (app.getStatus() ? "Hiệu lực" : "Đã hủy") << ", Trạng thái khám: " << (app.getIsProcessed() ? "Đã khám" : "Chưa khám") << endl;
    // }
    // path file_path = DATA_PATH "AppoinmentDB";
    // file_path.append("2024_11.txt");
    // file_path = absolute(file_path);
    // cout << "File path: " << file_path << endl;
    // Date dd;
    // dd.setDate("16/11/2024");
    // Appoinment app(Patients[0], dd, 1, "Đau bụng");
    // app.ThemLichKham();
    // Component xxx = Patientdisplay(pp);

    // listPatient list;   
    // bool check = list.readListPatientFromFile();

    // if (check) {
    //     cout << "Read file successfully" << endl;
    // } else {
    //     cout << "Read file failed" << endl;
    // }

    // // list.addPatient();
    // vector<Patient> result = list.setPatientByBirthRange("01/01/2005", "01/03/2005");

    // for(const auto& p : result) {
    //     cout << p.getFullName() << endl;
    // }

    // cout << "----------------" << endl;
    // result = list.setAllPatient();
    // for(const auto& p : result) {
    //     cout << p.getFullName() << endl;
    // }
    
    // cout << "----------------" << endl;
    // result = list.searchPatient(SearchField::FullName, "Ng");
    // for(const auto& p : result) {
    //     cout << p.getFullName() << endl;
    // }

    // system("pause");
    return 0;
}

