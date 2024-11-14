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
void loginUI()
{   
    string username, password;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component username_input = Input(username, "Tên đăng nhập: ");
    Component password_input = Input(password, "Mật khẩu: ");
    Component signin_button = Button("Đăng nhập", [&] {
        // Perform login logic here
    });
    Component signup_button = Button("Đăng ký", [] {
        // Navigate to registration screen
    });





}