#include <Library/Filelib.h>
bool isFileEmpty(std::fstream& file) {
    // Di chuyển con trỏ đến cuối file
    file.seekg(0, std::ios::end);
    // Kiểm tra vị trí con trỏ, nếu là 0, file trống
    return file.tellg() == 0;
}

bool moveToEndOfLastLine(std::fstream &file) {
    // Di chuyển con trỏ đến cuối file
    file.seekg(0, std::ios::end);
    std::streamoff pos = file.tellg();

    // Biến để xác định có tìm thấy dòng không trống hay không
    bool found = false;
    char ch;
    // Duyệt ngược từ cuối file
    while (pos > 0) {
        pos--;
        file.seekg(pos, std::ios::beg);
        file.get(ch);
        if(ch != '\n') {
            break;
        }
    }
    while (pos > 0) 
    {   
        pos--;
        file.seekg(pos, std::ios::beg);
        file.get(ch);
        if(ch == '\n') 
        {
            found = true;
            break;
        }
    }
    
    return found;
}
