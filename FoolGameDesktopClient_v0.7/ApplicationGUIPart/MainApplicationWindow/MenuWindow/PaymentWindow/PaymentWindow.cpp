#include "PaymentWindow.h"

PaymentWindow::PaymentWindow(QWidget *parent)
    :QWidget{ parent },
     m_spinBox{ new QSpinBox },
     m_addCash{ new QPushButton("Add cash") },
     m_subCash{ new QPushButton("Substract cash") },
     m_exitButton{ new QPushButton(QIcon("D:/bufFiles/pictures/ara.png"), "") }
    {
        m_spinBox->setRange(0, 10000);
        m_spinBox->setValue(0);


        QGridLayout* layout = new QGridLayout;
        layout->addWidget(m_exitButton, 0, 0, 1, 1);
        layout->setRowStretch(1, 2);
        layout->addWidget(new QLabel("Change cash:"), 2, 1, 1, 4);
        layout->addWidget(m_spinBox, 3, 1, 1, 4);
        layout->addWidget(m_subCash, 4, 1, 1, 2);
        layout->addWidget(m_addCash, 4, 3, 1, 2);
        layout->setRowStretch(5, 1);
        layout->setColumnStretch(5, 1);
        this->setLayout(layout);

        QObject::connect(m_addCash, &QPushButton::clicked, [&](){ emit signalUserAddCash(m_spinBox->value()); m_spinBox->setValue(0);});
        QObject::connect(m_subCash, &QPushButton::clicked, [&](){ emit signalUserSubCash(m_spinBox->value()); m_spinBox->setValue(0);});
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &PaymentWindow::signalExitButtonWasClicked);
    }

void PaymentWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());
}
