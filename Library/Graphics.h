#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#define KEY_NONE -1
using namespace std;

int whereX(); // Lấy tọa độ x của con trỏ hiện tại
int whereY(); // Lấy tọa độ y của con trỏ hiện tại
int getCurrentCursorPositionY(); // Lấy vị trí dòng hiện tại của con trỏ màn hình trong Console

void gotoXY(int x, int y); // Dịch con trỏ hiện tại đến điểm có tọa độ (x, y)
void SetColor(WORD color); // Đặt màu cho chữ
void ShowCur(bool CursorVisibility); // Làm ẩn/hiện trỏ chuột
int inputKey(); // Trả về mã phím người dùng bấm
void textcolor(int color); // Đặt màu cho chuỗi

vector<string> splitTextIntoLines(const string& text, int boxWidth); // Tách chuỗi thành các dòng phù hợp với chiều rộng box

void emptyBox2(int x, int y, int boxWidth, int boxHeight, string backgroundColor, string borderColor); // Vẽ box mà không có nội dung (loại thứ nhất)
void emptyBox2_(int x, int y, int boxWidth, int boxHeight, string backgroundColor, string borderColor); // Vẽ box mà không có nội dung (loại thứ hai)
void emptyBox(int x, int y, int w, int h, int t_color, int b_color); // Vẽ box mà không có nội dung (kiểu 1 với màu số nguyên)
void emptyBox_(int x, int y, int w, int h, int t_color, int b_color); // Vẽ box mà không có nội dung (kiểu 2 với màu số nguyên)

void printBox(int x, int y, int boxWidth, int boxHeight, string text, string backgroundColor, string borderColor, string textColor); // Vẽ box có nội dung
void box(int x, int y, int boxWidth, int boxHeight, string content, string backgroundColor, string borderColor, string textColor); // Vẽ box có nội dung (kiểu 1)
void box_(int x, int y, int boxWidth, int boxHeight, string content, string backgroundColor, string borderColor, string textColor); // Vẽ box có nội dung (kiểu 2)

int move(int x, int y, int h, int &yp, int &kt, int soKhung); // Di chuyển đối tượng và trả về vị trí mới khi nhấn Enter

string hexToRgb(string hex);
string setTextColor(const string& hexColor);
string setTextColor(const int red, const int green, const int blue);

string setBackgroundColor(const string& hexColor);
string setBackgroundColor(const int red, const int green, const int blue);

string resetColor();
string setBold();
string setUnderline();
string setItalic();

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

#endif