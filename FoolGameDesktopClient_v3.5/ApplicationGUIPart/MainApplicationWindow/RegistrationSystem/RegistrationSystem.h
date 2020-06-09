#ifndef REGISTRATIONSYSTEM_H
#define REGISTRATIONSYSTEM_H

#include <QWidget>
#include "LogInWindow/LogInWindow.h"
#include "RegistrationWindow/RegistrationWindow.h"


class RegistrationSystem : public QWidget
{
    Q_OBJECT

private:
    LogInWindow* m_logInWindow;
    RegistrationWindow* m_registrationWindow;

    QString m_userName;
    QString m_userPassword;
public:
    explicit RegistrationSystem(QWidget *parent = nullptr);

public slots:
    void succesfullyLogIn();
    void succesfullyRegistration();
    void unsuccesfullyLogIn(const QString&);
    void unsuccesfullyRegistration(const QString&);

signals:
    void playerSignIn(const QString&, const QString&);

    void playerTryLogIn(const QString&, const QString&);
    void playerTryRegistration(const QString&, const QString&);

    void signalExitButtonWasClicked(bool);

protected:
    void clearEnterWidgets();
};

#endif // REGISTRATIONSYSTEM_H
