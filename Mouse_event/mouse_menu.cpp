#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Khai báo các mục menu
struct MenuItem {
    string text;
    COORD position; // Tọa độ hiển thị của mục menu
};

vector<MenuItem> menu = {
    {"1. Option 1", {5, 5}},
    {"2. Option 2", {5, 7}},
    {"3. Option 3", {5, 9}},
    {"4. Exit", {5, 11}}
};

// Hàm hiển thị menu
void DisplayMenu() {
    for (const auto& item : menu) {
        // Di chuyển con trỏ đến vị trí của mục menu
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), item.position);
        cout << item.text;
    }
}

// Kiểm tra sự kiện click chuột
int CheckMouseClick(COORD mousePos) {
    for (int i = 0; i < menu.size(); i++) {
        COORD pos = menu[i].position;
        // Kiểm tra nếu click chuột nằm trong dòng của mục menu
        if (mousePos.Y == pos.Y && mousePos.X >= pos.X && mousePos.X < pos.X + menu[i].text.length()) {
            return i; // Trả về chỉ số của mục được click
        }
    }
    return -1; // Không click vào mục nào
}

int main() {
    // Cấu hình console để nhận sự kiện chuột
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
    SetConsoleOutputCP(CP_UTF8);
    INPUT_RECORD inputRecord;
    DWORD events;
    COORD mousePos;
    bool running = true;

    // Hiển thị menu
    DisplayMenu();

    while (running) {
        // Đọc sự kiện từ console
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        // Kiểm tra nếu sự kiện là sự kiện chuột
        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;
            if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                // Lấy vị trí con trỏ chuột khi click
                mousePos = mouseEvent.dwMousePosition;

                // Kiểm tra xem có click vào mục nào trong menu
                int choice = CheckMouseClick(mousePos);
                if (choice != -1) {
                    switch (choice) {
                        case 0:
                            cout << "\nBạn đã chọn Option 1\n";
                            break;
                        case 1:
                            cout << "\nBạn đã chọn Option 2\n";
                            break;
                        case 2:
                            cout << "\nBạn đã chọn Option 3\n";
                            break;
                        case 3:
                            cout << "\nThoát chương trình\n";
                            running = false;
                            break;
                    }
                }
            }
        }
    }

    // system("pause");
    return 0;
}
