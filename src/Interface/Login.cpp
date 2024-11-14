#include <Interface/Login.hpp>
void signup_UI()
{   
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    string username, password, confirm_password;
    Component username_input = Input(username, "Tên đăng nhập: ");
    InputOption input_password_option;
    input_password_option.password = true;
    
    // input_password_option.multiline = false;
    Component password_input = Input(password, "Mật khẩu: ", input_password_option);
    Component confirm_password_input = Input(confirm_password, "Xác nhận mật khẩu: ", input_password_option);
    Component signup_button = Button("Đăng ký", [&] {
        // Perform signup logic here
    });
    Component exit_button = Button("Quay lại", [] {
        // Exit the application
    });
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
            // vector<Patient> ls_Patients = patients.searchPatient(SearchField::ID, account.getID_patient());
            // login_msg = account.getID_patient();
            vector<Patient> ls_Patients = patients.setAllPatient();
            for (auto& pt : ls_Patients) {
                if (pt.getID_patient() == pt_id) {
                    Patient_UI(pt);
                    break;
                }
            }
                // login_msg = ls_Patients.empty() ? "Không tìm thấy bệnh nhân nào!" : "Có bệnh nhân!";
            // login_msg = ls_Patients[0].getFullName();
        }

    });
    Component switch_button = Button("Đăng ký", [] {
        // Navigate to registration screen
    });
    Component exit_button = Button("Exit", [&] { exit(1); });

    auto container = Container::Vertical(Components{
        username_input,
        password_input,
        login_button,
        switch_button,
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
                       switch_button->Render() |
                           size(WIDTH, EQUAL, 25) | center,
                   }),
                   exit_button->Render() |
                       size(WIDTH, EQUAL, 25) | center,
 
               }) |
               border | center | hcenter;
    });
 
    screen.Loop(renderer);


}