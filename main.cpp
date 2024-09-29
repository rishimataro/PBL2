#include "./Management/Single/Account.h"
// #include "./Management/Single/Date.h"
// #include "./Management/Single/Patient.h"

int main() {
    Account a;
    system("cls");
    a.inputAccount();
    a.printAccount();

    // fstream f;
    // f.open("./database/AccountDB/account.txt", ios::in);
    // a.setAccount(f);
    // system("cls");
    // a.printAccount();
    // f.close();

    fstream f;
    f.open("./database/AccountDB/account.txt", ios::app);
    a.saveAccount(f);
    f.close();

    // Date dayOfBirth;
    // dayOfBirth.inputDate();
    // dayOfBirth.printDate();

    // Patient p;
    // system("cls");
    // p.inputPatient();
    // p.printPatient();

    return 0;
}
