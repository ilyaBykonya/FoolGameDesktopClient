#include "LoadingWindow.h"

LoadingWindow::LoadingWindow(QWidget *parent)
    :QWidget{ parent },
     m_amountOfPoints{ 8 },
     m_redMarkerPosition{ 1 },
     m_firstYellowMarker{ 0 },
     m_secondYellowMarker{ 2 },
     m_exitButton{ new QPushButton(QIcon("../pictures/quit_button_picture/ara.png"), "") }
    {
        this->startTimer(250, Qt::TimerType::PreciseTimer);
        QObject::connect(m_exitButton, &QPushButton::clicked, this, &LoadingWindow::signalExitButtonWasClicked);

        QGridLayout* layout = new QGridLayout;
        layout->addWidget(m_exitButton, 0, 0, 1, 1, Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft);
        layout->setRowStretch(1, 10);
        layout->setColumnStretch(1, 10);
        this->setLayout(layout);
    }

void LoadingWindow::timerEvent(QTimerEvent*)
{
    this->update();
}
void LoadingWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
        painter.setBrush(QBrush(QColor(105, 105, 105)));
        painter.drawRect(this->rect());

    for(quint8 i = 0; i < m_amountOfPoints; ++i)
    {
        if(i == m_redMarkerPosition)
            painter.setPen(QPen(QColor(255, 0, 0), 2));
        else if(i == m_firstYellowMarker || i == m_secondYellowMarker)
            painter.setPen(QPen(QColor(255, 255, 0), 2));
        else
            painter.setPen(QPen(QColor(0, 255, 0), 2));

        qreal angle = ::qDegreesToRadians(360.0 * i / m_amountOfPoints);
        quint16 xPos = (this->width() / 2) + (cos(angle) * 20);
        quint16 yPos = (this->height() / 2) + (sin(angle) * 20);
        painter.drawPoint(xPos, yPos);
    }

    markersStep();
}

void LoadingWindow::markersStep()
{
    ++m_redMarkerPosition;
    if(m_redMarkerPosition == m_amountOfPoints)
        m_redMarkerPosition = 0;

    ++m_firstYellowMarker;
    if(m_firstYellowMarker == m_amountOfPoints)
        m_firstYellowMarker = 0;

    ++m_secondYellowMarker;
    if(m_secondYellowMarker == m_amountOfPoints)
        m_secondYellowMarker = 0;
}
