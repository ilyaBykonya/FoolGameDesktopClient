#ifndef GAMETABLEWIDGET_H
#define GAMETABLEWIDGET_H
#include "OtherPlayerDeck/OtherPlayerDeckWidget.h"
#include "ThisPlayerDeck/ThisPlayerDeckWidget.h"
#include "BattleArea/BattleAreaWidget.h"
#include "StartDeck/StartDeckWidget.h"
#include "HandUp/HandUpWidget.h"
class PlayerAction
{
private:
    PlayerActionType m_type;
    Card::Suit m_cardSuit;
    Card::Dignity m_cardDignity;
    qint16 m_pairID;
public:
    PlayerAction(PlayerActionType t, Card::Suit s, Card::Dignity d, qint16 p)
        :m_type{ t }, m_cardSuit{ s }, m_cardDignity{ d }, m_pairID{ p }
        {
        }
    PlayerActionType type() const { return m_type; }
    Card::Suit suit() const { return m_cardSuit; }
    Card::Dignity dignity() const { return m_cardDignity; }
    qint16 pairID() const { return m_pairID; }
};


class GameTableWidget : public QWidget
{
    Q_OBJECT
private:
    StartDeckWidget* m_startDeckWidget;
    QList<SharedParentForPlayersDeck*> m_playersList;
    BattleAreaWidget* m_battleAreaWidget;
    HandUpWidget* m_handUpWidget;

    QList<qint16> m_playersIDList;
    ThisPlayerDeckWidget* m_thisPlayer;
    qint16 m_thisPlayerID;
    qint16 m_attackerID;
    qint16 m_defenderID;

    QList<PlayerAction*> m_thisPlayerActionsList;
public:
    explicit GameTableWidget(Card::Suit, Card::Dignity, qint16, QList<qint16>, qint16, qint16, qint16, QWidget *parent = nullptr);

protected:
    SharedParentForPlayersDeck* findDeckForID(qint16);

public slots:
    void serverSlotPlayerTakeAllCards(qint16);
    void serverSlotThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void serverSlotOtherPlayerTakeCardFromDeck(qint16);
    void serverSlotPlayerTossedCard(qint16, Card::Suit, Card::Dignity);
    void serverSlotPlayerBeatCard(qint16, qint16, Card::Suit, Card::Dignity);
    void serverSlotPlayerTransferable(qint16, Card::Suit, Card::Dignity);
    void serverSlotSetNewMainPair(qint16, qint16);
    void serverSlotMakeTurn();

    void serverSlotUnsuccesfullyAction(PlayerActionType, Card::Suit, Card::Dignity, qint16);

    void startCardMove(Card*);
    void playerMoveCard(Card*, QPoint);
    void playerChangeThisCard(Card*, QPoint);

signals:
    void actionButtonWasClicked();
    void tryBeat(Card::Suit, Card::Dignity, qint16);
    void tryToss(Card::Suit, Card::Dignity);
    void tryTrancferable(Card::Suit, Card::Dignity);
};


#endif // GAMETABLEWIDGET_H
