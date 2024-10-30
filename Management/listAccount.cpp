#include "./listAccount.h"

// * Constructor & Destructor
listAccount::listAccount()
{
    this->head = NULL;
}

listAccount::~listAccount()
{
    if (this->head == NULL)
    {
        return;
    }

    Node<Account> *current = this->head;
    Node<Account> *tail = this->head->prev;

    do
    {
        Node<Account> *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    this->head = NULL;
}

// * Setter & Getter
int listAccount::setCountRole(int role)
{
    int count = 0;
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getRole() == role)
            count++;
    }
    return count;
}

void listAccount::setListAccountByFile()
{
    fstream fin;
    fin.open("./Database/AccountDB/account.txt", ios::in);

    if (!fin.is_open())
        return;

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        Account account;
        account.setAccount(line);
        this->append(account);
    }
    fin.close();
}

void listAccount::saveListAccountToFile()
{
    fstream fout;
    fout.open("./Database/AccountDB/account.txt", ios::out);

    if (!fout.is_open())
        return;

    for (int i = 0; i < this->size(); i++)
    {
        this->get(i).saveAccount(fout);
    }

    fout.close();
}

// * Display
void boxAccountHorizontal(int x, int y, int w, int h, int size)
{
    // void box(int x, int y, int boxWidth, int boxHeight, string content, string backgroundColor, string borderColor, string textColor);
    box(x, y, w - 5, h, "      ID", BLACK, WHITE, GREEN);
    box(x + 15, y, w + 5, h, "        TÀI KHOẢN", BLACK, WHITE, ORANGE);
    box(x + 40, y, w, h, "      MẬT KHẨU", BLACK, WHITE, BLUE);
    box(x + 60, y, w, h, "      VAI TRÒ", BLACK, WHITE, PURPLE);

    gotoXY(x + 15, y);
    cout << "┬";
    for (int i = 2; i < 4; i++)
    {
        gotoXY(x + (i * 20), y);
        cout << "┬";
    }

    for (int i = 0; i < size; i++)
    {
        y += 2;
        emptyBox(x, y, w - 5, h, 15, 1);
        emptyBox(x + 15, y, w + 5, h, 15, 1);
        emptyBox(x + 40, y, w, h, 15, 1);
        emptyBox(x + 60, y, w, h, 15, 1);

        gotoXY(x, y);
        cout << "├";
        gotoXY(x + 80, y);
        cout << "┤";
        gotoXY(x + 15, y);
        cout << "┼";
        for (int j = 2; j < 4; j++)
        {
            gotoXY(x + (j * 20), y);
            cout << "┼";
        }
    }

    gotoXY(x, y + 2);
    gotoXY(x + 15, y + 2);
    cout << "┴";
    for (int i = 2; i < 4; i++)
    {
        gotoXY(x + (i * 20), y + 2);
        cout << "┴";
    }
}

void listAccount::printAccountByRole(int role)
{
    if (this->size() == 0)
        return;

    int x = 40, y = 5, w = 20, h = 2, size = this->size(); // tổng w = 60
    string roleStr;
    int roleCount = this->setCountRole(role);

    if (role == 0)
        roleStr = "Quản trị viên";
    else if (role == 1)
        roleStr = "Bác sĩ";
    else if (role == 2)
        roleStr = "Bệnh nhân";

    box_(x, y - 3, 80, h, "DANH SÁCH TÀI KHOẢN CÓ VAI TRÒ LÀ '" + roleStr + "'", WHITE, WHITE, BLUE);
    boxAccountHorizontal(x, y, w, h, roleCount);

    int y2 = 8;
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getRole() == role)
        {
            gotoXY(x + 1, y2);
            this->get(i).printAccountHorizontal();
            y2 += 2;
        }
    }

    gotoXY(x, y2);
}

void listAccount::printAllAccount()
{
    if (this->size() == 0)
        return;

    int x = 40, y = 5, w = 20, h = 2, size = this->size(); // tổng w = 80

    box_(x, y - 3, 80, h, "                       DANH SÁCH TẤT CẢ TÀI KHOẢN HIỆN CÓ", WHITE, WHITE, RED);
    boxAccountHorizontal(x, y, w, h, size);

    int y2 = 8;
    for (int i = 0; i < this->size(); i++)
    {
        gotoXY(x + 1, y2);
        this->get(i).printAccountHorizontal();
        y2 += 2;
    }

    gotoXY(x, y2);
}

// * Sign Up & Sign In
string enterPassword()
{
    string pw;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && pw.length() > 0)
        {
            cout << "\b \b";
            pw.pop_back();
        }
        else if (ch != '\b')
        {
            cout << "●";
            pw.push_back(ch);
        }
    }
    return pw;
}

string enterUserName()
{
    string name;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && name.length() > 0)
        {
            cout << "\b \b";
            name.pop_back();
        }
        else if (ch != '\b')
        {
            cout << ch;
            name.push_back(ch);
        }
    }
    return name;
}

int enterRole()
{
    int role = 0;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch >= '0' && ch <= '2')
        {
            role = ch - '0';
            cout << ch;
        }
        else if (ch == '\b')
        {
            cout << "\b \b";
            role = 0;
        }
    }
    return role;
}

void listAccount::signUp(Account &account)
{
    string tmpID, tmpUserName, tmpPassword, tmpRePassword;
    int tmpRole;
    // string tmpName, tmpPhone, tmpDOB, tmpAddress;
    // bool tmpGender;

    int x = 60, y = 10, w = 40, h = 2;
    int a, b;
    Point point;
    this->count++;
    tmpID = "ACC" + to_string(this->count);

SIGNUP:
    // Tạo các button
    // (string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height);
    button btn_userName("Tài khoản      : ", WHITE, BLUE, BLUE, x, y, w, h),
        btn_password("Mật khẩu       : ", WHITE, GREEN, GREEN, x, y + 3, w, h),
        btn_RePassword("Xác nhận lại MK: ", WHITE, ORANGE, ORANGE, x, y + 6, w, h),
        btn_signUp("Đăng ký", GREEN, WHITE, GREEN, x + 4, y + 10, w - 30, h),
        btn_exit("Quay lại", YELLOW, WHITE, YELLOW, x + 25, y + 10, w - 30, h);

    emptyBox2(x - 5, y - 5, w + 10, h + 16, WHITE, WHITE);
    box_(x, y - 3, w, h, "            ĐĂNG KÝ TÀI KHOẢN", WHITE, RED, RED);

    btn_userName.draw();
    btn_password.draw();
    btn_RePassword.draw();
    btn_signUp.draw();
    btn_exit.draw();

    button *buttons[] = {&btn_userName, &btn_password, &btn_RePassword, &btn_signUp, &btn_exit};

    cout << setTextColor(BLACK) << setBackgroundColor(WHITE);
    while (true)
    {
        point = DetectLeftMouseClick();

        button *clickedButton = setClick(point, buttons, 5);

        if (clickedButton == &btn_userName)
        {
            gotoXY(x + 18, y + 1);
            tmpUserName = enterUserName();
            gotoXY(x + 18, y + 4);
            tmpPassword = enterPassword();
            gotoXY(x + 18, y + 7);
            tmpRePassword = enterPassword();
        }
        else if (clickedButton == &btn_signUp)
        {
            if (tmpPassword != tmpRePassword)
            {
                gotoXY(x, y + 16);
                cout << resetColor() << setTextColor(PINK) << setItalic() << "Mật khẩu và mật khẩu xác nhận không khớp!" << endl;
                gotoXY(x + 6, y + 17);
                cout << setTextColor(GREY);
                system("pause");
                system("cls");
                goto SIGNUP;
            }
            else
            {
                gotoXY(x + 10, y + 16);
                cout << resetColor() << setTextColor(GREEN) << setItalic() << "Đăng ký thành công!\n";
                gotoXY(x + 6, y + 17);
                cout << setTextColor(GREY);
                system("pause");
                break;
            }
        }
        else if (clickedButton == &btn_exit)
        {
            //
            return;
        }
    }
    // Thêm thông tin tài khoản
    account.setID(tmpID);
    account.setUserName(tmpUserName);
    account.setPassword(tmpPassword);
    account.setRole(tmpRole);
    this->append(account);
    this->saveListAccountToFile();

    // Thêm thông tin bệnh nhân



    cout << resetColor();
    return;
}

void listAccount::signIn(Account &account)
{
    string tmpUserName, tmpPassword;
    int tmpRole;
    int x = 60, y = 10, w = 40, h = 2;
    int a, b;
    Point point;

SIGNIN:
    // (string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height);
    button btn_userName("Tài khoản: ", WHITE, BLUE, BLUE, x, y, w, h),
        btn_password("Mật khẩu : ", WHITE, GREEN, GREEN, x, y + 3, w, h),
        btn_role("Vai trò  : ", WHITE, ORANGE, ORANGE, x, y + 6, w, h),
        btn_login("Đăng nhập", GREEN, WHITE, GREEN, x + 4, y + 10, w - 30, h),
        btn_exit("Quay lại", YELLOW, WHITE, YELLOW, x + 25, y + 10, w - 30, h),
        btn_forgotPassword("Quên mật khẩu", WHITE, RED, WHITE, x + 13, y + 14, w - 20, h);

    emptyBox2(x - 5, y - 5, w + 10, h + 20, WHITE, WHITE);
    box_(x, y - 3, w, h, "          ĐĂNG NHẬP TÀI KHOẢN", WHITE, RED, RED);

    btn_userName.draw();
    btn_password.draw();
    btn_role.draw();
    btn_login.draw();
    btn_exit.draw();
    btn_forgotPassword.draw();

    button *buttons[] = {&btn_userName, &btn_password, &btn_role, &btn_login, &btn_exit, &btn_forgotPassword};

    cout << setTextColor(BLACK) << setBackgroundColor(WHITE);
    while (true)
    {
        point = DetectLeftMouseClick();

        button *clickedButton = setClick(point, buttons, 6);

        if (clickedButton == &btn_userName)
        {
            gotoXY(x + 13, y + 1);
            tmpUserName = enterUserName();
            gotoXY(x + 13, y + 4);
            tmpPassword = enterPassword();
            gotoXY(x + 13, y + 7);
            tmpRole = enterRole();
        }
        else if (clickedButton == &btn_login)
        {
            if (this->checkSignIn(tmpUserName, tmpPassword, tmpRole, account) == false)
            {
                gotoXY(x - 7, y + 19);
                cout << resetColor() << setTextColor(PINK) << setItalic() << "Tài khoản hoặc mật khẩu hoặc vai trò sai! Vui lòng nhập lai!" << endl;
                gotoXY(x + 7, y + 20);
                cout << setTextColor(GREY);
                system("pause");
                system("cls");
                goto SIGNIN;
            }
            else
            {
                gotoXY(x + 10, y + 19);
                cout << resetColor() << setTextColor(GREEN) << setItalic() << "Đăng nhập thành công!\n";
                gotoXY(x + 8, y + 20);
                cout << setTextColor(GREY);
                system("pause");
                break;
            }
        }
        else if (clickedButton == &btn_exit)
        {
            //
            return;
        }
        else if (clickedButton == &btn_forgotPassword)
        {
            cout << resetColor();
            system("cls");
            this->forgotPassword(account);
            return;
        }
    }
    cout << resetColor();
    return;
}

bool listAccount::checkSignIn(const string &userName, const string &password, const int &role, Account &account)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getUserName() == userName && this->get(i).getPassword() == password && this->get(i).getRole() == role)
        {
            account = this->get(i);
            return true;
        }
    }
    return false;
}

void listAccount::forgotPassword(Account &account)
{
    string tmpUserName, tmpPassword, tmpRePassword;
    int index = -1;
    int x = 60, y = 10, w = 40, h = 2;

    // Tạo giao diện đơn giản
    button btn_userName("Nhập tài khoản   : ", WHITE, BLUE, BLUE, x, y, w, h),
           btn_password("Nhập mật khẩu mới: ", WHITE, GREEN, GREEN, x, y + 3, w, h),
           btn_RePassword("Xác nhận lại MK  : ", WHITE, ORANGE, ORANGE, x, y + 6, w, h),
           btn_submit("Xác nhận", GREEN, WHITE, GREEN, x + 4, y + 10, w - 30, h),
           btn_exit("Quay lại", YELLOW, WHITE, YELLOW, x + 25, y + 10, w - 30, h);

FORGOT_PASSWORD:
    emptyBox2(x - 5, y - 5, w + 10, h + 16, WHITE, WHITE);
    box_(x, y - 3, w, h, "           QUÊN MẬT KHẨU", WHITE, RED, RED);

    btn_userName.draw();
    btn_password.draw();
    btn_RePassword.draw();
    btn_submit.draw();
    btn_exit.draw();

    button *buttons[] = {&btn_userName, &btn_password, &btn_RePassword, &btn_submit, &btn_exit};

    cout << setTextColor(BLACK) << setBackgroundColor(WHITE);
    Point point;

    while (true) {
        point = DetectLeftMouseClick();
        button *clickedButton = setClick(point, buttons, 5);

        if (clickedButton == &btn_userName) {
            gotoXY(x + 20, y + 1);
            tmpUserName = enterUserName();

            index = -1;
            for (int i = 0; i < this->size(); i++) {
                if (this->get(i).getUserName() == tmpUserName) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                gotoXY(x, y + 16);
                cout << resetColor() << setTextColor(PINK) << setItalic() << "Tài khoản không tồn tại! Vui lòng thử lại." << endl;
                gotoXY(x + 2, y + 17);
                cout << setTextColor(GREY);
                system("pause");
                system("cls");
                goto FORGOT_PASSWORD;
            }
        } else if (clickedButton == &btn_password) {
            gotoXY(x + 20, y + 4);
            tmpPassword = enterPassword();
        } else if (clickedButton == &btn_RePassword) {
            gotoXY(x + 20, y + 7);
            tmpRePassword = enterPassword();
        } else if (clickedButton == &btn_submit) {
            if (tmpPassword != tmpRePassword) {
                gotoXY(x, y + 16);
                cout << resetColor() << setTextColor(GREEN) << setItalic() << "Mật khẩu và mật khẩu xác nhận không khớp!";
                gotoXY(x + 2, y + 17);
                cout << setTextColor(GREY);
                system("pause");
                system("cls");
                goto FORGOT_PASSWORD;
            }

            // Cập nhật mật khẩu mới
            this->get(index).setPassword(tmpPassword);
            this->saveListAccountToFile();
            gotoXY(x + 1, y + 16);
            cout << resetColor() << setTextColor(GREEN) << setItalic() << "Mật khẩu đã được cập nhật thành công!";
            gotoXY(x + 3, y + 17);
            cout << setTextColor(GREY);
            system("pause");
            system("cls");
            break;
        } else if (clickedButton == &btn_exit) {
            // Quay lại đăng nhập trong menu
            return;
        }
    }
}

// * Check
int listAccount::checkID(const string &ID)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getID() == ID)
            return i;
    }
    return 0;
}

int listAccount::checkUserName(const string &userName)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getUserName() == userName)
            return i;
    }
    return 0;
}
int listAccount::checkPassword(const string &password)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getPassword() == password)
            return i;
    }
    return 0;
}
int listAccount::checkRole(const int &role)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->get(i).getRole() == role)
            return i;
    }
    return 0;
}

// * Delete
void listAccount::removeAccountByID(const string &ID) {
    Node<Account> *current = this->head;
    if (current == NULL)
        return;

    int x = 60, y = 10, w = 20, h = 2;
    int index = checkID(ID);
    if (index == 0) {
        gotoXY(x + 10, y - 5);
        cout << resetColor() << setTextColor(RED) << setBackgroundColor(WHITE) << "ID không tồn tại!" << endl;
        cout << setTextColor(GREY);
        system("pause");
        system("cls");
        return;
    }

    // Confirmation prompt
    button btn_confirm("Chắc chắn", GREEN, WHITE, GREEN, x, y, w, h),
           btn_cancel("Không", RED, WHITE, RED, x + 25, y, w, h);

    box_(x - 5, y - 3, w + 30, h + 5, "Bạn chắc chắn muốn xóa tài khoản này không?", WHITE, WHITE, RED);

    btn_confirm.draw();
    btn_cancel.draw();

    button *buttons[] = {&btn_confirm, &btn_cancel};
    Point point;

    while (true) {
        point = DetectLeftMouseClick();
        button *clickedButton = setClick(point, buttons, 2);

        if (clickedButton == &btn_confirm) {
            this->remove(index);
            gotoXY(x, y - 5);
            cout << resetColor() << setTextColor(RED) << setItalic() << "Xóa tài khoản thành công!" << endl;
            gotoXY(x, y - 4);
            cout << setTextColor(GREY);
            system("pause");
            system("cls");
            this->saveListAccountToFile();
            break;
        } else if (clickedButton == &btn_cancel) {
            gotoXY(x, y - 5);
            cout << resetColor() << setTextColor(PINK) << setItalic() << "Hủy xóa tài khoản." << endl;
            gotoXY(x, y - 4);
            cout << setTextColor(GREY);
            system("pause");
            system("cls");
            break;
        }
    }
    return;
}

//* Update Account
void listAccount::updateAccountByID(const string &ID) {
    Node<Account> *current = this->head;
    if (current == NULL) return;

    int x = 40, y = 8, w = 30, h = 2;
    int x2  = x + 40;

    int index = checkID(ID);
    if (index == 0) {
        gotoXY(x, y + 20);
        cout << "ID không tồn tại!" << endl;
        return;
    }

    Account currentAcc = this->get(index);
    Point point;
    string newUserName, newPassword;

    button btn_ID, btn_userName, btn_password, btn_role,
           btn_confirm("Xác nhận", GREEN, WHITE, GREEN, x + 20, y + 15, w - 20, h),
           btn_exit("Quay lại", YELLOW, WHITE, YELLOW, x + 40, y + 15, w - 20, h);
SIGNUP: 
    box_(x, y - 3, w, h, "THÔNG TIN CŨ", WHITE, WHITE, RED);
    btn_ID.set("ID       : ", WHITE, BLUE, BLUE, x, y, w, h); btn_ID.draw();
    btn_userName.set("Tài khoản: ", WHITE, GREEN, GREEN, x, y + 3, w, h); btn_userName.draw();
    btn_password.set("Mật khẩu : ", WHITE, ORANGE, ORANGE, x, y + 6, w, h); btn_password.draw();
    btn_role.set("Vai trò  : ", WHITE, ORANGE, ORANGE, x, y + 9, w, h); btn_role.draw();
    gotoXY(x, y);
    cout << setTextColor(BLACK) << setBackgroundColor(WHITE);
    currentAcc.printAccountVertical();

    box_(x2, y - 3, w, h, "THÔNG TIN SỬA ĐỔI", WHITE, WHITE, GREEN);
    btn_ID.set("ID       : ", WHITE, BLUE, BLUE, x2, y, w, h); btn_ID.draw();
    btn_userName.set("Tài khoản: ", WHITE, GREEN, GREEN, x2, y + 3, w, h); btn_userName.draw();
    btn_password.set("Mật khẩu : ", WHITE, ORANGE, ORANGE, x2, y + 6, w, h); btn_password.draw();
    btn_role.set("Vai trò  : ", WHITE, ORANGE, ORANGE, x2, y + 9, w, h); btn_role.draw();

    btn_confirm.draw();
    btn_exit.draw();

    button *buttons[] = { &btn_ID, &btn_userName, &btn_password, &btn_role, &btn_confirm, &btn_exit };
    
    while (true) {
        gotoXY(x2 + 12, y + 1); cout << setTextColor(BLACK) << setBackgroundColor(WHITE) << currentAcc.getID();
        gotoXY(x2 + 12, y + 10); cout << setTextColor(BLACK) << setBackgroundColor(WHITE) << currentAcc.getRoleToString();
        point = DetectLeftMouseClick();
        button *clickedButton = setClick(point, buttons, 6);

        // Xử lý nhập liệu cho từng nút
        if (clickedButton == &btn_userName) {
            gotoXY(x2 + 12, y + 4);
            newUserName = enterUserName();
            if (!newUserName.empty()) {
                currentAcc.setUserName(newUserName);
            }
        } else if (clickedButton == &btn_password) {
            gotoXY(x2 + 12, y + 7);
            newPassword = enterPassword();
            if (!newPassword.empty()) {
                currentAcc.setPassword(newPassword);
            }
        } else if (clickedButton == &btn_confirm) {
            // Kiểm tra thông tin trước khi cập nhật
            if (!currentAcc.getUserName().empty() && !currentAcc.getPassword().empty()) {
                this->set(index, currentAcc);
                this->saveListAccountToFile();
                cout << resetColor();
                gotoXY(x + 28, y + 20); cout << setTextColor(GREEN) << setItalic() << "Cập nhật thành công!" << endl;
                gotoXY(x + 25, y + 21); cout << setTextColor(GREY);
                system("pause");
                system("cls");
                break;
            } else {
                gotoXY(x, y + 20);
                gotoXY(x + 25, y + 20); cout << setTextColor(PINK) << setItalic() << "Tên đăng nhập hoặc mật khẩu không hợp lệ!" << endl;
                gotoXY(x + 27, y + 21); cout << setTextColor(GREY);
                system("pause");
                system("cls");
                goto SIGNUP;
            }
        } else if (clickedButton == &btn_exit) {
            // Thoát khi nhấn nút quay lại
            return;
        }
    }
    return;
}

// * Search (tuong doi)
string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void listAccount::searchAccountByID(const string &ID)
{
    if (this->size() == 0)
        return;

    int x = 40, y = 5, w = 20, h = 2;
    int totalAccounts = this->size();
    bool found = false;

    string lowerID = toLowerCase(ID);

    box_(x, y - 3, 80, h, "DANH SÁCH TÀI KHOẢN CÓ ID BẮT ĐẦU BẰNG '" + ID + "'", WHITE, WHITE, PINK);

    for (int i = 0; i < totalAccounts; i++)
    {
        string id_search = toLowerCase(this->get(i).getID());

        if (id_search.find(lowerID) == 0)
        {
            if (!found)
            {
                box(x, y, w - 5, h, "ID", WHITE, WHITE, GREEN);
                box(x + 15, y, w + 5, h, "TÀI KHOẢN", WHITE, WHITE, ORANGE);
                box(x + 40, y, w, h, "MẬT KHẨU", WHITE, WHITE, BLUE);
                box(x + 60, y, w, h, "VAI TRÒ", WHITE, WHITE, PURPLE);

                gotoXY(x + 15, y);
                cout << "┬";
                for (int j = 2; j < 4; j++)
                {
                    gotoXY(x + (j * 20), y);
                    cout << "┬";
                }
                y += 2;
            }

            emptyBox(x, y, w - 5, h, 15, 1);
            emptyBox(x + 15, y, w + 5, h, 15, 1);
            emptyBox(x + 40, y, w, h, 15, 1);
            emptyBox(x + 60, y, w, h, 15, 1);

            gotoXY(x, y);
            cout << "├";
            gotoXY(x + 80, y);
            cout << "┤";
            gotoXY(x + 15, y);
            cout << "┼";
            for (int j = 2; j < 4; j++)
            {
                gotoXY(x + (j * 20), y);
                cout << "┼";
            }

            gotoXY(x + 1, y + 1);
            this->get(i).printAccountHorizontal();
            y += 2;

            found = true;
        }
    }

    if (!found)
    {
        gotoXY(x + 10, y);
        cout << resetColor() << setTextColor(PURPLE) << setBackgroundColor(WHITE) << setItalic() << "KHÔNG CÓ TÀI KHOẢN CẦN TÌM!" << endl;
    }
    else
    {
        gotoXY(x + 15, y);
        cout << "┴";
        for (int i = 2; i < 4; i++)
        {
            gotoXY(x + (i * 20), y);
            cout << "┴";
        }
    }
}

void listAccount::searchAccountByUserName(const string &userName)
{
    if (this->size() == 0)
        return;

    int x = 40, y = 5, w = 20, h = 2;
    int totalAccounts = this->size();
    bool found = false;

    string lowerUserName = toLowerCase(userName);

    box_(x, y - 3, 80, h, "DANH SÁCH TÀI KHOẢN CÓ USERNAME BẮT ĐẦU BẰNG '" + userName + "'", WHITE, WHITE, PINK);

    for (int i = 0; i < totalAccounts; i++)
    {
        string userName_search = toLowerCase(this->get(i).getUserName());

        if (userName_search.find(lowerUserName) == 0)
        {
            if (!found)
            {
                box(x, y, w - 5, h, "ID", WHITE, WHITE, GREEN);
                box(x + 15, y, w + 5, h, "TÀI KHOẢN", WHITE, WHITE, ORANGE);
                box(x + 40, y, w, h, "MẬT KHẨU", WHITE, WHITE, BLUE);
                box(x + 60, y, w, h, "VAI TRÒ", WHITE, WHITE, PURPLE);

                gotoXY(x + 15, y);
                cout << "┬";
                for (int j = 2; j < 4; j++)
                {
                    gotoXY(x + (j * 20), y);
                    cout << "┬";
                }
                y += 2;
            }

            emptyBox(x, y, w - 5, h, 15, 1);
            emptyBox(x + 15, y, w + 5, h, 15, 1);
            emptyBox(x + 40, y, w, h, 15, 1);
            emptyBox(x + 60, y, w, h, 15, 1);

            gotoXY(x, y);
            cout << "├";
            gotoXY(x + 80, y);
            cout << "┤";
            gotoXY(x + 15, y);
            cout << "┼";
            for (int j = 2; j < 4; j++)
            {
                gotoXY(x + (j * 20), y);
                cout << "┼";
            }

            gotoXY(x + 1, y + 1);
            this->get(i).printAccountHorizontal();
            y += 2;

            found = true;
        }
    }

    if (!found)
    {
        gotoXY(x + 10, y);
        cout << resetColor() << setTextColor(PURPLE) << setBackgroundColor(WHITE) << setItalic() << "KHÔNG CÓ TÀI KHOẢN CẦN TÌM!" << endl;
    }
    else
    {
        gotoXY(x + 15, y);
        cout << "┴";
        for (int i = 2; i < 4; i++)
        {
            gotoXY(x + (i * 20), y);
            cout << "┴";
        }
    }
}