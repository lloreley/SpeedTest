#include "../include/mainwindow.hpp"

MainWindow::MainWindow(const char *windowTitle,
                       size_t minimumWidth,
                       size_t minimumHeight,
                       QWidget *parent) : QWidget(parent)
{
    // Logger::getInstance()("LOG::WINDOW::CONSTRUCTOR -> start work\n");
    if (windowTitle)
    {
        this->setWindowTitle(windowTitle);
        // Logger::getInstance()("LOG::WINDOW::CONSTRUCTOR::PROCESS::SETTING::WINDOW_TITLE -> successful\n");
    }

    if (minimumHeight && minimumWidth)
    {
        this->setMinimumSize(minimumWidth, minimumHeight);
        // Logger::getInstance()("LOG::WINDOW::CONSTRUCTOR::PROCESS::SETTING::MINIMUM_WINDOW_SIZE -> successful\n");
    }


    label = new QLabel(this);
    setAttribute(Qt::WA_DeleteOnClose);
    // Logger::getInstance()("LOG::WINDOW::CONSTRUCTOR::ATTRIBUTE::SETTING::DELETE_ON_CLOSE -> successful\n");
    this->setMinimumSize(minimumWidth, minimumHeight);

    // Logger::getInstance( )("LOG::WINDOW::CONSTRUCTOR -> end work\n");
}
MainWindow::~MainWindow()
{
    // Logger::getInstance()("LOG::WINDOW:::DESTRUCTOR -> start work\n");
    // Logger::getInstance()("LOG::WINDOW::DESTRUCTOR -> end work\n");
}
