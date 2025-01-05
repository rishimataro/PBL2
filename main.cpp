// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>          // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
// #include <Management/Appoinment.hpp>
// #include <Management/listPatient.hpp>
// #include <Management/Patient.hpp>
// #include <Management/listMedicalRecord.hpp>
#include <Management/MedicalRecord.hpp>
// #include <Management/listAppoinment.hpp>
// #include "Interface/Patient_interface.hpp"
// #include "Management/Date.hpp"
#include "Interface/Login.hpp"
// #include <fstream>
// #include <iostream>
// #include <windows.h>
#include <filesystem>
#include <string>
using namespace std;
// using namespace filesystem;
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    homeUI();
    // loginUI();
    // dang nhap admin
    // listAccount accounts;
    // string username = "admin123@", password = "123456789";
    // Account *account;
    // cout << "Dang nhap ADMIN" << endl;
    // int check = accounts.signIn(account, username, password);
    // cout << 111 << endl;

    // if(check == 1) {
    //     cout << "Dang nhap USER thanh cong" << endl;
    // }
    // else if(check == 0) {
    //     cout << "Dang nhap ADMIN thanh cong" << endl;
    // }
    // else if(check == -1) {
    //     cout << "Dang nhap that bai" << endl;
    // }

    system("pause");
    return 0;
}