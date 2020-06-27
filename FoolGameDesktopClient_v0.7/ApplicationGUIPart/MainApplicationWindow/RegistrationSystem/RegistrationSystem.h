#ifndef REGISTRATIONSYSTEM_H
#define REGISTRATIONSYSTEM_H
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
    void succesfullySignIn();
    void unsuccesfullySignIn(const QString&);

signals:
    void userSignIn(const QString&, const QString&);

    void playerTryLogIn(const QString&, const QString&);
    void playerTryRegistration(const QString&, const QString&);

    void signalExitButtonWasClicked(bool);

protected:
    void clearEnterWidgets();

protected slots:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // REGISTRATIONSYSTEM_H
