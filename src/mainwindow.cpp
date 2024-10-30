#include "../include/mainwindow.hpp"

MainWindow::MainWindow(const char *windowTitle,
                       size_t minimumWidth,
                       size_t minimumHeight,
                       QWidget *parent) : QWidget(parent)
{
    if (windowTitle)
    {
        this->setWindowTitle(windowTitle);
    }

    if (minimumHeight && minimumWidth)
    {
        this->setMinimumSize(minimumWidth, minimumHeight);
    }
    // layout = new QHBoxLayout(this);
    // layout->setContentsMargins(QMargins(0, 0, 0, 0));
    logwin = new LoginWindow(this);
    // layout->addWidget(logwin);

    // label = new QLabel(this);
    // setAttribute(Qt::WA_DeleteOnClose);
    this->setMinimumSize(minimumWidth, minimumHeight);
}
MainWindow::~MainWindow()
{
}

void MainWindow::login()
{
    // hide all widgets in main widnow;
    // QWidget* slider = new QWidget(this);
    // slider->resize(QSize(this->width()/2, this->height()/2));


}
