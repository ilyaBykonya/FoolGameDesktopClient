#ifndef GAMESELECTIONWINDOW_H
#define GAMESELECTIONWINDOW_H
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatScene/ChatScene.h"
#include "FoolGameApplicationWindow/Widgets/PermanentWidgets/ChatSystem/ChatView/ChatView.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>

class GameSelectionWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_exitButton;
    QPushButton* m_simplePlayButton;

    ChatView* m_sharedGameChat;


public:
    explicit GameSelectionWindow(ChatScene*, QWidget *parent = nullptr);

signals:
    void signalExitButtonWasClicked(bool);
    void signalPlayButtonWasClicked(bool);
};

#endif // GAMESELECTIONWINDOW_H
