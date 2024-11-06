cmake_minimum_required(VERSION 3.10)

project(PBL2_NTNT_HLP
)
# Xuất tệp lệnh biên dịch
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Thiết lập tiêu chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(ftxui)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ftxui/cmake" ${CMAKE_MODULE_PATH})
# Tạo executable từ tệp nguồn
add_executable(main main.cpp)

add_library(header_lib INTERFACE)
target_include_directories(header_lib 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/Header
)

# Thêm file thư viện lib
add_library(lib
    include/Library/Filelib.hpp
    include/Library/Graphics.hpp
    include/Library/Mouse.hpp
    src/Library/Filelib.cpp
    src/Library/Graphics.cpp
    src/Library/Mouse.cpp

)
target_include_directories(lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Thêm file thư viện management
add_library(manag
    include/Management/Account.hpp
    include/Management/Appoinment.hpp
    include/Management/Date.hpp
    # include/Management/listAccount.hpp
    # include/Management/listMedicalRecord.hpp
    include/Management/listPatient.hpp
    include/Management/Patient.hpp
    src/Management/Account.cpp
    src/Management/Appoinment.cpp
    src/Management/Date.cpp
    src/Management/listAccount.cpp
    # src/Management/listMedicalRecord.cpp
    src/Management/Patient.cpp
    src/Management/listPatient.cpp
)
target_include_directories(manag 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_library(template
    include/Template/LinkedList.hpp
    src/Template/LinkedList.cpp
)
target_include_directories(template 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_library(ui
    include/Interface/Patient_interface.hpp
    include/Interface/Login.hpp
    src/Interface/Patient_interface.cpp
    src/Interface/Login.cpp
)
target_include_directories(ui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(lib
    PUBLIC header_lib)


target_link_libraries(manag
    # PRIVATE header_lib
    PUBLIC lib
    PUBLIC template
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
target_link_libraries(ui
    # PRIVATE header_lib    
    # PRIVATE lib
    # PRIVATE template
    PUBLIC manag
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
) 
target_link_libraries(main
    # PRIVATE header_lib
    # PRIVATE lib
    # PRIVATE manag
    # PRIVATE template
    PRIVATE ui
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
