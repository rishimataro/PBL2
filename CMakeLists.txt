cmake_minimum_required(VERSION 3.10)

project(PBL2_NTNT_HLP
)
# Xuất tệp lệnh biên dịch
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Thiết lập tiêu chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_subdirectory(src)
# add_subdirectory(include)

add_subdirectory(ftxui)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ftxui/cmake" ${CMAKE_MODULE_PATH})
# Tạo executable từ tệp nguồn
add_executable(main main.cpp)

# target_link_libraries(
#   PRIVATE ftxui::screen
#   PRIVATE ftxui::dom
#   PRIVATE ftxui::component # Not needed for this example.
# )
add_library(header_lib INTERFACE)
target_include_directories(header_lib 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/Header
)
# add_library(header_lib
#     include/Library/Header.h    
# )
add_library(lib
    include/Library/Filelib.h
    include/Library/Graphics.h
    include/Library/Mouse.hpp
    src/Library/Filelib.cpp
    src/Library/Graphics.cpp
    src/Library/Mouse.cpp
)
target_include_directories(lib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_library(manag
    include/Management/Account.h
    include/Management/Appoinment.h
    include/Management/Date.h
    include/Management/listAccount.h
    include/Management/Patient.h
    src/Management/Account.cpp
    src/Management/Appoinment.cpp
    src/Management/Date.cpp
    src/Management/listAccount.cpp
    src/Management/Patient.cpp
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
    src/Interface/Patient_interface.cpp
)
target_include_directories(ui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(lib
    # PUBLIC stdc++fs
    PUBLIC header_lib)
target_link_libraries(manag
    # PRIVATE header_lib
    PRIVATE lib
    PRIVATE template
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
target_link_libraries(ui
    # PRIVATE header_lib    
    PRIVATE lib
    PRIVATE template
    PRIVATE manag
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)  
target_link_libraries(main
    # PRIVATE header_lib
    PRIVATE lib
    PRIVATE manag
    PRIVATE template
    PRIVATE ui
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
 
