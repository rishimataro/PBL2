#include "TextBox.hpp"
#include "mouse.hpp"
// Hàm kiểm tra ký tự hợp lệ
std::string WStringToUTF8(const std::wstring& wide_string) {
    if (wide_string.empty()) return std::string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string[0], 
                                          (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
    std::string utf8_string(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wide_string[0], (int)wide_string.size(), 
                        &utf8_string[0], size_needed, nullptr, nullptr);

    return utf8_string;
}
std::wstring UTF8ToWString(const std::string& utf8_string) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8_string);
}
void print_wstring(const std::wstring& wstr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hConsole, wstr.c_str(), wstr.size(), &written, nullptr);
}
void setupUtf16Console() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdin), _O_U16TEXT);   // Đầu vào
    _setmode(_fileno(stdout), _O_U16TEXT);  // Đầu ra
}
std::optional<wchar_t> getUnicodeCharIfPressed() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE) {
        std::cerr << "Lỗi lấy handle input" << std::endl;
        return std::nullopt;
    }

    DWORD numEvents = 0;
    if (!GetNumberOfConsoleInputEvents(hIn, &numEvents)) {
        std::cerr << "Lỗi lấy số lượng sự kiện input" << std::endl;
        return std::nullopt;
    }

    if (numEvents > 0) {
        INPUT_RECORD inputRecord;
        DWORD numRead;
        if (ReadConsoleInput(hIn, &inputRecord, 1, &numRead) &&
            inputRecord.EventType == KEY_EVENT &&
            inputRecord.Event.KeyEvent.bKeyDown) {
            return inputRecord.Event.KeyEvent.uChar.UnicodeChar;
        }
    }

    return std::nullopt;
}
textBox::textBox(int x, int y, int width, std::string label, std::string labelColor, std::string backgroundColor, std::string borderColor)
    : x(x), y(y), width(width), label(label), labelColor(labelColor), backgroundColor(backgroundColor), borderColor(borderColor)
{
    this->lengthLimit = width - 2;
    this->spaceAccepted = true;
    this->textColor = labelColor;
}

void textBox::show() const
{   
    if(content.empty())
        box(x, y, width, 2, label, backgroundColor, borderColor, labelColor);
    else
    {
        box(x, y, width, 2, content, backgroundColor, borderColor, textColor);
    }
}
void textBox::showLabel() const
{
    int _x = x + 1;
    int _y = y + 1;
    gotoXY(_x, _y);
    cout << setTextColor(labelColor);
    cout << setBackgroundColor(backgroundColor);
    cout << label;
    for (int i = label.length(); i < lengthLimit; i++)
    {
        cout << " ";
    }

    ShowCur(false);
    cout << resetColor();
    
}
void textBox::showContent() const
{
    int _x = x + 1;
    int _y = y + 1;
    gotoXY(_x, _y);
    cout << setTextColor(textColor);
    cout << setBackgroundColor(backgroundColor);
    cout << content;
    for (int i = content.length(); i < lengthLimit; i++)
    {
        cout << " ";
    }
    gotoXY(_x + content.length(), _y);
    ShowCur(true);
    cout << resetColor();
}
bool textBox::isClicked(int x, int y)
{
    return (x >= this->x && x <= this->x + this->width + 1 && y >= this->y && y <= this->y + 2);
}
bool textBox::isClickedInside(int x, int y)
{
    return (x >= this->x + 1 && x <= this->x + this->width - 2 && y == this->y + 1); 
}
// void textBox::input()
// {   
//     SetConsoleOutputCP(CP_UTF8);
//     SetConsoleCP(CP_UTF8);
//     int _x = x + 1;
//     int _y = y + 1;
//     setCursorPosition(content, x, y);
//     wchar_t ch;
//     show();
//     wstring input = UTF8ToWString(content);
//     int cursorPos = input.length();
//     InputEvent event;
//     gotoXY(_x, _y);
//     cout << setTextColor(textColor);
//     cout << setBackgroundColor(backgroundColor);
//     for (int i = 0; i < lengthLimit; i++)
//     {
//         cout << " ";
//     }
//     gotoXY(_x + content.length(), _y);
//     while(true)
//     {   
//         gotoXY(_x + cursorPos, _y);
        
//         if(auto unicodeChar = getUnicodeCharIfPressed())
//         {   
//             ch = *unicodeChar;
//             if (ch == L'\r') {  // Nhấn Enter để kết thúc chỉnh sửa
//                 break;
//             } else if (ch == 224 || ch == 0) {  // Bắt phím mũi tên
//                 // ch = inputRecord.Event.KeyEvent.bKeyDown;
//                 if (ch == 75 && cursorPos > 0) {  // Mũi tên trái
//                     cursorPos--;
//                     gotoXY(_x + cursorPos, _y);
//                 } else if (ch == 77 && cursorPos < input.length()) {  // Mũi tên phải
//                     cursorPos++;
//                     gotoXY(_x + cursorPos, _y);
//                 }
//             } else if (ch == L'\b' && cursorPos > 0) {  // Backspace
//                 input.erase(cursorPos - 1, 1);
//                 cursorPos--;
//                 gotoXY(_x, _y);
//                 // std::wcerr << input << L" ";  // Xóa ký tự cuối
//                 print_wstring(input);
//                 gotoXY(_x + cursorPos, _y);
//             } else if (ch >= 32 && input.length() < lengthLimit) {  // Các ký tự in được
//                 input.insert(cursorPos, 1, ch);
//                 cursorPos++;
//                 gotoXY(_x, _y);
//                 // std::wcerr << input << L" ";  // Cập nhật chuỗi Unicode
//                 print_wstring(input);
//                 gotoXY(_x + cursorPos, _y);
//             }
//         }else
//         {
//             ch = _getwch();
//             if (ch == L'\r') {  // Nhấn Enter để kết thúc chỉnh sửa
//                 break;
//             } else if (ch == 224 || ch == 0) {  // Bắt phím mũi tên
//                 // ch = _getwch();
//                 if (ch == 75 && cursorPos > 0) {  // Mũi tên trái
//                     cursorPos--;
//                     gotoXY(_x + cursorPos, _y);
//                 } else if (ch == 77 && cursorPos < input.length()) {  // Mũi tên phải
//                     cursorPos++;
//                     gotoXY(_x + cursorPos, _y);
//                 }
//             } else if (ch == L'\b' && cursorPos > 0) {  // Backspace
//                 input.erase(cursorPos - 1, 1);
//                 cursorPos--;
//                 gotoXY(_x, _y);
//                 // std::wcerr << input << L" ";  // Xóa ký tự cuối
//                 print_wstring(input);
//                 gotoXY(_x + cursorPos, _y);
//             } else if (ch >= 32 && input.length() < lengthLimit) {  // Các ký tự in được
//                 input.insert(cursorPos, 1, ch);
//                 cursorPos++;
//                 gotoXY(_x, _y);
//                 // std::wcerr << input << L" ";  // Cập nhật chuỗi Unicode
//                 print_wstring(input);
//                 gotoXY(_x + cursorPos, _y);
//             }
//         }
        


//         if (inputRecord.EventType == MOUSE_EVENT)
//         {   
//             MOUSE_EVENT_RECORD mer = inputRecord.Event.MouseEvent;
//             if (mer.dwEventFlags == 0 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) 
//             {
//                 clickPosition = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
//                 if(isClicked(clickPosition.x, clickPosition.y))
//                 {   
//                     if(isClickedInside(clickPosition.x, clickPosition.y))
//                     {   
//                         if(clickPosition.x >= _x && clickPosition.x <= _x + input.length())
//                         {
//                             cursorPos = clickPosition.x - _x;
//                             gotoXY(clickPosition.x, clickPosition.y);
//                         }
//                         else
//                         {
//                             cursorPos = input.length();
//                             setCursorPosition(input, x, y);
//                         }
                        
//                     }
//                     else
//                     {
//                         cursorPos = input.length();
//                         setCursorPosition(input, x, y);
//                     }
//                 }
//                 // else
//                 // {
//                 //     break;
//                 // }
//             }
//         }
//     }   
//     SetConsoleMode(hInput, prev_mode);
//     content = WStringToUTF8(input);
// }

void textBox::input()
{   
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT);

    int _x = x + 1;
    int _y = y + 1;
    setCursorPosition(content, x, y);
    wchar_t ch;
    show();
    wstring input = UTF8ToWString(content);
    int cursorPos = input.length();
    InputEvent event;
    gotoXY(_x, _y);
    cout << setTextColor(textColor);
    cout << setBackgroundColor(backgroundColor);
    for (int i = 0; i < lengthLimit; i++)
    {
        cout << " ";
    }
    gotoXY(_x + content.length(), _y);
    // GetAsyncKeyState(VK_LBUTTON);
    DWORD events;
    INPUT_RECORD inputRecord;
    Point clickPosition;
    while(true)
    {   
        gotoXY(_x + cursorPos, _y);
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if(inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
        {   
            // ch = inputRecord.Event.KeyEvent.uChar.UnicodeChar;  // Đọc ký tự Unicode
            // ch = inputRecord.Event.KeyEvent.wVirtualKeyCode;
            // wchar_t chx = inputRecord.Event.KeyEvent.uChar.AsciiChar;
            // kbhit();
            ch = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
            if (ch == L'\r') {  // Nhấn Enter để kết thúc chỉnh sửa
                break;
            } else if (ch == 224 || ch == 0) {  // Bắt phím mũi tên
                ch = inputRecord.Event.KeyEvent.bKeyDown;
                if (ch == 75 && cursorPos > 0) {  // Mũi tên trái
                    cursorPos--;
                    gotoXY(_x + cursorPos, _y);
                } else if (ch == 77 && cursorPos < input.length()) {  // Mũi tên phải
                    cursorPos++;
                    gotoXY(_x + cursorPos, _y);
                }
            } else if (ch == L'\b' && cursorPos > 0) {  // Backspace
                input.erase(cursorPos - 1, 1);
                cursorPos--;
                gotoXY(_x, _y);
                // std::wcerr << input << L" ";  // Xóa ký tự cuối
                print_wstring(input + L" ");  // Cập nhật chu��i Unicode
                gotoXY(_x + cursorPos, _y);
            } else if (ch >= 32 && input.length() < lengthLimit) {  // Các ký tự in được
                input.insert(cursorPos, 1, ch);
                cursorPos++;
                gotoXY(_x, _y);
                // std::wcerr << input << L" ";  // Cập nhật chuỗi Unicode
                print_wstring(input + L" ");  // Cập nhật chu��i Unicode
                gotoXY(_x + cursorPos, _y);
            }
        }


        if (inputRecord.EventType == MOUSE_EVENT)
        {   
            MOUSE_EVENT_RECORD mer = inputRecord.Event.MouseEvent;
            if (mer.dwEventFlags == 0 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) 
            {
                clickPosition = { mer.dwMousePosition.X, mer.dwMousePosition.Y };
                if(isClicked(clickPosition.x, clickPosition.y))
                {   
                    if(isClickedInside(clickPosition.x, clickPosition.y))
                    {   
                        if(clickPosition.x >= _x && clickPosition.x <= _x + input.length())
                        {
                            cursorPos = clickPosition.x - _x;
                            gotoXY(clickPosition.x, clickPosition.y);
                        }
                        else
                        {
                            cursorPos = input.length();
                            setCursorPosition(input, x, y);
                        }
                        
                    }
                    else
                    {
                        cursorPos = input.length();
                        setCursorPosition(input, x, y);
                    }
                }
                // else
                // {
                //     break;
                // }
            }
        }
    }   
    SetConsoleMode(hInput, prev_mode);
    content = WStringToUTF8(input);
}//10/30/-22:09

// void textBox::input() {
//         SetConsoleOutputCP(CP_UTF8);
//         SetConsoleCP(CP_UTF8);

//         show(); // Hiện box ngay lập tức

//         InputEvent event;
//         bool inputMode = false; 
//         string tempContent; 

//         while (true) {
//             event = MonitorInput();

//             if (event.type == InputEventType::MouseLeftClick) {
//                 if (isClicked(event.position.X, event.position.Y)) {
//                     inputMode = true; 
//                     tempContent.clear(); 
//                     gotoXY(event.position.X, event.position.Y);
//                     show(); 
//                 } else {
//                     inputMode = false;
//                     if (content.empty()) {
//                         showLabel(); 
//                     } else {
//                         showContent(); 
//                     }
//                     continue; 
//                 }
//             }

//             if (inputMode && event.type == InputEventType::KeyPress) {
//                 if (event.key == VK_RETURN || event.key == VK_ESCAPE) {
//                     inputMode = false; 
//                     content = tempContent; 
//                     if (content.empty()) {
//                         showLabel(); 
//                     } else {
//                         showContent(); 
//                     }
//                     break; 
//                 } 
//                 else if (event.key == '\b') {
//                     if (!tempContent.empty()) {
//                         tempContent.pop_back(); 
//                         showContent(); 
//                     }
//                 } 
//                 else if (isValidCharacter(event.key)) {
//                     tempContent += event.key; 
//                     showContent(); 
//                 }
//             }
//         }

//         show(); 
//         showContent(); 
//     }

void setCursorPosition(string& str, int x, int y)
{
    int _x;
    int _y = y + 1;
    _x = x + str.length() + 1;
    gotoXY(_x, _y);
}
void setCursorPosition(wstring& str, int x, int y)
{
    int _x = x + 1;
    int _y = y + 1;
    _x = x + str.length() + 1;
    gotoXY(_x, _y);
}
string textBox::getContent() const
{
    return content;
}
int textBox::currentCharacter() const
{
    int _x = whereX();
    return _x - (this->x + 1);
}
void textBox::setSpaceAccepted(bool newSpaceAccepted)
{
    this->spaceAccepted = newSpaceAccepted;
}
bool textBox::isValidCharacter(char key) const {
        // Kiểm tra ký tự hợp lệ: ký tự nhìn thấy ASCII và UTF-8
        return (isprint(key) || isUtf8Character(key)); // Có thể mở rộng thêm cho UTF-8
    }

bool textBox::isUtf8Character(char key) const {
        // Kiểm tra xem ký tự có phải là UTF-8 hay không (dễ dàng mở rộng nếu cần)
        return (static_cast<unsigned char>(key) >= 128); 
    }
textBox::~textBox()
{}
int main ()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    textBox tb(1, 1, 30, "user name", "FFFFFF", "000000", "FFFFFF");
    tb.input();
    system("pause");
}