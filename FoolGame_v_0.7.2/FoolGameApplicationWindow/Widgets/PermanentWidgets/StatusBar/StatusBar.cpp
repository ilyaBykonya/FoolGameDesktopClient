#include "StatusBar.h"


StatusBar::StatusBar(ThisUserFullInformation* userInfo, QWidget *parent)
    :QWidget{ parent },
     m_userName{ new InfoPanel() },
     m_dollars{ new InfoPanel(QPixmap("D:/bufFiles/pictures/dollar.png")) },
     m_tokens{ new InfoPanel(QPixmap("D:/bufFiles/pictures/coin.png")) },
     m_countOfGames{ new InfoPanel(QPixmap("D:/bufFiles/pictures/cng.png")) },
     m_raitingPoints{ new InfoPanel(QPixmap("D:/bufFiles/pictures/raiting.png")) }
    {
        this->setObjectName("StatusBar");
        this->setMinimumHeight(25);

        QHBoxLayout* layout = new QHBoxLayout;
            layout->addWidget(m_userName);
            layout->addWidget(m_dollars);
            layout->addWidget(m_tokens);
            layout->addWidget(m_countOfGames);
            layout->addWidget(m_raitingPoints);
        this->setLayout(layout);
        layout->setSpacing(0);
        layout->setContentsMargins(5, 1, 5, 1);


        this->slotUpdateInformation(userInfo);
    }

void StatusBar::slotUpdateInformation(ThisUserFullInformation* userInfo)
{
    m_userName->setValue(userInfo->name());
    m_dollars->setValue(QString::number(userInfo->dollars()));
    m_tokens->setValue(QString::number(userInfo->tokens()));
    m_countOfGames->setValue(QString::number(userInfo->countOfGames()));
    m_raitingPoints->setValue(QString::number(userInfo->raitingPoints()));
}

