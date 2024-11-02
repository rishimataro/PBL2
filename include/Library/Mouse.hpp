#include <windows.h>

struct Point {
    int x;
    int y;
};
// Hàm detect và trả về tọa độ khi có click chuột trái
Point DetectLeftMouseClick();

enum class InputEventType {
    None,
    KeyPress,
    MouseLeftClick,
    MouseRightClick,
    MouseMove,
    MouseDoubleClick,
    Exit
};

struct InputEvent {
    InputEventType type;
    char key;   // Chứa phím nhấn (nếu có)
    COORD position; // Vị trí chuột (nếu có)
};

InputEvent MonitorInput();
Point DetectMousePosition(HANDLE hInput);
wchar_t DetectKeyboardInput(HANDLE hInput);
wchar_t simulated_getwch(wchar_t inputChar);