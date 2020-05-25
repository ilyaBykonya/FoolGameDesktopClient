#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H
#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>

class PaymentWindow : public QWidget
{
    Q_OBJECT
    QSpinBox* m_spinBox;
    QPushButton* m_addCash;
    QPushButton* m_subCash;

    QPushButton* m_exitButton;

public:
    explicit PaymentWindow(QWidget *parent = nullptr);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
    void signalUserAddCash(qint16);
    void signalUserSubCash(qint16);
};

#endif // PAYMENTWINDOW_H
