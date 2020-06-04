#include "GameSelectionWindow.h"

GameSelectionWindow::GameSelectionWindow(QWidget *parent)
    :QWidget(parent)
    {
        QPushButton* btn = new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "", this);
        QObject::connect(btn, &QPushButton::clicked, this, &GameSelectionWindow::signalExitButtonWasClicked);

        QPushButton* simplePlayButton = new QPushButton("Play");
        simplePlayButton->setFlat(true);
        QObject::connect(simplePlayButton, &QPushButton::clicked, this, &GameSelectionWindow::signalPlayButtonWasClicked);

        QGridLayout* layout = new QGridLayout;
            layout->addWidget(btn, 0, 0);
            layout->addWidget(simplePlayButton, 2, 3);
            layout->setRowStretch(0, 1);
            layout->setRowStretch(1, 2);
            layout->setRowStretch(2, 1);
            layout->setRowStretch(3, 2);
            layout->setRowStretch(4, 2);
            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 1);
            layout->setColumnStretch(2, 1);
            layout->setColumnStretch(3, 2);
            layout->setColumnStretch(4, 1);
            layout->setColumnStretch(5, 1);
            layout->setColumnStretch(6, 1);
        this->setLayout(layout);
    }

void GameSelectionWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}

