#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include "QLabel"
#include <QPushButton>
#include <QPainter>

class RegistrationWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_passwordEdit;
public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

protected slots:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void checkRight();

signals:
    void signalUserRegistration(const QString&, const QString&);
};

#endif // REGISTRATIONWINDOW_H
