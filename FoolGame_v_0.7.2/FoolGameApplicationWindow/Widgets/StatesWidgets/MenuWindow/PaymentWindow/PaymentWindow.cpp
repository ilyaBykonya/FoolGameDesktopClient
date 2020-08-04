#include "PaymentWindow.h"

PaymentWindow::PaymentWindow(QWidget *parent)
    :QWidget{ parent },
     m_transactionChanger{ new QComboBox },
     m_addTokens{ new QPushButton("Add cash") },
     m_subTokens{ new QPushButton("Substract cash") },
     m_exitButton{ new QPushButton(QIcon("D:/FoolGame/FoolGameDesktopClient/pictures/quit_button_picture/ara.png"), "") }
    {
        //=====================================================================
        //=====================================================================


        for(quint8 i = 0; i < countOfTransactons; ++i)
            m_transactionChanger->addItem(QString::number(transactions[i]));

        m_transactionChanger->setCurrentIndex(0);


        //=====================================================================
        //=====================================================================

        QGridLayout* layout = new QGridLayout;
        layout->addWidget(m_exitButton, 0, 0, 1, 1);
        layout->setRowStretch(1, 2);
        layout->addWidget(new QLabel("Change cash:"), 2, 1, 1, 4);
        layout->addWidget(m_transactionChanger, 3, 1, 1, 4);
        layout->addWidget(m_subTokens, 4, 1, 1, 2);
        layout->addWidget(m_addTokens, 4, 3, 1, 2);
        layout->setRowStretch(5, 1);
        layout->setColumnStretch(5, 1);
        this->setLayout(layout);

        QObject::connect(m_addTokens, &QPushButton::clicked, [&](){ emit singalDepositToWallet(transactions[m_transactionChanger->currentIndex()]); m_transactionChanger->setCurrentIndex(0); });
        QObject::connect(m_subTokens, &QPushButton::clicked, [&](){ emit singalWithdrawFromWallet(transactions[m_transactionChanger->currentIndex()]); m_transactionChanger->setCurrentIndex(0); });
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &PaymentWindow::signalExitButtonWasClicked);
    }
