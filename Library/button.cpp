#include "Header.h"
#include "Graphics.h"

// Cấu trúc chứa tọa độ x và y
struct Point {
    int x;
    int y;
};

// Hàm detect và trả về tọa độ khi có click chuột
Point DetectMouseClick() {
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

class button
{   
    private:
    string text;
    string bgColor;
    string textColor;
    string borderColor;
    int x, y, width, height;
    // bool isClickedInside(int x, int y);
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

button::button(string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height)
    :text(text), bgColor(bgColor), textColor(textColor), borderColor(borderColor), x(x), y(y), width(width), height(height) 
{
    
}

void button::set(string text, string bgColor, string textColor, string borderColor, int x, int y, int width, int height)
{
    this->text = text;
    this->bgColor = bgColor;
    this->textColor = textColor;
    this->borderColor = borderColor;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
void button::draw()
{
    printBox(this->x, this->y, this->width, this->height, this->text, this->bgColor, this->borderColor, this->textColor);
}
void button::changeColor(string newColor)
{
    this->bgColor = newColor;
    // draw();
}

void button::changeText(string newText)
{
    this->text = newText;
    // draw();
}
void button::changeBorderColor(string newColor)
{
    this->borderColor = newColor;
    // draw();
}

void button::move(int dx, int dy)
{
    this->x += dx;
    this->y += dy;
    // draw();
}

bool button::isClicked(int x, int y)
{
    return (x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height);
}

void button::setPosition(int x, int y)
 {
    this->x = x;
    this->y = y;
    // draw();
}

void button::reSize(int newWidth, int newHeight)
{
    this->width = newWidth;
    this->height = newHeight;
    // draw();
}
button::~button()
{

}

int main()
{
    button btn1;
    btn1.changeText("Button 1");
    btn1.reSize(10, 3);
    btn1.draw();
    button btn2;
    btn2.changeText("Button 2");
    btn2.setPosition(20, 0);
    btn2.reSize(10, 3);
    btn2.draw();
    string t = "Axes represent a continuous range of style variations. One variable font can contain multiple axes. You can customize an axis to any number within its minimum or maximum range.";
    // printBox(5, 1, 49, 20, t, "E2F1E7", "629584", "629584");
    int x, y;
    Point point;
    while (true)
    {
        point = DetectMouseClick();
        x = point.x;
        y = point.y;
        if (btn1.isClicked(x, y))
        {
            btn1.changeColor("629584");
        }
        else
        {
            btn1.changeColor("E2F1E7");
        }
        if (btn2.isClicked(x, y))
        {
            btn2.changeColor("629584");
        }
        else
        {
            btn2.changeColor("E2F1E7");
        }
        btn1.draw();
        btn2.draw();
    }
    return 0;
    system("pause");
}