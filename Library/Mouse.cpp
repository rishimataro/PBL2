#include "Mouse.h"

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