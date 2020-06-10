#ifndef GAMESELECTIONWINDOW_H
#define GAMESELECTIONWINDOW_H
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>
#include "ChatWindow/ChatWindow.h"
class GameSelectionWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_exitButton;
    QPushButton* m_simplePlayButton;

    ChatWindow* m_sharedGameChat;
public:
    explicit GameSelectionWindow(QWidget *parent = nullptr);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
    void signalPlayButtonWasClicked(bool);


    void messageSignalReceiveMessage(ChatWindow::Canal, const QString&);
    void messageSignalSendMessage(ChatWindow::Canal, const QString&);
};

#endif // GAMESELECTIONWINDOW_H
