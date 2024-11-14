// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
// #include "./Management/listAccount.h"
#include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/dom/elements.hpp>
// #include <Management/Appoinment.hpp>
#include <Management/listPatient.hpp>
#include <Management/Patient.hpp>
#include <Management/Account.hpp>
#include <Management/listAccount.hpp>
// #include <Interface/Patient_interface.hpp>
// #include <fstream>
// #include <iostream>
// #include <windows.h>
// #include <filesystem>
using namespace std;
// using namespace filesystem;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    listAccount listAcc;
    listPatient listPat;
    int check1 = listAcc.readListAccountFromFile();
    

    if(check1) cout << "Đọc file ACC thành công" << endl;
    else cout << "Đọc file ACC thất bại" << endl;

    // if(check2) cout << "Ghi file ACC thành công" << endl;
    // else cout << "Ghi file ACC thất bại" << endl;

    int check3 = listPat.readListPatientFromFile();
    // int check4 = listPat.writeListPatientToFile(true);

    if(check3) cout << "Đọc file PAT thành công" << endl;
    else cout << "Đọc file PAT thất bại" << endl;

    // if(check4) cout << "Ghi file PAT thành công" << endl;
    // else cout << "Ghi file PAT thất bại" << endl;

    // cout << "-------------------" << endl;
    // vector<Account> acc = listAcc.setAllAccount();
    // for(int i = 0; i < acc.size(); i++) {
    //     cout << acc[i].getID() << " " << acc[i].getUserName() << " " << acc[i].getPassword() << " " << acc[i].getRole() << " " << acc[i].getID_patient() << endl;
    // }    

    // cout << "-------------------" << endl;
    // vector<Account> acc1 = listAcc.setAccountByRole(1);
    // for(int i = 0; i < acc1.size(); i++) {
    //     cout << acc1[i].getID() << " " << acc1[i].getUserName() << " " << acc1[i].getPassword() << " " << acc1[i].getRole() << endl;
    // }

    // for(int i = 0; i < listAcc.size(); i++) {
    //     cout << "ID_Patient: " << listAcc.get(i).getID_patient() << endl;
    // }
    int check2 = listAcc.writeListAccountToFile(true);
    cout << "-------------------" << endl;
    if(check2) cout << "Ghi file ACC thành công" << endl;
    else cout << "Ghi file ACC thất bại" << endl;


    system("pause");
    return 0;
}