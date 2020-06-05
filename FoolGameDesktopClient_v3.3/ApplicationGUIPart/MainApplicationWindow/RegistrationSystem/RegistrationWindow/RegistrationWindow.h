#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QtWidgets>

class RegistrationWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_nameLineEdit;
    QLineEdit* m_firstPasswordLineEdit;
    QLineEdit* m_secondPasswordLineEdit;

    QPushButton* m_registrationButton;
    QPushButton* m_signInButton;

    QLabel* m_errorString;
    QPushButton* m_exitButton;

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    QString userName() const;
    QString userPassword() const;

signals:
    void signalRegistrationButtonClicked();
    void signalLogInButtonClicked();

    void signalExitButtonWasClicked(bool);

public slots:
    void clear();
    void registrationError(const QString&);

protected slots:
    void tryRegistration();
};

#endif // REGISTRATIONWINDOW_H
