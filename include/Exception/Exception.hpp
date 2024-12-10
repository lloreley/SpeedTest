#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <QString>

class BaseException
{
public:
    explicit BaseException(const QString &message) : message_(message) {}
    virtual QString what() const { return message_; }
    virtual ~BaseException() {}

private:
    QString message_;
};

class InvalidNameException : public BaseException
{
public:
    explicit InvalidNameException(const QString &name)
        : BaseException("Invalid name: '" + name + "'. Name must start with a letter and contain 3 to 30 characters (letters, digits, or '_').") {}
};

class InvalidEmailException : public BaseException
{
public:
    explicit InvalidEmailException(const QString &email)
        : BaseException("Invalid email: '" + email + "'. Please enter a valid email address (e.g., example@domain.com).") {}
};

class InvalidPasswordException : public BaseException
{
public:
    explicit InvalidPasswordException(const QString &password)
        : BaseException("Invalid password! Password must be at least 8 characters long and include at least one uppercase letter, one lowercase letter, one digit, and one special character.") {}
};

class FileOpenException : public BaseException
{
public:
    explicit FileOpenException(const QString &fileName)
        : BaseException("Error opening file: " + fileName) {}
};

class NullPointerException : public BaseException
{
public:
    explicit NullPointerException(const QString &pointerName)
        : BaseException("Null pointer exception: " + pointerName + " is null.") {}
};

#endif
