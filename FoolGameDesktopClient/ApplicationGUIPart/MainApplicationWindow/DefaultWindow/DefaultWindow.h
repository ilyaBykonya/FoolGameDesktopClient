#ifndef DEFAULTWINDOW_H
#define DEFAULTWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>

class DefaultWindow : public QWidget
{
    Q_OBJECT

private:
    QPushButton* m_playButton;
    QPushButton* m_paymentButton;
    QPushButton* m_optionsButton;
    QPushButton* m_quitButton;

public:
    explicit DefaultWindow(QWidget *parent = nullptr);

signals:
    void signalPlayButtonWasCLicked(bool);
    void signalPaymentButtonWasCLicked(bool);
    void signalOptionsButtonWasCLicked(bool);
    void signalExitButtonWasClicked(bool);

protected slots:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // DEFAULTWINDOW_H
