#pragma once
#include "PlayersDecks/OtherPlayerDeck/OtherPlayerDeck.h"
#include "PlayersDecks/ThisPlayerDeck/ThisPlayerDeck.h"
#include "BattleArea/BattleAreaWidget.h"
#include "StartDeck/StartDeckWidget.h"
#include "HandUp/HandUpWidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QtMath>
#include <QFrame>

const quint8 countOfRows = 40;
const quint8 countOfColumns = 17;
class GameTableWidget : public QWidget
{
    Q_OBJECT
private:
    StartDeckWidget* m_startDeckWidget;
    QList<SharedPlayersDeckParent*> m_playersList;
    BattleAreaWidget* m_battleAreaWidget;
    HandUpWidget* m_handUpWidget;

    QList<quint32> m_playersIDList;
    ThisPlayerDeck* m_thisPlayer;
    UserID m_thisPlayerID;
    UserID m_attackerID;
    UserID m_defenderID;

    Card* m_bufferCard;


    QGridLayout* m_tableLayout;
public:
    explicit GameTableWidget(Card::Suit, Card::Dignity, UserID, QList<GameUserInformation*>, UserID, UserID, DeckSize, QWidget *parent = nullptr);


protected:
    SharedPlayersDeckParent* findDeckForID(quint32);

public slots:
    void serverSlotPlayerTossedCard(UserID, Card::Suit, Card::Dignity);
    void serverSlotPlayerBeatCard(UserID, PairID, Card::Suit, Card::Dignity);
    void serverSlotPlayerTransferable(UserID, Card::Suit, Card::Dignity);

    void serverSlotUnsuccesfullyAction();




    void serverSlotPlayerTakeAllCards(UserID);
    void serverSlotThisPlayerTakeCardFromDeck(Card::Suit, Card::Dignity);
    void serverSlotOtherPlayerTakeCardFromDeck(UserID);



    void serverSlotSetNewMainPair(UserID, UserID);
    void serverSlotMakeTurn();



protected slots:
    void slotStartCardMove(Card*);
    void slotPlayerMoveCard(Card*, QPoint);
    void slotPlayerChangeThisCard(Card*, QPoint);

signals:
    void actionButtonWasClicked();
    void tryBeat(PairID, Card::Suit, Card::Dignity);
    void tryToss(Card::Suit, Card::Dignity);
    void tryTrancferable(Card::Suit, Card::Dignity);
};
