#include "../include/AccountPage.h"

AccountPage::AccountPage(QWidget *parent) : Page(parent), user{nullptr}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    CHECK_PTR(layout)
    layout->setContentsMargins(0, 0, 50, 20);
    layout->setSpacing(30);
}
AccountPage::~AccountPage()
{
    for (auto child : children())
    {
        child->deleteLater();
    }
    user->deleteLater();
}
void AccountPage::setup()
{
    if (layout()->count() < 4)
    {
        findChild<QVBoxLayout *>()->addWidget(createNameLabel());
        findChild<QVBoxLayout *>()->addWidget(createEmailLabel());
        findChild<QVBoxLayout *>()->addWidget(createDateRegistrationLabel());
        findChild<QVBoxLayout *>()->addWidget(createHistoryLabel());
    }
}
QLabel *AccountPage::createNameLabel()
{
    CHECK_PTR(user)
    QLabel *nameLabel = new QLabel(this);
    CHECK_PTR(nameLabel)
    nameLabel->setText("Name:  " + user->getName());
    nameLabel->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
    return nameLabel;
}
QLabel *AccountPage::createEmailLabel()
{
    CHECK_PTR(user)
    QLabel *emailLabel = new QLabel(this);
    CHECK_PTR(emailLabel)
    emailLabel->setText("Email:  " + user->getEmail());
    emailLabel->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
    return emailLabel;
}
QLabel *AccountPage::createDateRegistrationLabel()
{
    CHECK_PTR(user)
    QLabel *dateRegistrationLabel = new QLabel(this);
    CHECK_PTR(dateRegistrationLabel)
    dateRegistrationLabel->setText("Date of registration:  " + user->getDateRegistration());
    dateRegistrationLabel->setProperty(ACCOUNT_PAGE_WIDGETS_PROPERTY);
    return dateRegistrationLabel;
}
QLabel *AccountPage::createHistoryLabel()
{
    QLabel *historyLabel = new QLabel(this);
    CHECK_PTR(historyLabel);
    historyLabel->setText("Testing history");
    return historyLabel;
}
void AccountPage::setUser(BaseUser *us) noexcept
{
    user = us;
    if (!user)
        return;
    setup();
    emit userInstalled();
}
BaseUser *AccountPage::getUser()
{
    return user;
}
void AccountPage::show()
{
    Page::show();
    QString userData = user->getUserData();
    if (userData != "" && layout()->count() < 5)
    {
        addResultsFromString(userData.mid(userData.indexOf("Typing history")));
        setStyleSheet(FileDataBase::readAllFile(STATIC_STYLES_FILE_PATH));
    }
}
void AccountPage::addResult(const QString &resultString)
{
    QStringList fields = resultString.split(DELITOR);
    if (fields.size() == 4)
    {
        QString text = fields[0];
        QString charactersPerMinute = fields[1];
        QString accuracy = fields[2];
        QString countMistakes = fields[3];

        QWidget *resultWidget = new QWidget(this);
        QVBoxLayout *resultLayout = new QVBoxLayout(resultWidget);
        resultWidget->setStyleSheet("font-size: 20px; border-radius: 12px;  padding: 0 25px; background-color: #1f2029; ");
        QLabel *textLabel = new QLabel("Plain text: " + text, resultWidget);
        textLabel->setWordWrap(true);
        resultLayout->addWidget(textLabel);
        resultLayout->addWidget(new QLabel("Char per minutes: " + charactersPerMinute, resultWidget));
        resultLayout->addWidget(new QLabel("Accuracy: " + accuracy, resultWidget));
        resultLayout->addWidget(new QLabel("Count mistakes: " + countMistakes, resultWidget));

        findChild<QVBoxLayout *>()->addWidget(resultWidget);
    }
}
void AccountPage::addResultsFromString(const QString &resultsString)
{
    QStringList results = resultsString.split("\n");
    for (const QString &str : results)
    {
        addResult(str);
    }
}
