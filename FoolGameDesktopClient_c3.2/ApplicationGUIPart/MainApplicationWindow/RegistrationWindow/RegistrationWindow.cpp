#include "RegistrationWindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    :QWidget{ parent },
     m_nameEdit{ new QLineEdit("") },
     m_passwordEdit{ new QLineEdit("") }
    {
        QPushButton* signInButton = new QPushButton("Sign in");
        QObject::connect(signInButton, &QPushButton::clicked, this, &RegistrationWindow::checkRight);
        m_nameEdit->setPlaceholderText("Name");
        m_passwordEdit->setPlaceholderText("Password");
        m_passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
        QPushButton* exitButton = new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "");
        QObject::connect(exitButton, &QPushButton::clicked, this, &RegistrationWindow::signalExitButtonWasClicked);

        QGridLayout* signInLayout = new QGridLayout;
        signInLayout->addWidget(m_nameEdit, 0, 0, 1, 3);
        signInLayout->addWidget(m_passwordEdit, 1, 0, 1, 3);
        signInLayout->addWidget(signInButton, 2, 1, 1, 1);

        QGridLayout* layout = new QGridLayout;
            layout->addWidget(exitButton, 0, 6);
            layout->addLayout(signInLayout, 2, 1, 1, 5);
            layout->setRowStretch(0, 2);
            layout->setRowStretch(1, 2);
            layout->setRowStretch(2, 0);
            layout->setRowStretch(3, 2);
            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 1);
            layout->setColumnStretch(2, 1);
            layout->setColumnStretch(3, 1);
            layout->setColumnStretch(4, 1);
            layout->setColumnStretch(5, 1);
            layout->setColumnStretch(6, 1);
        this->setLayout(layout);
    }

void RegistrationWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}

void RegistrationWindow::checkRight()
{
    QString name(m_nameEdit->text());
    QString password(m_passwordEdit->text());
    if((name.isNull()) || (name.length() < 5))
        return;
    if((password.isNull()) || (password.length() < 8))
        return;

    emit signalUserRegistration(name, password);
}
