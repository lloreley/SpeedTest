#include "../include/mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
        setup();
        setMinimumSize(MIN_MAIN_WINDOW_WIDHT, MIN_MAIN_WINDOW_HEIGHT);
        setObjectName(MAIN_WINDOW_OBJECT_NAME);
        setStyleSheet(FileDataBase::readAllFile(STATIC_STYLES_FILE_PATH));
}
MainWindow::~MainWindow()
{
        for (auto child : children())
        {
                child->deleteLater();
        }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
        BaseUser *user = area->getAccountPage()->getUser();
        if (user && user->getDateRegistration() != "none")
        {
                user->sendToServer(QString("disconnected\n") + NAME_SELECTOR + LEFT_MESSAGE_BRACKET + user->getName() + RIGHT_MESSAGE_BRACKET);
        }
        event->accept();
}
void MainWindow::emergencyExit(const BaseException ex)
{
        qDebug() << "here1";
        QMessageBox::critical(nullptr, "Error", QString("An error occurred: %1").arg(ex.what()), QMessageBox::Ok);
        QApplication::quit();
}
void MainWindow::isLoginPageHidden()
{
        try
        {
                setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
                area->getAccountPage()->setUser(logpage->getUser());
                connect(area->getAccountPage()->getUser(), &ServerClient::disconnected, [this]()
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
void MainWindow::setup()
{
        layout = new QGridLayout;
        logpage = new LoginPage(this);
        welcomePage = new WelcomePage(this);
        navigationPanel = new NavigationPanel(this);
        area = new ScrollArea(this);
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

        connect(logpage, &LoginPage::hidden, this, &MainWindow::isLoginPageHidden);
        connect(welcomePage, &WelcomePage::hidden, this, &MainWindow::isWelcomePageHidden);
        connect(welcomePage, &WelcomePage::TypingTest, area, &ScrollArea::showRepeatTypingTestPage);
        connect(welcomePage, &WelcomePage::TypingLessons, area, &ScrollArea::showTypingLessonsPage);
        connect(navigationPanel->typingTestButton(), &QAbstractButton::clicked, area, &ScrollArea::showRepeatTypingTestPage);
        connect(navigationPanel->typingLessonsButton(), &QAbstractButton::clicked, area, &ScrollArea::showTypingLessonsPage);
        connect(navigationPanel->accountButton(), &QAbstractButton::clicked, area, &ScrollArea::showAccountPage);
        connect(navigationPanel->logoutButton(), &QAbstractButton::clicked, this, &MainWindow::isLogout);
}
void MainWindow::isLogout()
{
        try
        {
                BaseUser *user = area->getAccountPage()->getUser();
                if (user && user->getDateRegistration() != "none")
                        user->sendToServer(QString("disconnected\n") + NAME_SELECTOR + LEFT_MESSAGE_BRACKET + user->getName() + RIGHT_MESSAGE_BRACKET);
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
        catch (const BaseException &ex)
        {
                emergencyExit(ex);
        }
}