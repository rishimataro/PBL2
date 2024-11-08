// // #include "./Management/Single/Account.h"
// // #include "./Management/Single/Date.h"
// // #include "./Management/Single/Patient.h"
// // #include "./Management/listAccount.h"
// #include <ftxui/component/component.hpp>        // for Button, Renderer, Input, etc.
// #include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
// #include <ftxui/dom/elements.hpp>
// #include <Management/Appoinment.hpp>
// #include <Interface/Patient_interface.hpp>
// // #include <fstream>
// // #include <iostream>
// // #include <windows.h>
// // #include <filesystem>
// using namespace std;
// // using namespace filesystem;
// ;int main() {
//         SetConsoleOutputCP(CP_UTF8);
//         SetConsoleCP(CP_UTF8);
    
//     // Account a;
//     // system("cls");
//     // a.inputAccount();
//     // a.printAccount();

//     // fstream f;
//     // f.open("./database/AccountDB/account.txt", ios::in);
//     // a.setAccount(f);
//     // system("cls");
//     // a.printAccount();
//     // f.close();

//     // fstream f;
//     // f.open("./database/AccountDB/account.txt", ios::app);
//     // a.saveAccount(f);
//     // f.close();

//     // Date dayOfBirth;
//     // dayOfBirth.inputDate();
//     // dayOfBirth.printDate();

//     // Patient p;
//     // system("cls");
//     // p.inputPatient();
//     // fstream f;
//     // string fileName = "./Database/PatientDB/" + p.getID_patient() + ".txt";
//     // f.open(fileName, ios::out);
//     // p.savePatient(f);
//     // p.setPatient(f);
//     // system("cls");
//     // p.printPatient();
//     // f.close();

//     Patient pp;
//     pp.setID_patient("P06");
//     pp.setAddress("1234 Hà Nội");
//     pp.setFullName("ばかやろ");
//     pp.setPhone("0987654321");
//     pp.setDayOfBirth(Date(1, 9, 2005));
//     pp.setGender(true);
//     // listAccount list_acc;
//     // list_acc.setListAccountByFile();
//     // system("cls");
//     // list_acc.printAllAccount();
//     // Appoinment app;
//     // Date date(28, 10, 2024);
//     // app.setDate(date);
//     // app.setTime(2);
//     // app.setDescription("Dau dau");
//     // app.setPatientID(pp);
//     // cout << app.setID() << endl;
//     // cout << app.writeToFile() << endl;
    
//     // // printCalendar(10, 2024);

//     // Patientdisplay(pp);
//     // Appoinment_UI(pp);
//     Patient_UI(pp);
//     // ScreenInteractive screen = ScreenInteractive::Fullscreen();
//     // screen.Loop(xxx);
//     system("pause");
//     return 0;
// }
// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <memory>  // for allocator, __shared_ptr_access, shared_ptr
#include <string>  // for string

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Input, Renderer, ResizableSplitLeft
#include "ftxui/component/component_base.hpp"  // for ComponentBase, Component
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, separator, text, Element, flex, vbox, border

int main() {
  using namespace ftxui;

  std::string content_1;
  std::string content_2;
  auto textarea_1 = Input(&content_1);
  auto textarea_2 = Input(&content_2);
  int size = 50;
  auto layout = ResizableSplitLeft(textarea_1, textarea_2, &size);

  auto component = Renderer(layout, [&] {
    return vbox({
               text("Input:"),
               separator(),
               layout->Render() | flex,
           }) |
           border;
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(component);
}
