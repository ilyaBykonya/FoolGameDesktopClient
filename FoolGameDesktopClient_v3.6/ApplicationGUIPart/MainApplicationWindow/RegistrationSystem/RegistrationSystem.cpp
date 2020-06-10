#include "RegistrationSystem.h"

RegistrationSystem::RegistrationSystem(QWidget *parent)
    :QWidget{ parent },
     m_logInWindow{ new LogInWindow },
     m_registrationWindow{ new RegistrationWindow }
    {
        m_registrationWindow->hide();
        QHBoxLayout* layout = new QHBoxLayout;
            layout->addWidget(m_logInWindow);
            layout->addWidget(m_registrationWindow);
        this->setLayout(layout);


        QObject::connect(m_logInWindow, &LogInWindow::signalRegistrationButtonClicked, [&](){ m_logInWindow->hide(); m_registrationWindow->show(); });
        QObject::connect(m_registrationWindow, &RegistrationWindow::signalLogInButtonClicked, [&](){ m_registrationWindow->hide(); m_logInWindow->show(); });

        QObject::connect(m_logInWindow, &LogInWindow::signalLogInButtonClicked, [&]()
        {
            m_userName = m_logInWindow->userName();
            m_userPassword = m_logInWindow->userPassword();
            emit this->playerTryLogIn(this->m_userName, this->m_userPassword);
        });

        QObject::connect(m_registrationWindow, &RegistrationWindow::signalRegistrationButtonClicked, [&]()
        {
            m_userName = m_registrationWindow->userName();
            m_userPassword = m_registrationWindow->userPassword();
            this->clearEnterWidgets();
            emit this->playerTryRegistration(this->m_userName, this->m_userPassword);

        });

        QObject::connect(m_logInWindow, &LogInWindow::signalExitButtonWasClicked, this, &RegistrationSystem::signalExitButtonWasClicked);
        QObject::connect(m_registrationWindow, &RegistrationWindow::signalExitButtonWasClicked, this, &RegistrationSystem::signalExitButtonWasClicked);
    }

void RegistrationSystem::succesfullyLogIn()
{
    this->playerSignIn(m_userName, m_userPassword);
    this->clearEnterWidgets();
}
void RegistrationSystem::succesfullyRegistration()
{
    this->playerSignIn(m_userName, m_userPassword);
    this->clearEnterWidgets();
}
void RegistrationSystem::unsuccesfullyLogIn(const QString& errorMessage)
{
    m_logInWindow->show();
    m_registrationWindow->hide();
    m_logInWindow->logInError(errorMessage);
}
void RegistrationSystem::unsuccesfullyRegistration(const QString& errorMessage)
{
    m_logInWindow->hide();
    m_registrationWindow->show();
    m_registrationWindow->registrationError(errorMessage);
}

void RegistrationSystem::clearEnterWidgets()
{
    m_logInWindow->clear();
    m_registrationWindow->clear();
}
