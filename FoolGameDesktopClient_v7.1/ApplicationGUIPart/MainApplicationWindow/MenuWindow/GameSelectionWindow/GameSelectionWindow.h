#ifndef GAMESELECTIONWINDOW_H
#define GAMESELECTIONWINDOW_H
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ChatWindow/ChatView/ChatView.h"
#include "ChatWindow/ChatScene/ChatScene.h"
#include "MinMaxWidget/MinMaxWidget.h"

class GameSelectionWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* m_exitButton;
    QPushButton* m_simplePlayButton;

    ChatView* m_sharedGameChat;
    MinMaxWidget* m_cashRangeController;

public:
    explicit GameSelectionWindow(ChatScene*, QWidget *parent = nullptr);

    quint32 minimumCash() const;
    quint32 maximumCash() const;
protected slots:
    virtual void paintEvent(QPaintEvent*) override;

signals:
    void signalExitButtonWasClicked(bool);
    void signalPlayButtonWasClicked(bool);
};

#endif // GAMESELECTIONWINDOW_H
