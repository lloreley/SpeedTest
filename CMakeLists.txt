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

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(SpeedTest
    main.cpp

    include/mainwindow.hpp
    src/mainwindow.cpp

    include/FileLoader/FileLoader.hpp
    include/LoginWindow/LoginWindow.hpp
    include/LoginWindow/LoginWindow.cpp
    include/LoginWindow/LoginSliders.hpp
    include/LoginWindow/LoginSliders.cpp
    include/LoginWindow/SignButton.hpp
    include/FileDataBase.hpp


    include/ServerClient.hpp
    include/User.hpp
)

target_link_libraries(SpeedTest Qt5::Widgets Qt5::Network)

