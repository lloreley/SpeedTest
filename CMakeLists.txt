cmake_minimum_required(VERSION 3.1.0)

project(SpeedTest VERSION 1.0.0 LANGUAGES CXX)

set(Qt5_DIR D:/tools/Qt/5.14.2/mingw73_64/lib/cmake/Qt5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(SpeedTest
    "main.cpp"
    "src/mainwindow.cpp"
    "include/mainwindow.hpp"
    "src/Logger.cpp"
    "src/String.cpp"
    "src/AnimatedTabBar/HAnimatedTabBar.cpp"
    "src/AnimatedTabBar/VAnimatedTabBar.cpp"
    "src/AnimatedTabBar/AnimatedTabBar.cpp"
    "include/AnimatedTabBar/AnimatedTabBar.hpp"
    "include/AnimatedTabBar/HAnimatedTabBar.hpp"
    "include/AnimatedTabBar/VAnimatedTabBar.hpp"
    "include/LoginWindow/LoginWindow.hpp"
    "include/LoginWindow/LoginWindow.cpp"
    
)

target_link_libraries(SpeedTest Qt5::Widgets)
