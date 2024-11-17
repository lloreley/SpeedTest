#ifndef DEFINES_HPP
#define DEFINES_HPP

// MainWindow

#define MIN_MAIN_WINDOW_HEIGHT                      600
#define MIN_MAIN_WINDOW_WIDHT                       800
#define MAIN_WINDOW_NAME                            "Typing speed test"//

// FileDataBase

#define USER_DATA_FOLDER_PATH                       "data/users"
#define DATA_FOLDER_PATH                            "data"
#define NAME_SELECTOR                               "name"
#define PASSWORD_SELECTOR                           "password"
#define EMAIL_SELECTOR                              "email"
#define ID_SELECTOR                                 "id"
#define USERS_COUNT_SELECETOR                       "users_count"

#define SERVER_PORT                                 8080

#define MESSAGE_TYPE_SELECTOR                       QString("message_type")
#define CHECK_CONNECTION_MESSAGE                    QString("check_connection")
#define CHECK_CREDENTIALS_MESSAGE_TYPE              QString("check_credentials")
#define ADD_USER_MESSAGE_TYPE                       QString("add_user")

#define LEFT_MESSAGE_BRACKET                        QString(": \"")
#define RIGHT_MESSAGE_BRACKET                       QString("\"\n")

// ServerClient

#define ACCESS_MESSAGE_TYPE                         QString("access: ")
#define ACCOUNT_MESSAGE_TYPE                        QString("account: ")
#define SERVER_IP                                   "127.0.0.1"
#define KEEP_ALIGN_TIME                             5000 // msec

#define ACCESS_USER_NOT_FOUND                       QString("\"user not found!\"")
#define ACCESS_PASSWORD_INCORRECT                   QString("\"password incorrect!\"")
#define ACCOUNT_CREATED                             QString("\"yes\"")
#define ACCOUNT_NOT_CREATED                         QString("\"no\"")

//                                                  PATHS
#define DYNAMIC_STYLES_FILE_PATH                    "styles/DynamicStyles.qss"
#define STATIC_STYLES_FILE_PATH                     "styles/StaticStyles.qss"
#define LOGO_PATH                                   "pictures/logo.png"

//                                                  PAGE    
#define ZERO_OPACITY                                0.0
#define MAX_OPACITY                                 1.0
#define PAGE_OPACITY_ANIMATION_DURATION             250

//                                                  BUTTON WITH HOVER
#define GOLD                                        QColor(255, 235, 167)
#define DARK_BLUE                                   QColor(16, 39, 112)
#define GRAY                                        QColor(109, 120, 135)
#define LIGHT_GRAY                                  QColor(203, 208, 223)
#define TRANSPARENT                                 QColor(255, 255, 255, 0)
#define SIGN_IN                                     "Sign In"
#define SIGN_UP                                     "Sign Up"

//                                                  LOGIN PAGE
#define LOGIN_PAGE_WIDTH                            800
#define LOGIN_PAGE_HEIGHT                           600
#define LOGIN_PAGE_SLIDER_WIDTH                     LOGIN_PAGE_WIDTH/2
#define LOGIN_PAGE_SLIDER_HEIGHT                    LOGIN_PAGE_HEIGHT
#define ZERO_CONTEXT_MARGINS                        QMargins(0, 0, 0, 0)
#define LOGIN_PAGE_MAIN_SLIDER_LAYOUT_SPACING       50
#define LOGIN_PAGE_LOGIN_SLIDER_LAYOUT_SPACING      5
#define LOGIN_PAGE_SLIDER_MOVE_DIRECTION_LEFT       "left"
#define LOGIN_PAGE_SLIDER_MOVE_DIRECTION_RIGHT      "right"

#define LOGIN_PAGE_SIGN_BUTTON_HOVER_DURATION       400
#define LOGIN_PAGE_MAIN_SLIDER_BORDER_RADIUS        150
#define LOGIN_PAGE_SLIDER_MOVE_DURATION             1200
#define LOGIN_PAGE_SLIDER_MOVE_EASIGN_CURVE         QEasingCurve::OutQuart
#define LOGIN_PAGE_SLIDER_BORDER_EASIGN_CURVE       QEasingCurve::OutQuad
#define LP_MS_BORDER_RADII_IN_RIGHT_POS             BorderRadii(LOGIN_PAGE_MAIN_SLIDER_BORDER_RADIUS, LOGIN_PAGE_MAIN_SLIDER_BORDER_RADIUS, 0, 0)
#define LP_MS_BORDER_RADII_IN_LEFT_POS              BorderRadii(0, 0, LOGIN_PAGE_MAIN_SLIDER_BORDER_RADIUS, LOGIN_PAGE_MAIN_SLIDER_BORDER_RADIUS)
#define QVARIAN_BORDER_RADII_IN_RIGHT_POS           QVariant::fromValue(LP_MS_BORDER_RADII_IN_RIGHT_POS)
#define QVARIAN_BORDER_RADII_IN_LEFT_POS            QVariant::fromValue(LP_MS_BORDER_RADII_IN_LEFT_POS)
#define LP_LS_TIME_WHEN_SWAP                        185
#define LOGIN_PAGE_SLIDER_LEFT_POS                  QPoint(0, 0)
#define LOGIN_PAGE_SLIDER_RIGHT_POS                 QPoint(LOGIN_PAGE_SLIDER_WIDTH, 0)
#define LP_LS_LOGO_SIZE                             QSize(100, 100)

#define LOGIN_PAGE_MAIN_SLIDER_OBJECT_NAME          "LoginPageMainSlider"
#define LP_MS_SIGN_BUTTON_OBJECT_NAME               "LoginPageMainSliderSignButton"
#define LP_MS_GREATING_LABEL_OBJECT_NAME            "LoginPageMainSliderGreatingLabel"
#define LP_MS_GREATING_LABEL_LEFT_POS_TEXT          "Welcome Back!"
#define LP_MS_GREATING_LABEL_RIGHT_POS_TEXT         "Hello, Friend!"
#define LP_MS_ADDITIONAL_LABEL_OBJECT_NAME          "LoginPageMainSliderAdditionalLabel"
#define LP_MS_ADDITIONAL_LABEL_LEFT_POS_TEXT        "Enter yor personal details to use all of application features"
#define LP_MS_ADDITIONAL_LABEL_RIGHT_POS_TEXT       "Register with your personal details to use all of application features"
#define LP_MS_GREATING_LABEL_IN_LAYOUT              qobject_cast<QLabel *>(this->layout()->itemAt(0)->widget())
#define LP_MS_ADDITIONAL_LABEL_IN_LAYOUT            qobject_cast<QLabel *>(this->layout()->itemAt(1)->widget())
#define LP_MS_SIGN_BUTTON_IN_LAYOUT                 qobject_cast<ButtonWithHover *>(this->layout()->itemAt(2)->widget())

#define LP_LS_MAIN_LABEL_OBJECT_NAME                "LoginPageLoginSliderMainLabel"
#define LP_LS_MAIN_LABEL_TEXT_IN_RIGHT_POS          "Create Account"
#define LP_LS_MAIN_LABEL_TEXT_IN_LEFT_POS           "Sign In"
#define LP_LS_SIGN_BUTTON_OBJECT_NAME               "LoginPageLoginSliderSignButton"
#define LP_LS_LINE_EDIT_PROPERTY                    "class", "loginLineEdit"
#define LP_LS_NAME_LINE_EDIT_PLACEHOLDER_TEXT       "Name"
#define LP_LS_EMAIL_LINE_EDIT_PLACEHOLDER_TEXT      "Email"
#define LP_LS_PASSWORD_LINE_EDIT_PLACEHOLDER_TEXT   "Password"
#define LP_LS_ERROR_LABEL_OBJECT_NAME               "LoginPageLoginSliderErrorLabel"
#define LP_LS_MAIN_LABEL_IN_LAYOUT                  qobject_cast<QLabel *>(this->layout()->itemAt(0)->widget())
#define LP_LS_ERROR_LABEL_IN_LAYOUT                 qobject_cast<QLabel *>(this->layout()->itemAt(2)->widget())
#define LP_LS_NAME_LINE_EDIT_IN_LAYOUT              qobject_cast<QLineEdit *>(this->layout()->itemAt(3)->widget())
#define LP_LS_EMAIL_LINE_EDIT_IN_LAYOUT             qobject_cast<QLineEdit *>(this->layout()->itemAt(4)->widget())
#define LP_LS_PASSWORD_LINE_EDIT_IN_LAYOUT          qobject_cast<QLineEdit *>(this->layout()->itemAt(5)->widget())
#define LP_LS_SIGN_BUTTON_IN_LAYOUT                 qobject_cast<ButtonWithHover *>(this->layout()->itemAt(6)->widget())

#define LP_LS_EL_EMTPY_FIELS_TEXT                   "Fill in all fiels"

//                                                  WELCOME PAGE       
#define WELCOME_PAGE_LAYOUT_SPACING                 30
#define WELCOME_PAGE_GREATING_LABEL_TEXT            "Welcome to Type.io!"
#define WELCOME_PAGE_ADDITIONAL_LABEL_TEXT          "Take a Typing Test, learn typing and improve\nyour Typing Skills"
#define WELCOME_PAGE_GREATING_OBJECT_NAME           "WelcomeGreatingLabel"
#define WELCOME_PAGE_ADDITIONAL_OBJECT_NAME         "WelcomeAdditionalLabel"
#define WELCOME_PAGE_RIGHT_BUTTON_OBJECT_NAME       "TypingLessons"
#define WELCOME_PAGE_RIGHT_BUTTON_TEXT              "Typing Lessons"
#define WELCOME_PAGE_LEFT_BUTTON_OBJECT_NAME        "StartTypingTest"
#define WELCOME_PAGE_LEFT_BUTTON_TEXT               "Start Typing Test"

#define WELCOME_PAGE_GREATING_LABEL_IN_LAYOUT       qobject_cast<QLabel *>(this->layout()->itemAt(0)->widget())
#define WELCOME_PAGE_ADDITIONAL_LABEL_IN_LAYOUT     qobject_cast<QLabel *>(this->layout()->itemAt(1)->widget())
#define WELCOME_PAGE_LEFT_BUTTON_IN_LAYOUT          qobject_cast<ButtonWithHover *>(layout()->itemAt(2)->layout()->itemAt(0)->widget())
#define WELCOME_PAGE_RIGHT_BUTTON_IN_LAYOUT         qobject_cast<ButtonWithHover *>(layout()->itemAt(2)->layout()->itemAt(1)->widget())



#endif