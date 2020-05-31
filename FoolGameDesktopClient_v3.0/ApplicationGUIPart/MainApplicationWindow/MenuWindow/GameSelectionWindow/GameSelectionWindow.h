#ifndef GAMESELECTIONWINDOW_H
#define GAMESELECTIONWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>

class GameSelectionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameSelectionWindow(QWidget *parent = nullptr);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
    void signalPlayButtonWasClicked(bool);
};

#endif // GAMESELECTIONWINDOW_H
