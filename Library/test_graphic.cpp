#include <iostream>
#include <string>
// #include <windows.h>

std::string hexToRgb(std::string hex) {
    int r, g, b;
    if((hex[0] == '#' && hex.length() == 7))
    {
        hex.erase(0, 1);
    }else if(hex.length() != 6)
    return "0;0;0";
    r = std::stoi(hex.substr(0, 2), nullptr, 16); // Giá trị đỏ
    g = std::stoi(hex.substr(2, 2), nullptr, 16); // Giá trị xanh lá
    b = std::stoi(hex.substr(4, 2), nullptr, 16); // Giá trị xanh dương
    return std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b);
}

std::string setTextColor(const std::string& hexColor) {
    return "\x1b[38;2;" + hexToRgb(hexColor) + "m";
}
std::string setTextColor(const int red, const int green, const int blue) {
    return "\x1b[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string setBackgroundColor(const std::string& hexColor) {
    return "\x1b[48;2;" + hexToRgb(hexColor) + "m";
}
std::string setBackgroundColor(const int red, const int green, const int blue) {
    return "\x1b[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";
}
std::string resetColor() {
    return "\x1b[0m";
}
std::string setBold() {
    return "\x1b[1m";
}
std::string setUnderline() {
    return "\x1b[4m";
}
std::string setItalic() {
    return "\x1b[3m";
}
int main() {
    // // Lấy handle của console
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // // Thiết lập màu chữ thành xanh lá cây
    // SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    // std::cout << "Text with green foreground.\n";

    // // Thiết lập màu chữ thành đỏ và nền thành trắng sáng
    // SetConsoleTextAttribute(hConsole, FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    // std::cout << "Text with red foreground and bright white background.\n";

    // SetConsoleTextAttribute(hConsole, 255);
    // std::cout << "Text with custom color.\n";  
    // // Đặt lại màu sắc về mặc định (trắng sáng trên nền đen)
    // SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // std::cout << "Text with default color.\n";

    // std::cout << setTextColor(77, 166, 58) << "\x1b[3m"  << "\x1b[4m" << "\x1b[1m" << "Hello, World!" <<"\x1b[0m\n";
    std::cout << setTextColor("#E947B3") << setBackgroundColor("#58BED4") << setBold() << "Hello" << resetColor();
    // std::cout << hexToRgb("4DA63A");

    // std::cout << "\x1b[1mThis is bold text!\x1b[0m\n";
    
    // In chữ bình thường
    std::cout << "This is normal text.\n";
    system("pause"); // Dừng chương trình để xem kết quả
    return 0;
}
