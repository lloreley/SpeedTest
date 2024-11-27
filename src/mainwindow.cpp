#include "../include/mainwindow.hpp"
MainWindow::MainWindow(const char *windowTitle,
                       size_t minimumWidth,
                       size_t minimumHeight,
                       QWidget *parent) : QWidget(parent)
{
        createWidgets();
        setConnections();
        this->setWindowTitle(windowTitle);
        this->setMinimumSize(minimumWidth, minimumHeight);
        this->setObjectName(MAIN_WINDOW_OBJECT_NAME);
        this->setStyleSheet(UserDataBase::readAllFile(STATIC_STYLES_FILE_PATH));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        if (QMessageBox::question(this, "Question", "Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
                event->ignore();
        }
        else
        {
                BaseUser *user = area->getAccountPage()->getUser();
                if (user && user->getDateRegistration() != "none")
                {
                        user->sendToServer(QString("disconnected\n") + NAME_SELECTOR + LEFT_MESSAGE_BRACKET + user->getName() + RIGHT_MESSAGE_BRACKET);
                }
                event->accept();
        }
}

void MainWindow::emergencyExit(const BaseException ex)
{
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(ex.what()), QMessageBox::Ok);
        std::exit(0);
}

void MainWindow::isLoginPageHidden()
{
        try
        {
                setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
                area->getAccountPage()->setUser(logpage->getUser());
                connect(area->getAccountPage()->getUser(), &ServerClient::disconnect, [this]()
                        {QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg("server stopped work"), QMessageBox::Ok);
                        isLogout(); });
                setLayout(layout);
                welcomePage->show();
        }
        catch (const BaseException ex)
        {
                emergencyExit(ex);
        }
}

void MainWindow::isWelcomePageHidden()
{
        area->show();
        navigationPanel->show();
}

void MainWindow::createWidgets()
{
        layout = new QGridLayout;
        logpage = new LoginPage(this);
        welcomePage = new WelcomePage(this);
        navigationPanel = new NavigationPanel(this);
        area = new LessonsScrollArea(this);
        CHECK_PTR(logpage)
        CHECK_PTR(welcomePage)
        CHECK_PTR(navigationPanel)
        CHECK_PTR(layout)
        CHECK_PTR(area)

        layout->addWidget(area, 0, 2, 10, 8);
        layout->addWidget(welcomePage, 0, 0, 10, 10);
        layout->addWidget(navigationPanel, 0, 0, 10, 1);
        logpage->show();

        for (int i = 0; i < layout->columnCount(); ++i)
                layout->setColumnStretch(i, 1);
        for (int i = 0; i < layout->rowCount(); ++i)
        {
                layout->setRowStretch(i, 1);
        }
        layout->setContentsMargins(ZERO_CONTENTS_MARGINS);
}

void MainWindow::setConnections()
{
        connect(logpage, &LoginPage::hidden, this, &MainWindow::isLoginPageHidden);
        connect(welcomePage, &WelcomePage::hidden, this, &MainWindow::isWelcomePageHidden);
        connect(welcomePage, &WelcomePage::TypingTest, area, &LessonsScrollArea::showRepeatTypingTestPage);
        connect(welcomePage, &WelcomePage::TypingLessons, area, &LessonsScrollArea::showTypingLessonsPage);
        connect(navigationPanel->typingTestButton(), &QAbstractButton::clicked, area, &LessonsScrollArea::showRepeatTypingTestPage);
        connect(navigationPanel->typingLessonsButton(), &QAbstractButton::clicked, area, &LessonsScrollArea::showTypingLessonsPage);
        connect(navigationPanel->accountButton(), &QAbstractButton::clicked, area, &LessonsScrollArea::showAccountPage);
        connect(navigationPanel->logoutButton(), &QAbstractButton::clicked, this, &MainWindow::isLogout);
}

void MainWindow::isLogout()
{
        BaseUser *user = area->getAccountPage()->getUser();
        if (user && user->getDateRegistration() != "none")
        {
                user->sendToServer(QString("disconnected\n") + NAME_SELECTOR + LEFT_MESSAGE_BRACKET + user->getName() + RIGHT_MESSAGE_BRACKET);
        }
        user->deleteLater();
        area->getAccountPage()->setUser(nullptr);
        area->hide();
        navigationPanel->QWidget::hide();
        welcomePage->QWidget::hide();
        logpage->show();
        logpage->createUnauthorizedUser();
        QLayout *accountLayout = area->getAccountPage()->layout();
        CHECK_PTR(accountLayout)
        QLayoutItem *item;
        while ((item = accountLayout->takeAt(0)) != nullptr)
        {
                if (QWidget *widget = item->widget())
                {
                        widget->deleteLater();
                }
                delete item;
        }
}