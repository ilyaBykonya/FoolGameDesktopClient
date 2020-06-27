#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QtMath>

class LoadingWindow : public QWidget
{
    Q_OBJECT
private:
    quint8 m_amountOfPoints;

    quint8 m_redMarkerPosition;
    quint8 m_firstYellowMarker;
    quint8 m_secondYellowMarker;

    QPushButton* m_exitButton;

public:
    explicit LoadingWindow(QWidget *parent = nullptr);

protected slots:
    virtual void timerEvent(QTimerEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;

private:
    void markersStep();

signals:
    void signalExitButtonWasClicked(bool);

};

#endif // LOADINGWINDOW_H
