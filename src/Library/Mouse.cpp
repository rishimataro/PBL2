#include <Library/Mouse.hpp>

Point DetectLeftMouseClick() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); // Lấy handle của console input
    DWORD events;
    INPUT_RECORD inputRecord;
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT); // Kích hoạt chế độ mouse input

    while (true) {
        // Chờ cho đến khi có sự kiện input
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == MOUSE_EVENT) { // Kiểm tra sự kiện là mouse event
            MOUSE_EVENT_RECORD mer = inputRecord.Event.MouseEvent;

            if (mer.dwEventFlags == 0) { // Sự kiện click chuột (không di chuyển)
                if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    // Trả về tọa độ khi có click chuột trái
                    Point point = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
                    return point;
                }
            }
        }
    }
}
InputEvent MonitorInput() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;

    // Lưu chế độ hiện tại của đầu vào và bật chế độ xử lý sự kiện
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    INPUT_RECORD input_record;
    DWORD events;

    // Đọc sự kiện nhập vào
    ReadConsoleInput(hInput, &input_record, 1, &events);

    // Xử lý sự kiện bàn phím
    if (input_record.EventType == KEY_EVENT) {
        KEY_EVENT_RECORD key_event = input_record.Event.KeyEvent;
        if (key_event.bKeyDown) {
            if (key_event.wVirtualKeyCode == VK_ESCAPE) {
                SetConsoleMode(hInput, prev_mode); // Khôi phục chế độ
                return { InputEventType::Exit, 0, {0, 0} };
            }
            return { InputEventType::KeyPress, key_event.uChar.AsciiChar, {0, 0} };
        }
    }
    // Xử lý sự kiện chuột
    else if (input_record.EventType == MOUSE_EVENT) {
        MOUSE_EVENT_RECORD mouse_event = input_record.Event.MouseEvent;
        if (mouse_event.dwEventFlags == 0) { // Nhấn chuột
            if (mouse_event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                return { InputEventType::MouseLeftClick, 0, mouse_event.dwMousePosition };
            else if (mouse_event.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                return { InputEventType::MouseRightClick, 0, mouse_event.dwMousePosition };
        } else if (mouse_event.dwEventFlags == MOUSE_MOVED) { // Di chuyển chuột
            return { InputEventType::MouseMove, 0, mouse_event.dwMousePosition };
        } else if (mouse_event.dwEventFlags == DOUBLE_CLICK) { // Nhấp đôi
            return { InputEventType::MouseDoubleClick, 0, mouse_event.dwMousePosition };
        }
    }

    SetConsoleMode(hInput, prev_mode); // Khôi phục chế độ ban đầu
    return { InputEventType::None, 0, {0, 0} }; // Không có sự kiện nào
}
Point DetectMousePosition(HANDLE hInput) {
    DWORD events;
    INPUT_RECORD inputRecord;

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mer = inputRecord.Event.MouseEvent;
            if (mer.dwEventFlags == 0 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                return { mer.dwMousePosition.X, mer.dwMousePosition.Y };
            }
        }
    }
}
wchar_t DetectKeyboardInput(HANDLE hInput) {
    DWORD events;
    INPUT_RECORD inputRecord;

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            wchar_t ch = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
            return ch;
        }
    }
}
wchar_t simulated_getwch(wchar_t inputChar) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;  // Mã phím ảo
    input.ki.wScan = inputChar;  // Ký tự Unicode
    input.ki.dwFlags = KEYEVENTF_UNICODE; // Đặt cờ cho ký tự Unicode
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // Gửi sự kiện nhấn phím
    SendInput(1, &input, sizeof(INPUT));

    // Mô phỏng nhả phím
    input.ki.dwFlags = KEYEVENTF_KEYUP; // Cờ nhả phím
    SendInput(1, &input, sizeof(INPUT));

    return inputChar;
}