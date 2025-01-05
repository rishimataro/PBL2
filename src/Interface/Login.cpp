#include <Interface/Login.hpp>

void signup_UI(listAccount &accounts, listPatient &patients)
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

            AccountUser *account;
            // listAccount accounts;
            // accounts.readListAccountFromFile();
            int signup_return = accounts.signUp(account, username, password);
            if (signup_return == -1) {
                signup_announce_msg = "Tên đăng nhập đã tồn tại.";
                // signup_announce_msg = accounts.end().getUserName();
                return;
            }
            if (signup_return == 1) {
                AccountUser *user = dynamic_cast<AccountUser*>(account);
                signup_announce_msg = "Đăng ký thành công!";
                // listPatient patients;
                // patients.readListPatientFromFile();
                Patient *patient = new Patient();
                patient->setID_patient();
                Patientdisplay(patient);
                patients.append(patient);

                patients.writeListPatientToFile(1);
                // patients.writeListPatientToFile(0);
                // patients.writePatientToFile(patients.size() - 1);
                user->setID_patient(patient->getID_patient());
                // accounts.
                accounts.writeListAccountToFile(0, 1);
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
            vbox({
                text("Đăng ký tài khoản") | hcenter,
                separator(),
                username_input->Render(),
                password_input->Render(),
                confirm_password_input->Render(),
                text(signup_announce_msg) | hcenter,
            })| size(WIDTH, EQUAL, 80) | size(HEIGHT, EQUAL, 6) | border | hcenter,
            hbox({
                exit_button->Render(),
                signup_button->Render(),
            }) | hcenter,
            
        });
    }) ;
    screen.Loop(signup_renderer);
}
void forgot_password_UI(listAccount &accounts)
{
    auto screen = ScreenInteractive::Fullscreen();
    string username, new_password, confirm_password, CCCD;
    Element msg = text("");
    ftxui::InputOption input_pw_opt;
    input_pw_opt.password = true;
    Component forgot_password_form = Container::Vertical({
        Renderer([&]{return vbox({
            text("Quên mật khẩu") | hcenter,
            separator(),
        });}),
        Container::Horizontal({Renderer([&]
                                { return vbox({
                                    text("Tên đăng nhập:"),
                                    text("Số CCCD:"),
                                    text("Mật khẩu mới:"),
                                    text("Xác nhận mật khẩu:"),
                                }); }),
                                Renderer([&]
                                            { return separator(); }),
                                Container::Vertical({
                                     Input(&username, "Tên đăng nhập:"),
                                     Input(&CCCD, "Số CCCD:"),
                                     Input(&new_password, "Mật khẩu mới:", input_pw_opt),
                                     Input(&confirm_password, "Xác nhận mật khẩu:", input_pw_opt),
                                }) | size(WIDTH, EQUAL, 50),
                                }) | border,
            Renderer([&]
            { return msg; }) | hcenter,
            Container::Horizontal({
                Button("Quay lại", [&] {
                    // Exit the application
                    screen.ExitLoopClosure()();
                }),
            Button("Khôi phục mật khẩu", [&] {
                if(username.empty() || CCCD.empty() || new_password.empty() || confirm_password.empty())
                {
                    msg = text("Vui lòng điền đầy đủ thông tin!");

                }else if (new_password!= confirm_password)
                {
                    msg = text("Vui lòng nhập lại mật khẩu đúng!");
                }else if (!valid_password(new_password))
                {
                    msg = text("Mật khẩu phải có ít nhất 8 ký tự và bao gồm chữ cái, số và ký tự đặc biệt.");
                }
                else
                {
                    Account *account;
                    int result = accounts.forgotPassword(account, CCCD, username, new_password, confirm_password);
                    if (result == 1) {
                        msg = text("Khôi phục mật khẩu thành công!") | color(Color::Green);
                    }else if (result != -3)
                    {
                        msg = text("Tên đăng nhập hoặc Số CCCD không đúng!") | color(Color::Red);
                    }
                }
                
                
            }),
        }) | hcenter
    }) | hcenter;
    screen.Loop(forgot_password_form);
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
    Account *account;
    // accounts.readListAccountFromFile();
    listPatient patients;
    // patients.readListPatientFromFile();

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
            AccountUser* patient_account = dynamic_cast<AccountUser*>(account);
            // listPatient patients;
            // patients.readListPatientFromFile();
            string pt_id = patient_account->getID_patient();
            vector<Patient*> ls_Patients = patients.searchPatient(SearchField::ID, patient_account->getID_patient());
            Patient_UI(ls_Patients[0], patients, accounts, patient_account);
        }else if(login_result == 0) {
            Admin_UI();
        }


    }) | hcenter;

    Component switch_signUP = Button("Đăng ký", [&] {
        // Navigate to registration screen
        signup_UI(accounts, patients);
    }) | hcenter;
    Component forgot_password_button = Button("Quên mật khẩu?", [&] {
        // Navigate to password reset screen
        forgot_password_UI(accounts);
    }) | hcenter;
    Component exit_button = Button("       Thoát       ", [&] { screen.ExitLoopClosure()(); }) | hcenter;

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
                       size(WIDTH, EQUAL, 55),
                   password_input->Render() | borderStyled(ROUNDED) |
                       size(WIDTH, EQUAL, 55),
                   text(login_msg) | bold | color(Color::Red),
                   hbox({
                       login_button->Render() | center,
                       separatorEmpty() | size(WIDTH, EQUAL, 3),
                       switch_signUP->Render() | center,
                       separatorEmpty() | size(WIDTH, EQUAL, 3),
                           forgot_password_button->Render() | center,
                   }) | hcenter,
                   exit_button->Render() |
                       size(WIDTH, EQUAL, 25) | center,
 
               }) |
               border | center;
    });
    Component Main_layout = Container::Vertical({
        username_input | borderStyled(ROUNDED) | size(WIDTH, EQUAL, 55),
        password_input | borderStyled(ROUNDED) | size(WIDTH, EQUAL, 55),
        Renderer([&]{return text(login_msg) | bold | color(Color::Red); }) | hcenter,
        Container::Horizontal({
            login_button | center,
            Renderer([&]{return separatorEmpty()|size(WIDTH, EQUAL, 3);}),
            switch_signUP | center,
            Renderer([&]{return separatorEmpty()|size(WIDTH, EQUAL, 3);}),
            forgot_password_button | center,
        }) | hcenter,
        exit_button | center

    })|border | center;
    screen.Loop(Main_layout);
}