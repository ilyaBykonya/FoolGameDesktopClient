#include "LogInWindow.h"

LogInWindow::LogInWindow(QWidget *parent)
    :QWidget{ parent },
     m_nameLineEdit{ new  QLineEdit },
     m_passwordLineEdit{ new QLineEdit },
     m_signInButton{ new QPushButton("Sign in") },
     m_registrationButton{ new QPushButton("Registration") },
     m_errorString{ new QLabel("") },
     m_exitButton{ new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "") }
    {
        m_passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        m_errorString->setAlignment(Qt::AlignmentFlag::AlignCenter);
        QPalette errorTextPal = m_errorString->palette();
        errorTextPal.setColor(QPalette::ColorRole::Text, Qt::GlobalColor::red);
        errorTextPal.setColor(QPalette::ColorRole::WindowText, Qt::GlobalColor::red);
        m_errorString->setPalette(errorTextPal);

        QGridLayout* layout = new QGridLayout;
            layout->addWidget(m_exitButton, 0, 0, Qt::AlignmentFlag::AlignCenter);

            layout->addWidget(new QLabel("Autorization yourself:"), 0, 1, Qt::AlignmentFlag::AlignCenter);

            layout->addWidget(new QLabel("Name:"), 1, 0, Qt::AlignmentFlag::AlignRight);
            layout->addWidget(m_nameLineEdit, 1, 1);

            layout->addWidget(new QLabel("Password:"), 2, 0, Qt::AlignmentFlag::AlignRight);
            layout->addWidget(m_passwordLineEdit, 2, 1);

            layout->addWidget(m_errorString, 3, 1);

            layout->addWidget(m_signInButton, 4, 1);
            layout->addWidget(m_registrationButton, 5, 1);

            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 5);
            layout->setRowStretch(0, 2);
            layout->setRowStretch(1, 1);
            layout->setRowStretch(2, 1);
            layout->setRowStretch(3, 1);
            layout->setRowStretch(4, 1);
            layout->setRowStretch(5, 1);
        this->setLayout(layout);


        QObject::connect(m_nameLineEdit, &QLineEdit::returnPressed, this, &LogInWindow::tryLogIn);
        QObject::connect(m_passwordLineEdit, &QLineEdit::returnPressed, this, &LogInWindow::tryLogIn);

        QObject::connect(m_signInButton, &QPushButton::clicked, this, &LogInWindow::tryLogIn);
        QObject::connect(m_registrationButton, &QPushButton::clicked, this, &LogInWindow::signalRegistrationButtonClicked);

        QObject::connect(m_exitButton, &QPushButton::clicked, this, &LogInWindow::signalExitButtonWasClicked);
    }

void LogInWindow::clear()
{
    m_nameLineEdit->clear();
    m_passwordLineEdit->clear();
    m_errorString->clear();
}
void LogInWindow::logInError(const QString& errorMessage)
{
    m_errorString->setText(QString("<h2><sub><i>") + errorMessage + QString("</i></sub></h2>"));
}
void LogInWindow::tryLogIn()
{
    if(m_nameLineEdit->text().size() < 8) {
        m_errorString->setText("<h2><sub><i>Name must be longer 7 symbols</i></sub></h2>");
        return;
    } else if(m_nameLineEdit->text().size() > 16) {
        m_errorString->setText("<h2><sub><i>Name must be shorter 17 symbols</i></sub></h2>");
        return;
    } else if(m_passwordLineEdit->text().size() < 8) {
        m_errorString->setText("<h2><sub><i>Password must be longer 7 symbols</i></sub></h2>");
        return;
    } else if(m_passwordLineEdit->text().size() > 16) {
        m_errorString->setText("<h2><sub><i>Password must be shorter 17 symbols</i></sub></h2>");
        return;
    } else {
        emit this->signalLogInButtonClicked();
    }
}



QString LogInWindow::userName() const
{
    return m_nameLineEdit->text();
}
QString LogInWindow::userPassword() const
{
    return m_passwordLineEdit->text();
}
