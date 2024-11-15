#ifndef DEFINES_HPP
#define DEFINES_HPP


//MainWindow


#define MIN_HEIGHT 600
#define MIN_WIDHT 800
#define MAIN_WINDOW_NAME "Typing speed test"

// FileDataBase

#define USER_DATA_FOLDER_PATH "data/users"
#define DATA_FOLDER_PATH "data"
#define NAME_SELECTOR "name"
#define PASSWORD_SELECTOR "password"
#define EMAIL_SELECTOR "email"
#define ID_SELECTOR "id"
#define USERS_COUNT_SELECETOR "users_count"

// #define KEEP_ALIGN_TIME 3000 // msec

#define SERVER_PORT 8080

#define MESSAGE_TYPE_SELECTOR "message_type"
#define CHECK_CONNECTION_MESSAGE "check_connection"
#define CHECK_CREDENTIALS_MESSAGE_TYPE "check_credentials"
#define ADD_USER_MESSAGE_TYPE "add_user"

// ServerClient

#define ACCESS_MESSAGE_TYPE "access" 
#define ACCOUNT_CREATED_MESSAGE_TYPE "account" 
#define CHECK_CREDENTIALS_MESSAGE_TYPE "check_credentials"
#define ADD_USER_MESSAGE_TYPE "add_user"
#define SERVER_IP "127.0.0.1"
#define KEEP_ALIGN_TIME 5000 // msec

// SignButton

#define STYLES_FILE_NAME "styles/Styles.qss"
#define SIGN_IN "Sign In"
#define SIGN_UP "Sign Up"
#define TRANSPARENT QColor(255, 255, 255, 0)
#define PURPLE QColor(81, 45, 168)
#define WHITE QColor(255, 255, 255)
#define WHITE_VISIBLE_BACKGROUND QColor(255, 255, 255, 255)
#define SIGN_BUTTON_HOVER_DURATION 400

// LoginWindow
#define MIN_LOGIN_WINDOW_WIDTH 800
#define MIN_LOGIN_WINDOW_HEIGHT 600

// LoginSliders
#define MIN_SLIDER_HEIGHT 600
#define MIN_SLIDER_WIDTH 400
#define ZERO_CONTEXT_MARGINS QMargins(0, 0, 0, 0)
#define SLIDER_BORDER_RADIUS 150
#define SLIDER_LEFT_POS QPoint(0, 0)
#define SLIDER_RIGHT_POS QPoint(MIN_SLIDER_WIDTH, 0)
#define SLIDER_DURATION 1000
#define SLIDER_EASING_CURVE QEasingCurve::OutQuart
#define GREETIN_LABEL_TEXT_BACK "Welcome Back!"
#define GREETIN_LABEL_TEXT_HELLO "Hello, Friend!"
#define ADDITIONAL_LABEL_TEXT_BACK "Enter yor personal details to use all of application features"
#define ADDITIONAL_LABEL_TEXT_HELLO "Register with your personal details to use all of application features"
#define LAYOUT_SPACING 50
#define LEFT_POS_BORDER_RADII BorderRadii(0, 0, SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS)
#define RIGHT_POS_BORDER_RADII BorderRadii(SLIDER_BORDER_RADIUS, SLIDER_BORDER_RADIUS, 0, 0)
#define MAIN_LABEL_LOGIN_TAB_TEXT_BACK "Sign In"
#define MAIN_LABEL_LOGIN_TAB_TEXT_HELLO "Create Account"
#define NAME_PLACEHOLDER_TEXT "Name"
#define EMAIL_PLACEHOLDER_TEXT "Email"
#define PASSWORD_PLACEHOLDER_TEXT "Password"
#define LOGIN_TAB_LAYOUT_SPACING 5
#define LOGO_PATH "pictures/logo.png"

#endif