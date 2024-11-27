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

    include/Pages/LoginPage/LoginPage.hpp
    include/Pages/LoginPage/LoginSliders.hpp
    include/Pages/LoginPage/LoginSliders.cpp
    
    include/ButtonWithHover.hpp

    include/DataBase/FileDataBase.hpp
    include/DataBase/UserDataBase.hpp

    include/Pages/WelcomePage/WelcomePage.hpp
    include/Pages/TypingTest/TypingTest.hpp
    include/Pages/TypingLessons/TypingLessons.hpp
    include/Pages/NavigationPage/NavigationPage.hpp
    include/Pages/AccountPage/AccountPage.hpp
    include/Exception/Exception.hpp
    include/Pages/Page.hpp
    include/Pages/LessonsScrollArea.hpp


    include/Accounts/ServerClient.hpp
    include/Accounts/User.hpp
)

target_link_libraries(SpeedTest Qt5::Widgets Qt5::Network)

