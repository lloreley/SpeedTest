#ifndef ACCOUNT_PAGE_HPP
#define ACCOUNT_PAGE_HPP

#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include "Page.h"
#include "User.h"
#include "Exception.h"

class AccountPage : public Page
{
    Q_OBJECT
public:
    AccountPage(QWidget *parent);
    ~AccountPage();
    QLabel *createNameLabel();
    QLabel *createEmailLabel();
    QLabel *createDateRegistrationLabel();
    QLabel *createHistoryLabel();
    void setUser(BaseUser *us) noexcept;
    BaseUser *getUser();
public slots:
    void show();
    void addResult(const QString &resultString);

private:
    BaseUser *user;
    void addResultsFromString(const QString &resultsString);
    void setup();
signals:
    void userInstalled();
};

#endif
