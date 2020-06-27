#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QtWidgets>

class LogInWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_nameLineEdit;
    QLineEdit* m_passwordLineEdit;

    QPushButton* m_signInButton;
    QPushButton* m_registrationButton;

    QLabel* m_errorString;
    QPushButton* m_exitButton;

public:
    explicit LogInWindow(QWidget *parent = nullptr);
    QString userName() const;
    QString userPassword() const;

signals:
    void signalLogInButtonClicked();
    void signalRegistrationButtonClicked();

    void signalExitButtonWasClicked(bool);

public slots:
    void clear();
    void logInError(const QString&);

protected slots:
    void tryLogIn();
};

#endif // SIGNINWINDOW_H
