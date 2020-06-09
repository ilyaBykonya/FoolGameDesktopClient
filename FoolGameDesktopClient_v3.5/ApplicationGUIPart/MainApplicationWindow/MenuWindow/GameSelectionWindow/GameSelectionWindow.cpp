#include "GameSelectionWindow.h"

GameSelectionWindow::GameSelectionWindow(QWidget *parent)
    :QWidget{ parent },
     m_exitButton{ new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "", this) },
     m_simplePlayButton{ new QPushButton("Play") },
     m_sharedGameChat{ new ChatWindow(ChatWindow::Canal::InApplication) }
    {
        m_simplePlayButton->setFlat(true);
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &GameSelectionWindow::signalExitButtonWasClicked);
        QObject::connect(m_simplePlayButton, &QPushButton::clicked, this, &GameSelectionWindow::signalPlayButtonWasClicked);

        QObject::connect(m_sharedGameChat, &ChatWindow::signalSendMessage, this, &GameSelectionWindow::messageSignalSendMessage);
        QObject::connect(this, &GameSelectionWindow::messageSignalReceiveMessage, m_sharedGameChat, &ChatWindow::slotReceiveMessage);

        QGridLayout* layout = new QGridLayout;
            layout->addWidget(m_exitButton, 0, 0);
            layout->addWidget(m_simplePlayButton, 2, 1);
            layout->addWidget(m_sharedGameChat, 0, 3, 5, 2);
            layout->setRowStretch(0, 1);
            layout->setRowStretch(1, 1);
            layout->setRowStretch(2, 1);
            layout->setRowStretch(3, 1);
            layout->setRowStretch(4, 1);
            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 1);
            layout->setColumnStretch(2, 1);
            layout->setColumnStretch(3, 2);
            layout->setColumnStretch(4, 3);
        this->setLayout(layout);
    }

void GameSelectionWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}

