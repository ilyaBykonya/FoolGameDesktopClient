#ifndef GAMESELECTIONWINDOW_H
#define GAMESELECTIONWINDOW_H
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>
#include "ChatWindow/ChatView/ChatView.h"
#include "ChatWindow/ChatScene/ChatScene.h"
class GameSelectionWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_exitButton;
    QPushButton* m_simplePlayButton;

    ChatView* m_sharedGameChat;
public:
    explicit GameSelectionWindow(ChatScene*, QWidget *parent = nullptr);

protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
    void signalPlayButtonWasClicked(bool);
};

#endif // GAMESELECTIONWINDOW_H
