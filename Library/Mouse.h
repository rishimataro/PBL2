#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
struct Point {
    int X;
    int Y;
};

// Hàm detect và trả về tọa độ khi có click chuột trái
Point DetectLeftMouseClick();

#endif