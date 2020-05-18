#include "DefaultWindow.h"

DefaultWindow::DefaultWindow(QWidget *parent)
    :QWidget{ parent },
     m_playButton{ new QPushButton("Play", this) },
     m_paymentButton{ new QPushButton("Money", this) },
     m_optionsButton{ new QPushButton("Options", this) },
     m_quitButton{ new QPushButton("Exit", this) }
    {
        //********************************************************
        //signals
        QObject::connect(m_playButton, &QPushButton::clicked, this, &DefaultWindow::signalPlayButtonWasCLicked);
        QObject::connect(m_paymentButton, &QPushButton::clicked, this, &DefaultWindow::signalPaymentButtonWasCLicked);
        QObject::connect(m_optionsButton, &QPushButton::clicked, this, &DefaultWindow::signalOptionsButtonWasCLicked);
        QObject::connect(m_quitButton, &QPushButton::clicked, this, &DefaultWindow::signalExitButtonWasClicked);

        //********************************************************
        //options
        //Шрифт. Желательно выбрать другой
        m_playButton->setFont(QFont("Perpetua Titling MT", 9, 3));
        m_paymentButton->setFont(QFont("Perpetua Titling MT", 9, 3));
        m_optionsButton->setFont(QFont("Perpetua Titling MT", 9, 3));
        m_quitButton->setFont(QFont("Perpetua Titling MT", 9, 3));

        QPalette pall;
        pall.setColor(QPalette::ColorRole::ButtonText, QColor(128, 0, 0));
        m_playButton->setPalette(pall);
        m_paymentButton->setPalette(pall);
        m_optionsButton->setPalette(pall);
        m_quitButton->setPalette(pall);

        m_playButton->setFlat(true);
        m_paymentButton->setFlat(true);
        m_optionsButton->setFlat(true);
        m_quitButton->setFlat(true);

        //********************************************************
        //layout
        QGridLayout* layout = new QGridLayout;
        layout->setRowStretch(0, 3);
        layout->setRowStretch(5, 3);
        layout->setColumnStretch(0, 1);
        layout->setColumnStretch(4, 1);
        layout->addWidget(m_playButton, 1, 1, 1, 3);
        layout->addWidget(m_paymentButton, 2, 1, 1, 3);
        layout->addWidget(m_optionsButton, 3, 1, 1, 3);
        layout->addWidget(m_quitButton, 4, 1, 1, 3);
        this->setLayout(layout);
        //********************************************************
    }

void DefaultWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}
