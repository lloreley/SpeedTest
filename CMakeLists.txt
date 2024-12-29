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
    src/AccountPage.cpp
    src/ButtonWithHover.cpp
    src/FileDataBase.cpp
    src/ScrollArea.cpp
    src/LoginPage.cpp
    src/LoginSliders.cpp
    src/NavigationPage.cpp
    src/Page.cpp
    src/TypingLessons.cpp
    src/TypingTest.cpp
    src/User.cpp
    src/WelcomePage.cpp
    src/mainwindow.cpp

    include/AccountPage.h
    include/ButtonWithHover.h
    include/CircularLinkedList.h
    include/Exception.h
    include/FileDataBase.h
    include/ScrollArea.h
    include/LoginPage.h
    include/LoginSliders.h
    include/mainwindow.h
    include/NavigationPage.h
    include/Page.h
    include/TypingTest.h
    include/TypingLessons.h
    include/User.h
    include/WelcomePage.h
)

target_link_libraries(SpeedTest Qt5::Widgets Qt5::Network)

