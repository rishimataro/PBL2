#pragma once
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <vector>
#include "windows.h" 
#include "Mouse.h"
#define KEY_NONE	-1
using namespace std;

string hexToRgb(string);
// Thiết lập màu text
string setTextColor(const string&);
// Thiết lập màu text
string setTextColor(const int, const int, const int);
// Thiết lập màu background
string setBackgroundColor(const string&);
// Thiết lập màu background
string setBackgroundColor(const int, const int, const int);
// Xóa hết toàn bộ thuộc tính text và background
string resetAll();
// Thiết lập chữ đậm
string setBold();
// Thiết lập chữ gạch dưới
string setUnderline();
// Thiết lập chữ nghiêng
string setItalic();
string hexToRgb(string);
// Thiết lập màu text
string setTextColor(const string&);
// Thiết lập màu text
string setTextColor(const int, const int, const int);
// Thiết lập màu background
string setBackgroundColor(const string&);
// Thiết lập màu background
string setBackgroundColor(const int, const int, const int);
// Xóa hết toàn bộ thuộc tính text và background
string resetAll();
// Thiết lập chữ đậm
string setBold();
// Thiết lập chữ gạch dưới
string setUnderline();
// Thiết lập chữ nghiêng
string setItalic();
//* Hàm lấy tọa độ x của con trỏ hiện tại
int whereX();

//* Hàm lấy tọa độ y của con trỏ hiện tại
int whereY();

//* Hàm lấy vị trí dòng hiện tại của con trỏ màn hình trong Console
int getCurrentCursorPositionY();

//* Hàm dịch con trỏ hiện tại đến điểm có tọa độ (x, y)
void gotoXY(int x, int y);

//* Hàm đặt màu cho chữ
void SetColor(WORD color);

//* Hàm làm ẩn trỏ chuột
void ShowCur(bool CursorVisibility);

//* Hàm trả về mã phím người dùng bấm
int inputKey();

//* Hàm đặt màu cho chuỗi
void textcolor(int x);

vector<string> splitTextIntoLines(const string& text, int boxWidth);
//* Hàm vẽ box mà không có nội dung
void emptyBox2(int row, int col, int width, int height, string backgroundColor, string borderColor);

void emptyBox(int x, int y, int w, int h, int t_color, int b_color);  // 1 gạch
void emptyBox_(int x, int y, int w, int h, int t_color, int b_color); // 2 gạch
void emptyBox2_(int row, int col, int width, int height, string backgroundColor, string borderColor);

//* Hàm vẽ box có nội dung
void box(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content);  // 1 gạch
void printBox(int row, int col, int boxWidth, int boxHeight, string content, string backgroundColor, string borderColor, string textColor);
void printBox_(int row, int col, int boxWidth, int boxHeight, string content, string backgroundColor, string borderColor, string textColor);
void box_(int x, int y, int w, int h, int t_color, int b_color, int content_color, string content); // 2 gạch

//* Hàm di chuyển đối tượng và trả về vị trí mới khi phím Enter được nhấn
int move(int x, int y, int h, int &yp, int &kt, int soKhung);

void SetConsoleSize(int width, int height);

void SetConsoleSizeAndDisableResize(int width, int height);


class button
{   
    private:
    string text;
    string bgColor;
    string textColor;
    string borderColor;
    int x, y, width, height;
    public:
    button(string text = "Button", string bgColor = "E2F1E7", string textColor = "243642", string borderColor = "243642", int x = 0, int y = 0, int width = 8, int height = 3);
    void set(string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height);
    void draw();
    void handleClick(int x, int y);
    void changeColor(string newColor);
    void changeText(string newText);
    void changeBorderColor(string newColor);
    void move(int dx, int dy);
    bool isClicked(int x, int y);
    void setPosition(int x, int y);
    void reSize(int newWidth, int newHeight);
    ~button();
};

