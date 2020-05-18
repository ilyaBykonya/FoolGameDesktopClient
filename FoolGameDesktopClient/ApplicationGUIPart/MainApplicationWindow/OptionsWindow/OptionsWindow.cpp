#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(QWidget *parent)
    :QWidget{ parent },
      m_exitButton{ new QPushButton("EXIT", this) }
    {
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &OptionsWindow::signalExitButtonWasClicked);
        m_exitButton->setGeometry(this->rect());
    }
