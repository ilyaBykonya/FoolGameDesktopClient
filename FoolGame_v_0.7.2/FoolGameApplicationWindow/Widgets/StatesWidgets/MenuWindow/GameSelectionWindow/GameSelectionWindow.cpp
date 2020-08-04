#include "GameSelectionWindow.h"

GameSelectionWindow::GameSelectionWindow(ChatScene* chatScene, QWidget *parent)
    :QWidget{ parent },
     m_exitButton{ new QPushButton(QIcon("D:/FoolGame/FoolGameDesktopClient/pictures/quit_button_picture/ara.png"), "", this) },
     m_simplePlayButton{ new QPushButton("Play") },
     m_sharedGameChat{ new ChatView(chatScene, this) }
    {
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &GameSelectionWindow::signalExitButtonWasClicked);
        QObject::connect(m_simplePlayButton, &QPushButton::clicked, this, &GameSelectionWindow::signalPlayButtonWasClicked);

        QObject::connect(m_sharedGameChat, &ChatView::signalViewWarResized, chatScene, &ChatScene::resizeAllScene);



        QHBoxLayout* mainGameSelectorLayout = new QHBoxLayout;
            QVBoxLayout* layout = new QVBoxLayout;
                QHBoxLayout* m_exitButtonLayout = new QHBoxLayout;
                m_exitButtonLayout->addWidget(m_exitButton, 0, (Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft));
                m_exitButtonLayout->addStretch(3);
            layout->addLayout(m_exitButtonLayout, 1);
            layout->addWidget(m_simplePlayButton, 1, Qt::AlignmentFlag::AlignHCenter);
            layout->addStretch(3);
        mainGameSelectorLayout->addLayout(layout, 3);
        mainGameSelectorLayout->addWidget(m_sharedGameChat, 4);
        this->setLayout(mainGameSelectorLayout);
        mainGameSelectorLayout->update();
    }

