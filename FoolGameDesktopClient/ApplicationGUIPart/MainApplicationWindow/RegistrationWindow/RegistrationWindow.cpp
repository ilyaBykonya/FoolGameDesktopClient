#include "RegistrationWindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    :QWidget{ parent },
     m_nameEdit{ new QLineEdit("Name") },
     m_passwordEdit{ new QLineEdit("Password") }
    {
        QPushButton* signInButton = new QPushButton("Sign in");
        QObject::connect(signInButton, &QPushButton::clicked, this, &RegistrationWindow::checkRight);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addStretch(3);
        layout->addWidget(new QLabel("Enter your name:"));
        layout->addWidget(m_nameEdit);
        layout->addStretch(1);
        layout->addWidget(new QLabel("Enter your password:"));
        layout->addWidget(m_passwordEdit);
        layout->addStretch(2);
        layout->addWidget(signInButton);
        layout->addStretch(1);
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
    if((name.isNull()) || (name == ""))
        return;
    if((password.isNull()) || (password == ""))
        return;

    emit signalUserRegistration(name, password);
}
