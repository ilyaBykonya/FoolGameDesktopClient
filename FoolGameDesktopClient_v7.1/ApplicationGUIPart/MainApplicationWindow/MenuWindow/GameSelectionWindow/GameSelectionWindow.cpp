#include "GameSelectionWindow.h"

GameSelectionWindow::GameSelectionWindow(ChatScene* chatScene, QWidget *parent)
    :QWidget{ parent },
     m_exitButton{ new QPushButton(QIcon("../pictures/quit_button_picture/ara.png"), "", this) },
     m_simplePlayButton{ new QPushButton("Play") },
     m_sharedGameChat{ new ChatView(chatScene, this) },
     m_cashRangeController{ new MinMaxWidget }
    {
        m_simplePlayButton->setFlat(true);
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &GameSelectionWindow::signalExitButtonWasClicked);
        QObject::connect(m_simplePlayButton, &QPushButton::clicked, this, &GameSelectionWindow::signalPlayButtonWasClicked);

        QObject::connect(m_sharedGameChat, &ChatView::signalViewWarResized, chatScene, &ChatScene::resizeAllScene);


        QHBoxLayout* mainGameSelectorLayout = new QHBoxLayout;
            QVBoxLayout* layout = new QVBoxLayout;
                QHBoxLayout* m_exitButtonLayout = new QHBoxLayout;
                m_exitButtonLayout->addStretch(1);
                m_exitButtonLayout->addWidget(m_exitButton, 1, (Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft));
                m_exitButtonLayout->addStretch(2);
            layout->addLayout(m_exitButtonLayout, 1);
            layout->addWidget(m_simplePlayButton, 1, Qt::AlignmentFlag::AlignHCenter);
            layout->addStretch(3);
            layout->addWidget(m_cashRangeController, 1);
        mainGameSelectorLayout->addLayout(layout, 3);
        mainGameSelectorLayout->addWidget(m_sharedGameChat, 4);
        this->setLayout(mainGameSelectorLayout);
        mainGameSelectorLayout->update();
    }

quint32 GameSelectionWindow::minimumCash() const
{
    return m_cashRangeController->min();
}
quint32 GameSelectionWindow::maximumCash() const
{
    return m_cashRangeController->max();
}

void GameSelectionWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}

