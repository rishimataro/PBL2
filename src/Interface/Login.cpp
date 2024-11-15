#include <Interface/Login.hpp>
bool valid_password(const string& password) {
    if (password.length() < 8) {
        return false;
    }
    if (!regex_search(password, regex("[a-zA-Z]"))) {
        return false;
    }
    if (!regex_search(password, regex("[0-9]"))) {
        return false;
    }
    if (!regex_search(password, regex("[!@#$%^&*()_+=-\\[\\]{};':\"\\\\|,.<>/?]"))) {
        return false;
    }
    return true;
    
}
void signup_UI()
{   
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    string username, password, confirm_password;
    Component username_input = Input(&username, "Tên đăng nhập: ");
    InputOption input_password_option;
    input_password_option.password = true;
    string signup_msg[] = {
        "Vui lòng điền đầy đủ thông tin!",
        "Mật khẩu phải có ít nhất 8 ký tự và bao gồm chữ cái, số và ký tự đặc biệt."
        "Mật khẩu phải khác tên đăng nhập."
        "Vui lòng nhập lại mật khẩu đúng."
        "Tên đăng nhập đã tồn tại."
    };
    string signup_announce_msg;
    // input_password_option.multiline = false;
    Component password_input = Input(&password, "Mật khẩu: ", input_password_option);
    Component confirm_password_input = Input(&confirm_password, "Xác nhận mật khẩu: ", input_password_option);
    Component signup_button = Button("Đăng ký", [&] {
        // Perform signup logic here
        if (username.empty() || password.empty() || confirm_password.empty()) {
            signup_announce_msg = "Vui lòng điền đầy đủ thông tin!";
            return;
        }else
        if (password!= confirm_password) {
            signup_announce_msg = "Vui lòng nhập lại mật khẩu đúng.";
            return;
        }else
        if (!valid_password(password)) {
            signup_announce_msg = "Mật khẩu phải có ít nhất 8 ký tự và bao gồm chữ cái, số và ký tự đặc biệt.";
            return;
        }else
        if (password == username) {
            signup_announce_msg = "Mật khẩu phải khác tên đăng nhập.";
            return;
        }
        else
        {

            Account account;
            listAccount accounts;
            accounts.readListAccountFromFile();
            int signup_return = accounts.signUp(account, username, password);
            if (signup_return == -1) {
                // signup_announce_msg = "Tên đăng nhập đã tồn tại.";
                signup_announce_msg = accounts.end().getUserName();
                return;
            }
            if (signup_return == 1) {
                signup_announce_msg = "Đăng ký thành công!";
                listPatient patients;
                patients.readListPatientFromFile();
                Patient patient;
                patient.setID_patient();
                Patientdisplay(patient);
                patients.append(patient);

                patients.writeListPatientToFile(1);
                // patients.writeListPatientToFile(0);
                patients.writePatientToFile(patients.size() - 1);
                account.setID_patient(patient.getID_patient());
                accounts.set(accounts.size() - 1, account);
                accounts.writeListAccountToFile(1);
                // screen.ExitLoopClosure()();
                return;
            }
        }

    });
    Component exit_button = Button("Quay lại", [&] {
        // Exit the application
        screen.ExitLoopClosure()();
    });
    Component Signup_container = Container::Vertical({
        username_input,
        password_input,
        confirm_password_input,
        Container::Horizontal({
            exit_button,
            signup_button,
        }),
    });
    Component signup_renderer = Renderer(Signup_container, [&](){
        return vbox({
            text("Đăng ký tài khoản") | hcenter,
            separator(),
            username_input->Render(),
            password_input->Render(),
            confirm_password_input->Render(),
            text(signup_announce_msg) | hcenter,
            separator(),
            hbox({
                exit_button->Render(),
                signup_button->Render(),
            }),
        });
    }) | size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 10) | border | hcenter;
    screen.Loop(signup_renderer);
}
void login_process(const string& username, const string& password, listAccount& accounts)
{

}
void loginUI()
{   
    string username, password;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    string login_error_msg[] = {
        "Tên đăng nhập hoặc mật khẩu không đúng!",
        "Vui lòng điền đầy đủ thông tin!"
    };
    string login_msg;
    Component username_input = Input(&username, "Tên đăng nhập:");
    InputOption input_password_option;
    input_password_option.password = true;
    Component password_input = Input(&password, "Mật khẩu:", input_password_option);
    listAccount accounts;
    Account account;
    accounts.readListAccountFromFile();
    Component login_button = Button("Đăng nhập", [&] {
        if (username.empty() || password.empty()) {
            login_msg = login_error_msg[1];
            return;
        }
        int login_result = accounts.signIn(account, username, password);
        if (login_result == -1)
        {
            login_msg = login_error_msg[0];
            return;
        }
        // Perform login logic here
            login_msg = "Đăng nhập thành công!";
        if(login_result == 1) {
            listPatient patients;
            patients.readListPatientFromFile();
            string pt_id = account.getID_patient();
            vector<Patient> ls_Patients = patients.searchPatient(SearchField::ID, account.getID_patient());
            Patient_UI(ls_Patients[0]);
            // login_msg = account.getID_patient();
            // vector<Patient> ls_Patients = patients.setAllPatient();
            // for (auto& pt : ls_Patients) {
            //     if (pt.getID_patient() == pt_id) {
            //         Patient_UI(pt);
            //         break;
            //     }
            // }
                // login_msg = ls_Patients.empty() ? "Không tìm thấy bệnh nhân nào!" : "Có bệnh nhân!";
            // login_msg = ls_Patients[0].getFullName();
        }

    });
    Component switch_signUP = Button("Đăng ký", [] {
        // Navigate to registration screen
        signup_UI();
    });
    Component exit_button = Button("Exit", [&] { screen.ExitLoopClosure()(); });

    auto container = Container::Vertical(Components{
        username_input,
        password_input,
        login_button,
        switch_signUP,
        exit_button,
        Renderer(
            [&] { return text(login_msg) | bold | color(Color::Red); }),
    });
 
    auto renderer = Renderer(container, [&] {
        return vbox({
                   username_input->Render() | borderStyled(ROUNDED) |
                       size(WIDTH, EQUAL, 50),
                   password_input->Render() | borderStyled(ROUNDED) |
                       size(WIDTH, EQUAL, 50),
                   text(login_msg) | bold | color(Color::Red),
                   hbox({
                       login_button->Render() |
                           size(WIDTH, EQUAL, 25) | center,
                       switch_signUP->Render() |
                           size(WIDTH, EQUAL, 25) | center,
                   }),
                   exit_button->Render() |
                       size(WIDTH, EQUAL, 25) | center,
 
               }) |
               border | center | hcenter;
    });
 
    screen.Loop(renderer);


}