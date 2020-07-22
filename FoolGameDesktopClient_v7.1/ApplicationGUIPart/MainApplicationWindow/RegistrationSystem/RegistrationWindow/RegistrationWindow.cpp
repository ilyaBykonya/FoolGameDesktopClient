#include "RegistrationWindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    :QWidget{ parent },
     m_nameLineEdit{ new  QLineEdit },
     m_firstPasswordLineEdit{ new QLineEdit },
     m_secondPasswordLineEdit{ new QLineEdit },
     m_registrationButton{ new QPushButton("Registration") },
     m_signInButton{ new QPushButton("Sign in") },
     m_errorString{ new QLabel("") },
     m_exitButton{ new QPushButton(QIcon("../pictures/quit_button_picture/ara.png"), "") }
    {
        m_errorString->setAlignment(Qt::AlignmentFlag::AlignCenter);
        QPalette errorTextPal = m_errorString->palette();
        errorTextPal.setColor(QPalette::ColorRole::Text, Qt::GlobalColor::red);
        errorTextPal.setColor(QPalette::ColorRole::WindowText, Qt::GlobalColor::red);
        m_errorString->setPalette(errorTextPal);

        QGridLayout* layout = new QGridLayout;
            layout->addWidget(m_exitButton, 0, 0, Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft);

            layout->addWidget(new QLabel("Registration yourself:"), 0, 1, Qt::AlignmentFlag::AlignCenter);

            layout->addWidget(new QLabel("Name:"), 1, 0, Qt::AlignmentFlag::AlignRight);
            layout->addWidget(m_nameLineEdit, 1, 1);

            layout->addWidget(new QLabel("Password:"), 2, 0, Qt::AlignmentFlag::AlignRight);
            layout->addWidget(m_firstPasswordLineEdit, 2, 1);

            layout->addWidget(new QLabel("Confirm:"), 3, 0, Qt::AlignmentFlag::AlignRight);
            layout->addWidget(m_secondPasswordLineEdit, 3, 1);

            layout->addWidget(m_errorString, 4, 1, Qt::AlignmentFlag::AlignCenter);

            layout->addWidget(m_registrationButton, 5, 1);
            layout->addWidget(m_signInButton, 6, 1);

            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 5);
            layout->setRowStretch(0, 2);
            layout->setRowStretch(1, 1);
            layout->setRowStretch(2, 1);
            layout->setRowStretch(3, 1);
            layout->setRowStretch(4, 1);
            layout->setRowStretch(5, 1);
        this->setLayout(layout);


        QObject::connect(m_nameLineEdit, &QLineEdit::returnPressed, this, &RegistrationWindow::tryRegistration);
        QObject::connect(m_firstPasswordLineEdit, &QLineEdit::returnPressed, this, &RegistrationWindow::tryRegistration);
        QObject::connect(m_secondPasswordLineEdit, &QLineEdit::returnPressed, this, &RegistrationWindow::tryRegistration);

        QObject::connect(m_registrationButton, &QPushButton::clicked, this, &RegistrationWindow::tryRegistration);
        QObject::connect(m_signInButton, &QPushButton::clicked, this, &RegistrationWindow::signalLogInButtonClicked);

        QObject::connect(m_exitButton, &QPushButton::clicked, this, &RegistrationWindow::signalExitButtonWasClicked);
    }


void RegistrationWindow::clear()
{
    m_nameLineEdit->clear();
    m_firstPasswordLineEdit->clear();
    m_secondPasswordLineEdit->clear();
    m_errorString->clear();
}
void RegistrationWindow::registrationError(const QString& errorMessage)
{
    m_errorString->setText(QString("<h2><sub><i>") + errorMessage + QString("</i></sub></h2>"));
}
void RegistrationWindow::tryRegistration()
{
    if(m_nameLineEdit->text().size() < 8) {
        m_errorString->setText("<h2><sub><i>Name must be longer 7 symbols</i></sub></h2>");
        return;
    } else if(m_nameLineEdit->text().size() > 16) {
        m_errorString->setText("<h2><sub><i>Name must be shorter 17 symbols</i></sub></h2>");
        return;
    } else if(m_firstPasswordLineEdit->text() != m_secondPasswordLineEdit->text()) {
        m_errorString->setText("<h2><sub><i>Passwords mismatch</i></sub></h2>");
        return;
    } else if(m_firstPasswordLineEdit->text().size() < 8) {
        m_errorString->setText("<h2><sub><i>Password must be longer 7 symbols</i></sub></h2>");
        return;
    } else if(m_firstPasswordLineEdit->text().size() > 16) {
        m_errorString->setText("<h2><sub><i>Password must be shorter 17 symbols</i></sub></h2>");
        return;
    } else {
        emit this->signalRegistrationButtonClicked();
    }
}

QString RegistrationWindow::userName() const
{
    return m_nameLineEdit->text();
}
QString RegistrationWindow::userPassword() const
{
    return m_firstPasswordLineEdit->text();
}
