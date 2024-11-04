// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <Management/Appoinment.hpp>
#include <Interface/Patient_interface.hpp>
// #include <fstream>
// #include <iostream>
// #include <windows.h>
// #include <filesystem>
using namespace std;
// using namespace filesystem;
;int main() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    
    // Account a;
    // system("cls");
    // a.inputAccount();
    // a.printAccount();

    // fstream f;
    // f.open("./database/AccountDB/account.txt", ios::in);
    // a.setAccount(f);
    // system("cls");
    // a.printAccount();
    // f.close();

    // fstream f;
    // f.open("./database/AccountDB/account.txt", ios::app);
    // a.saveAccount(f);
    // f.close();

    // Date dayOfBirth;
    // dayOfBirth.inputDate();
    // dayOfBirth.printDate();

    // Patient p;
    // system("cls");
    // p.inputPatient();
    // fstream f;
    // string fileName = "./Database/PatientDB/" + p.getID_patient() + ".txt";
    // f.open(fileName, ios::out);
    // p.savePatient(f);
    // p.setPatient(f);
    // system("cls");
    // p.printPatient();
    // f.close();

    Patient pp;
    pp.setID_patient("P06");
    pp.setAddress("1234 Hà Nội");
    pp.setFullName("Cháo Thỏ");
    pp.setPhone("0987654321");
    pp.setDayOfBirth(Date(1, 9, 2005));
    pp.setGender(true);
    // listAccount list_acc;
    // list_acc.setListAccountByFile();
    // system("cls");
    // list_acc.printAllAccount();
    // Appoinment app;
    // Date date(28, 10, 2024);
    // app.setDate(date);
    // app.setTime(2);
    // app.setDescription("Dau dau");
    // app.setPatientID(pp);
    // cout << app.setID() << endl;
    // cout << app.writeToFile() << endl;
    
    // // printCalendar(10, 2024);

    Component xxx = Patientdisplay(pp);
    // ScreenInteractive screen = ScreenInteractive::Fullscreen();
    // screen.Loop(xxx);
    system("pause");
    return 0;
}
