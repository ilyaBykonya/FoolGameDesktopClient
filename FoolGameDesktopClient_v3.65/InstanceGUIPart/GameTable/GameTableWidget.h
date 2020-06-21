#ifndef GAMETABLEWIDGET_H
#define GAMETABLEWIDGET_H
#include "OtherPlayerDeck/OtherPlayerDeckWidget.h"
#include "ThisPlayerDeck/ThisPlayerDeckWidget.h"
#include "BattleArea/BattleAreaWidget.h"
#include "StartDeck/StartDeckWidget.h"
#include "HandUp/HandUpWidget.h"
#include "ChatWindow/ChatView/ChatView.h"
#include "ChatWindow/ChatScene/ChatScene.h"
#include <QtMath>
#include <QPushButton>
#include <QTimer>
class GameTableWidget : public QWidget
{
    Q_OBJECT
private:
    StartDeckWidget* m_startDeckWidget;
    QList<SharedParentForPlayersDeck*> m_playersList;
    BattleAreaWidget* m_battleAreaWidget;
    HandUpWidget* m_handUpWidget;

    QList<quint32> m_playersIDList;
    ThisPlayerDeckWidget* m_thisPlayer;
    UserID m_thisPlayerID;
    UserID m_attackerID;
    UserID m_defenderID;

    Card* m_bufferCard;


    ChatView* m_instanceChatWindow;

public:
    explicit GameTableWidget(Card::Suit, Card::Dignity, UserID, QList<UserID>, UserID, UserID, quint8, ChatScene*, QWidget *parent = nullptr);

protected:
    SharedParentForPlayersDeck* findDeckForID(quint32);

public slots:
    void serverSlotPlayerTakeAllCards(UserID);
    void serverSlotThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void serverSlotOtherPlayerTakeCardFromDeck(UserID);
    void serverSlotPlayerTossedCard(UserID, Card::Suit, Card::Dignity);
    void serverSlotPlayerBeatCard(UserID, PairID, Card::Suit, Card::Dignity);
    void serverSlotPlayerTransferable(UserID, Card::Suit, Card::Dignity);
    void serverSlotSetNewMainPair(UserID, UserID);
    void serverSlotMakeTurn();

    void serverSlotUnsuccesfullyAction();

    void startCardMove(Card*);
    void playerMoveCard(Card*, QPoint);
    void playerChangeThisCard(Card*, QPoint);

signals:
    void actionButtonWasClicked();
    void tryBeat(PairID, Card::Suit, Card::Dignity);
    void tryToss(Card::Suit, Card::Dignity);
    void tryTrancferable(Card::Suit, Card::Dignity);

};


#endif // GAMETABLEWIDGET_H
