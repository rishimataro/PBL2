// #include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"
#include "./Management/listAccount.h"

int main() {
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

    listAccount list_acc;
    list_acc.setListAccountByFile();
    system("cls");
    list_acc.printAllAccount();
    system("pause");
    return 0;
}
