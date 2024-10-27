#include <windows.h>
struct Point {
    int x;
    int y;
};

// Hàm detect và trả về tọa độ khi có click chuột trái
Point DetectLeftMouseClick();