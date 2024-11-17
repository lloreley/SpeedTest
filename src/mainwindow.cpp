#include "../include/mainwindow.hpp"

#include <QGraphicsBlurEffect>
MainWindow::MainWindow(const char *windowTitle,
                       size_t minimumWidth,
                       size_t minimumHeight,
                       QWidget *parent) : QWidget(parent)
{
        this->setWindowTitle(windowTitle);
        this->setMinimumSize(minimumWidth, minimumHeight);

        logwin = new LoginPage(this);
        user = new UnauthorizedUser(this);
        logwin->setUser(user);

        connect(logwin, &Page::faded, [this]()
                {WelcomePage *wp = new WelcomePage(this);
                setLayout(new QHBoxLayout(this));
                this->layout()->addWidget(wp);
                wp->appear(); });

        this->setObjectName("MainWindow");
        this->setStyleSheet(UserDataBase::readAllFile(STATIC_STYLES_FILE_PATH));
}